#ifndef SEARCH_H
#define SEARCH_H

#include "../cpp-chess/chess.h"
#include "../evaluate/evaluate.h"
#include <vector>

class Search
{
    chess::Board &board;
    Evaluate eval;
    int negamax(int depth, int current_eval);

public:
    explicit Search(chess::Board &b) : board(b), eval(b){};
    chess::Move best_move();
};

#endif // SEARCH_H