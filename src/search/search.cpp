#include "search.h"
#include <iostream>
#include <vector>

chess::Move Search::best_move()
{
    std::vector<chess::Move> moves;

    // negamax search
    int moveIndex = 0;
    int bestEval = EVAL_MIN;
    int searchCounter = 2; // search 2 ply

    moves = board.generate_legal_captures();

    if (moves.empty())
    {
        moves = board.generate_legal_moves();
    }

    for (int i = 0; i < moves.size(); i++)
    {
        board.push(moves[i]);
#ifdef DEBUG
        std::cout << std::endl << "Searchinag move " << moves[i].uci() << std::endl;
#endif
        int val = -negamax(searchCounter - 1, 1);

        if (val > bestEval)
        {
            bestEval = val;
            moveIndex = i;
        }
        board.pop();
    }

    return moves[moveIndex];
}

// simple dfs negamax algorithm, pretty inefficient
int Search::negamax(int counter, int depth)
{
    if (counter <= -10) {
        int value = eval.evaluate(board.turn);
#ifdef DEBUG
        std::cout << value << std::endl;
#endif
        return value;
    }

    int max = EVAL_MIN;
    std::vector<chess::Move> moves = board.generate_legal_captures();

    if (moves.empty())
    {
        if (!board.is_check()) // not a forced move
        {
            if (counter <= 0) {
                int value = eval.evaluate(board.turn);
#ifdef DEBUG
                std::cout << value << std::endl;
#endif
                return value;
            }
        }
        moves = board.generate_legal_moves();
    }

    for (auto &move : moves)
    {
        board.push(move);
#ifdef DEBUG
        std::cout << move.uci() << " " << counter << " ";
#endif
        int score = -negamax(counter - 1, depth + 1);
        if (score > max) {
            max = score;
        }
        board.pop();
    }
    return max;
}

// std::cout << std::endl << std::string(board) << std::endl;