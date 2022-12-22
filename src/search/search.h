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
    chess::Color myColor;
    int quiesce(int counter, int moves_pushed, int alpha, int beta);
    int alphaBeta(int counter, int moves_pushed, int alpha, int beta);
    void orderMovesByTT(std::vector<chess::Move> &moves);
    void orderMovesByMVVLVA(std::vector<chess::Move> &moves);
    void walkLine();

public:
    explicit Search(chess::Board &b, Timer &t, TranspositionTable &tt_obj, chess::Color myColor)
        : board(b), timer(t), tt_obj(tt_obj), eval(b), myColor(myColor) {};
    chess::Move best_move();
};

#endif // SEARCH_H