#ifndef SEARCH_H
#define SEARCH_H

#include "../cpp-chess/chess.h"
#include "../evaluate/evaluate.h"
#include "../timer/timer.h"
#include <vector>

class Search
{
    chess::Board &board;
    Timer &timer;
    Evaluate eval;
    int negamax(int counter, int depth);

public:
    explicit Search(chess::Board &b, Timer &t) : board(b), timer(t), eval(b) {};
    chess::Move best_move();
};

#endif // SEARCH_H