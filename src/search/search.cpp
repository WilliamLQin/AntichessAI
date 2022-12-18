#include "search.h"
#include <iostream>
#include <vector>

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
    if (moves.size() == 1) {
        return moves[0];
    }

    // TODO: Move ordering

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
#ifdef DEBUG
            std::cout << std::endl << "Searching move " << moves[i].uci() << std::endl;
#endif
            // Do the rest of the search starting with this move
            int val = -negamax(level - 1, 1);

            if (val > iterBestEval)
            {
                iterBestEval = val;
                iterBestIndex = i;
            }
            board.pop();

            // OUT OF TIME, return best move (not from this search iteration)
            if (!timer.checkpoint()) {
                return moves[bestMove];
            }
        }

        // only update best move if entire level searched
        bestMove = iterBestIndex;
    }

    // will never reach here
    // return moves[bestMove];
}

// DFS negamax
// with "full" search of forced moves (capture or check)
int Search::negamax(int counter, int depth)
{
    // Search hard stop: forced move search depth exceeded or game over
    if (counter <= -10 || board.is_game_over(true)) {
        int value = eval.evaluate(board.turn);
#ifdef DEBUG
        std::cout << value << std::endl;
#endif
        return value;
    }

    // check if there are any forced captures
    std::vector<chess::Move> moves = board.generate_legal_captures();
    if (moves.empty()) // no forced captures
    {
        // no forced captures && not check => not forced move
        // counter <= 0 so search depth reached, stop
        if (!board.is_check() && counter <= 0)
        {
            int value = eval.evaluate(board.turn);
#ifdef DEBUG
            std::cout << value << std::endl;
#endif
            return value;
        }

        // if didn't stop, move set is all legal moves
        moves = board.generate_legal_moves();
    }

    // To get evaluation at current node, run this line of code outside play/unplay move
    // eval.evaluate(board.turn)

    // DFS backtrack search: play move, recurse, unplay move
    int max = EVAL_MIN;
    for (auto &move : moves)
    {
        board.push(move); // play move

        // To get evaluation at a child node, run this line of code between play/unplay move:
        // eval.evaluate(board.turn)

#ifdef DEBUG
        std::cout << move.uci() << " " << counter << " ";
#endif
        // recurse
        int score = -negamax(counter - 1, depth + 1);
        // reevaluate variables
        if (score > max) {
            max = score;
        }

        board.pop(); // un play move
    }
    return max;
}

// std::cout << std::endl << std::string(board) << std::endl;