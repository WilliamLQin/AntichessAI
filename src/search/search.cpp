#include "search.h"
#include <vector>
#include <iostream>

chess::Move Search::best_move() {
    std::vector<chess::Move> moves;
    
    moves = board.generate_legal_captures();
    if (moves.empty()) {
        moves = board.generate_legal_moves();
    }

    // negamax search
    int moveIndex = 0;
    int bestEval = -9999999;
    for (int i = 0; i < moves.size(); i++) {
        board.push(moves[i]);
        int val = -negamax(3);
        if (val > bestEval) {
            bestEval = val;
            moveIndex = i;
        }
        board.pop();
    }
    
    return moves[moveIndex];
}

// simple dfs negamax algorithm, pretty inefficient
int Search::negamax(int depth) {
    if (depth == 0) {
        return eval.evaluate(board.turn);
    }
    std::vector<chess::Move> moves = board.generate_legal_captures();
    if (moves.empty()) {
        moves = board.generate_legal_moves();
    }
    
    int max = -99999999;
    for (auto & move : moves) {
        board.push(move);
        int score = -negamax(depth - 1);
        if (score > max) {
            max = score;
        }
        board.pop();
    }
    return max;
}
