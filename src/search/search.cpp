#include "search.h"
#include <iostream>
#include <vector>

#ifdef DEBUG
long long int numSearched = 0;
long long int ttHits = 0;
#endif

void Search::walkLine()
{
    std::optional<TranspositionTable::TTEntry> ttEntry = tt_obj.loadEval();
    if (ttEntry != std::nullopt && strcmp(ttEntry->move_uci, "000000") != 0 && !board.is_game_over(true))
    {
        chess::Move nextMove = chess::Move::from_uci(ttEntry->move_uci);
        std::cout << "(" << ttEntry->eval << ", " << ttEntry->depth << ", " << ttEntry->nodeType << ")" << "->" << ttEntry->move_uci << " ";
        tt_obj.push(nextMove);
        walkLine();
        tt_obj.pop();
    }
    else
    {
        std::cout << "(" << ttEntry->eval << ", " << ttEntry->depth << ", " << ttEntry->nodeType << ")";
    }
}

chess::Move Search::best_move()
{
    std::vector<chess::Move> moves;

    // negamax search
    int bestMove = 0;

    moves = board.generate_legal_captures();
    if (moves.empty())
    {
        moves = board.generate_legal_moves();
    }

    // forced move
    if (moves.size() == 1)
    {
        return moves[0];
    }

    // TODO: Move ordering

#ifdef DEBUG
    numSearched = 0;
    ttHits = 0;
#endif
    // wrap iterative deepening in try block as out of time will raise exception
    try
    {
        // ITERATIVE DEEPENING, keep increasing levels until timer.checkpoint() returns false
        for (int level = 1;; level += 1)
        {
            // negamax search
            int iterBestIndex = 0;
            int iterBestEval = EVAL_MIN;

            // First ply - look through each move and find the one with the best score
            for (int i = 0; i < moves.size(); i++)
            {
                tt_obj.push(moves[i]);
//#ifdef DEBUG
//                std::cout << std::endl << "Searching move " << moves[i].uci() << std::endl;
//#endif
                int val = -alphaBeta(level - 1, 1, EVAL_MIN, EVAL_MAX);

                if (val > iterBestEval)
                {
                    iterBestEval = val;
                    iterBestIndex = i;
                }
                tt_obj.pop();
            }

            // only update best move if entire level searched
            bestMove = iterBestIndex;

#ifdef DEBUG
            std::cout << "best move for level " << level << ": " << moves[bestMove].uci()
                << " " << iterBestEval << std::endl;

            tt_obj.push(moves[bestMove]);
            std::cout << moves[bestMove].uci() << " ";
            walkLine();
            std::cout << std::endl;
            tt_obj.pop();

            std::cout << "num positions searched: " << numSearched << std::endl;
            std::cout << "tt hits: " << ttHits << std::endl;
#endif

            // checkmate at lowest depth (given by iterative deepening)
            if (iterBestEval == EVAL_MAX) {
                break;
            }
        }
    }
    catch (const Timer::OutOfTime &e)
    {
        // pop all moves
        for (int i = 0; i < e.depth; i += 1)
        {
            tt_obj.pop();
        }
    }
#ifdef DEBUG
    std::cout << "Number of positions searched: " << numSearched << std::endl;
    std::cout << "Transposition table hits: " << ttHits << std::endl;
#endif
    return moves[bestMove];
}

// DFS negamax
// with "full" search of forced moves (capture or check)
int Search::alphaBeta(int counter, int moves_pushed, int alpha, int beta)
{
    timer.checkOutOfTime(moves_pushed);
#ifdef DEBUG
    numSearched += 1;
#endif

    // Search stop: game over
    // do this BEFORE transposition table load to notice threefold repetition
    if (board.is_game_over(true))
    {
        int val = eval.evaluate(board.turn);
        tt_obj.storeEval(val, counter, TT_EXACT, (char*)"000000");
        return val;
    }

    int alphaOriginal = alpha;

    // TRANSPOSITION TABLE LOAD - check cache
    std::optional<chess::Move> bestResponse = std::nullopt;
    std::optional<TranspositionTable::TTEntry> ttEntry = tt_obj.loadEval();
    if (ttEntry != std::nullopt)
    {
#ifdef DEBUG
        ttHits += 1;
#endif
        if (ttEntry->depth >= counter)
        {
            if (ttEntry->nodeType == TT_EXACT) // EXACT
            {
                return ttEntry->eval;
            }
            else if (ttEntry->nodeType == TT_BETA) // LOWER BOUND
            {
                if (ttEntry->eval > alpha) // can raise the lower bound?
                {
                    alpha = ttEntry->eval;
                }
            }
            else if (ttEntry->nodeType == TT_ALPHA) // UPPER BOUND
            {
                if (ttEntry->eval < beta) // can lower the upper bound?
                {
                    beta = ttEntry->eval;
                }
            }

            if (alpha >= beta)
            {
                return ttEntry->eval;
            }
        }

        if (strcmp(ttEntry->move_uci, "000000") != 0)
        {
            bestResponse = std::optional<chess::Move>(chess::Move::from_uci(ttEntry->move_uci));
        }
    }

    // Search stop: end of search
    if (counter <= 0)
    {
        int val = eval.evaluate(board.turn);
        tt_obj.storeEval(val, counter, TT_EXACT, (char*)"000000");
        return val;
    }

    // currently performing QUIESCENCE SEARCH (i.e. searching down forced moves after a capture)
//    if (counter < 0) {
//        // For quiescence search, we want to calculate static evaluation at every node
//        // to do some alpha beta pruning
//        int value = eval.evaluate(board.turn);
////        tt_obj.storeEval(value, searchDepth - counter, 'q', (char*)"000000");
////        return value;
//        if (value >= beta)
//        {
//            tt_obj.storeEval(value, searchDepth - counter, 'q', (char*)"000000");
//            return beta;
//        }
//        if (value > alpha)
//        {
//            alpha = value;
//        }
//    }

    // check if there are any forced captures
    std::vector<chess::Move> moves = board.generate_legal_captures();
    if (moves.empty()) // no forced captures
    {
        // no forced captures && not check => not forced move
        // counter <= 0 so search depth reached, stop
//        if (!board.is_check() && counter <= 0)
//        {
//            int val = eval.evaluate(board.turn);
//            tt_obj.storeEval(val, counter, TT_EXACT, (char*)"000000");
//            return val;
//        }

        // if didn't stop, move set is all legal moves
        moves = board.generate_legal_moves();
    }

    // TODO: move ordering

    int bestEval = EVAL_MIN;
    int bestMoveIndex = 0;
    // DFS backtrack search: play move, recurse, unplay move
    for (int i = -1; i < ((int)moves.size()); i++)
    {
        if (i == -1)
        {
            if (bestResponse != std::nullopt)
            {
                tt_obj.push(bestResponse.value());
            }
            else
            {
                continue;
            }
        }
        else
        {
            tt_obj.push(moves[i]); // play move
        }

//#ifdef DEBUG
//        std::cout << move.uci() << " " << counter << " ";
//#endif
        int childScore = -alphaBeta(counter - 1, moves_pushed + 1, -beta, -alpha);

        tt_obj.pop(); // un play move

        if (childScore > bestEval)
        {
            bestEval = childScore;
            bestMoveIndex = i;
        }

        if (childScore > alpha)
        {
            alpha = childScore;
        }

        // alpha-beta pruning
        if (alpha >= beta)
        {
            break;
        }
    }

    // TRANSPOSITION TABLE STORE
    char nodeType = TT_EXACT;
    if (bestEval <= alphaOriginal)
    {
        nodeType = TT_ALPHA; // UPPERBOUND
    }
    else if (bestEval >= beta)
    {
        nodeType = TT_BETA; // LOWERBOUND
    }
    // else EXACT

    // bestResponse should be nonnull if bestMoveIndex == -1
    tt_obj.storeEval(
        bestEval,
        counter,
        nodeType,
        bestMoveIndex == -1 ? bestResponse.value().uci().c_str() : moves[bestMoveIndex].uci().c_str()
    );

    return alpha;
}
