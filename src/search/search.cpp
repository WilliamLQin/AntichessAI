#include "search.h"
#include <iostream>
#include <vector>

#ifdef DEBUG
long long int numSearched = 0;
#endif

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
                board.push(moves[i]);
//#ifdef DEBUG
//                std::cout << std::endl << "Searching move " << moves[i].uci() << std::endl;
//#endif
                // Do the rest of the search starting with this move
                int val = -alphaBeta(level - 1, 1, EVAL_MIN, EVAL_MAX);

                if (val > iterBestEval)
                {
                    iterBestEval = val;
                    iterBestIndex = i;
                }
                board.pop();
            }

            // only update best move if entire level searched
            bestMove = iterBestIndex;

#ifdef DEBUG
            std::cout << "best move for level " << level << ": " << moves[bestMove].uci()
                << " " << iterBestEval << std::endl;
            std::cout << "num positions searched: " << numSearched << std::endl;
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
            board.pop();
        }
    }
#ifdef DEBUG
    std::cout << "Number of positions searched: " << numSearched << std::endl;
#endif
    return moves[bestMove];
}

// DFS negamax
// with "full" search of forced moves (capture or check)
int Search::alphaBeta(int counter, int depth, int alpha, int beta)
{
    timer.checkOutOfTime(depth);
#ifdef DEBUG
    numSearched += 1;
#endif

    // Search stop: game over
    if (board.is_game_over(true))
    {
        return eval.evaluate(board.turn);
    }

    // currently performing QUIESCENCE SEARCH (i.e. searching down forced moves after a capture)
    if (counter < 0) {
        // For quiescence search, we want to calculate static evaluation at every node
        // to do some alpha beta pruning
        int value = eval.evaluate(board.turn);
        if (value >= beta)
        {
            return beta;
        }
        if (value > alpha)
        {
            alpha = value;
        }
    }

    // check if there are any forced captures
    std::vector<chess::Move> moves = board.generate_legal_captures();
    if (moves.empty()) // no forced captures
    {
        // no forced captures && not check => not forced move
        // counter <= 0 so search depth reached, stop
        if (!board.is_check() && counter <= 0)
        {
            return eval.evaluate(board.turn);
        }

        // if didn't stop, move set is all legal moves
        moves = board.generate_legal_moves();
    }

    // TODO: move ordering

    // DFS backtrack search: play move, recurse, unplay move
    for (auto &move : moves)
    {
        board.push(move); // play move

//#ifdef DEBUG
//        std::cout << move.uci() << " " << counter << " ";
//#endif
        // recurse
        int childScore = -alphaBeta(counter - 1, depth + 1, -beta, -alpha);

        board.pop(); // un play move

        // alpha-beta pruning
        if (childScore >= beta)
        {
            return beta;
        }

        if (childScore > alpha)
        {
            alpha = childScore;
        }
    }
    return alpha;
}
