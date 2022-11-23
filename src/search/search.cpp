#include "search.h"
#include <vector>
#include <iostream>

chess::Move Search::best_move()
{
    std::vector<chess::Move> moves;

    // negamax search
    int moveIndex = 0;
    int bestEval = -9999999;

    moves = board.generate_legal_captures();

    if (moves.empty())
    {
        moves = board.generate_legal_moves();
    }

    for (int i = 0; i < moves.size(); i++)
    {
        board.push(moves[i]);
        int val = -negamax(2, bestEval);

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
int Search::negamax(int depth, int current_eval)
{
    if (depth == 0)
        return eval.evaluate(board.turn);

    int max = -99999999;
    std::vector<chess::Move> moves = board.generate_legal_captures();
    bool moves_are_capture = true;
    bool current_player_in_check = false;

    if (moves.empty())
    {
        moves_are_capture = false;
        moves = board.generate_legal_moves();
    }

    for (auto &move : moves)
    {
        board.push(move);
        if (moves_are_capture || board.is_check())
        {
            int score = -negamax(depth, current_eval);
        }
        else
        {
            int score = -negamax(depth - 1, current_eval);
        }
        board.pop();
    }
    return max;
}

// std::cout << std::endl << std::string(board) << std::endl;