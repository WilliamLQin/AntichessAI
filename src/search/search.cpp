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
        std::cout << " q: " << quiesce(0, 0, EVAL_MIN, EVAL_MAX);
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
            for (int i = 0; i < ((int)moves.size()); i++)
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

void Search::orderMovesByTT(std::vector<chess::Move> &moves)
{
    std::sort(moves.begin(), moves.end(),
        [this](const chess::Move &a, const chess::Move &b) {
            int aEval = 1000;
            tt_obj.push(a);
            std::optional<TranspositionTable::TTEntry> ttEntry = tt_obj.loadEval();
            if (ttEntry != std::nullopt)
            {
                aEval = ttEntry->eval;
            }
            tt_obj.pop();

            int bEval = 1000;
            tt_obj.push(b);
            ttEntry = tt_obj.loadEval();
            if (ttEntry != std::nullopt)
            {
                bEval = ttEntry->eval;
            }
            tt_obj.pop();

            return aEval < bEval; // want WORST result for the other player first => BEST move for us
        }
    );
}

// 6 piece types
// PAWN = 1, KNIGHT = 2, BISHOP = 3, ROOK = 4, QUEEN = 5, KING = 6;
// Victim first, then attacker
int mvv_lva_table[6][6] = {
        15, 14, 13, 12, 11, 10, // victim P, attacker P, N, B, R, Q, K
        25, 24, 23, 22, 21, 20, // victim N, attacker P, N, B, R, Q, K
        35, 34, 33, 32, 31, 30, // victim B, attacker P, N, B, R, Q, K
        45, 44, 43, 42, 41, 40, // victim R, attacker P, N, B, R, Q, K
        55, 54, 53, 52, 51, 50, // victim Q, attacker P, N, B, R, Q, K
        0, 0, 0, 0, 0, 0, // victim K, attacker P, N, B, R, Q, K
};

void Search::orderMovesByMVVLVA(std::vector<chess::Move> &moves)
{
    std::sort(moves.begin(), moves.end(),
        [this](const chess::Move &a, const chess::Move &b) {
            int aVal = 0;
            std::optional<chess::Piece> aVictim = board.piece_at(a.to_square);
            std::optional<chess::Piece> aAttacker = board.piece_at(a.from_square);
            if (aVictim != std::nullopt && aAttacker != std::nullopt)
            {
                aVal = mvv_lva_table[aVictim->piece_type - 1][aAttacker->piece_type - 1];
            }

            int bVal = 0;
            std::optional<chess::Piece> bVictim = board.piece_at(a.to_square);
            std::optional<chess::Piece> bAttacker = board.piece_at(a.from_square);
            if (bVictim != std::nullopt && bAttacker != std::nullopt)
            {
                bVal = mvv_lva_table[bVictim->piece_type - 1][bAttacker->piece_type - 1];
            }

            return aVal > bVal; // higher priority goes FIRST
        }
    );
}

// QUIESCENCE SEARCH - search captures only with alpha beta and eager evaluation
int Search::quiesce(int counter, int moves_pushed, int alpha, int beta)
{
    int val = eval.evaluate(board.turn);

    // hard stop
    if (counter < -8 && moves_pushed % 2 == 0)
    {
        return val;
    }

    if (val >= beta)
    {
        return beta;
    }
//    if (val > alpha)
//    {
//        alpha = val;
//    }

    std::vector<chess::Move> moves = board.generate_legal_captures();
    if (moves.empty())
    {
        return val;
    }
    orderMovesByMVVLVA(moves);

    // DFS backtrack search: play move, recurse, unplay move
    for (int i = 0; i < ((int)moves.size()); i++)
    {
        tt_obj.push(moves[i]); // play move

        int childScore = -quiesce(counter - 1, moves_pushed + 1, -beta, -alpha);

        tt_obj.pop(); // un play move

        if (childScore > alpha)
        {
            alpha = childScore;
        }

        // alpha-beta pruning
        if (alpha >= beta)
        {
            return beta;
        }
    }

    return alpha;
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
        int val = quiesce(counter, moves_pushed, EVAL_MIN, EVAL_MAX);
        tt_obj.storeEval(val, counter, TT_EXACT, (char*)"000000");
        return val;
    }

    // check if there are any forced captures
    std::vector<chess::Move> moves = board.generate_legal_captures();
    if (moves.empty()) // no forced captures
    {
        moves = board.generate_legal_moves();
        // MOVE ORDERING - sort the moves by transposition table entry hits
        orderMovesByTT(moves);
    }
    else
    {
        orderMovesByMVVLVA(moves);
    }


#ifdef DEBUG2
    for (int i = 0; i < ((int)moves.size()); i++)
    {
        tt_obj.push(moves[i]);
        std::optional<TranspositionTable::TTEntry> ttEntry = tt_obj.loadEval();
        if (ttEntry != std::nullopt)
        {
            std::cout << ttEntry->eval << " ";
        }
        else
        {
            std::cout << "n/a ";
        }
        tt_obj.pop();
    }

    if (bestResponse != std::nullopt)
    {
        std::cout << bestResponse.value() << " " << moves[0] << " " << moves.back() << std::endl;
    }
    else
    {
        std::cout << "No best response" << std::endl;
    }
#endif

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
