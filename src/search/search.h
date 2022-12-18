#ifndef SEARCH_H
#define SEARCH_H

#include "../cpp-chess/chess.h"
#include "../evaluate/evaluate.h"
#include "../timer/timer.h"
#include "../memoization/transposition_table.h"
#include <vector>

class Search
{
    chess::Board &board;
    Timer &timer;
    TranspositionTable &tt_obj;
    Evaluate eval;
    int alphaBeta(int counter, int depth, int alpha, int beta);
    void walkLine();

public:
    explicit Search(chess::Board &b, Timer &t, TranspositionTable &tt_obj)
        : board(b), timer(t), tt_obj(tt_obj), eval(b){};
    chess::Move best_move();
};

#endif // SEARCH_H