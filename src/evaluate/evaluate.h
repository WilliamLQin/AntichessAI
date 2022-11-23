//
// Created by William Qin on 2022-10-11.
//

#ifndef ANTICHESSAI_EVALUATE_H
#define ANTICHESSAI_EVALUATE_H

#include "../cpp-chess/chess.h"
#include <limits.h>

class Evaluate {
    chess::Board &board;
public:
    explicit Evaluate(chess::Board &b) : board(b) {};
    int evaluate(chess::Color);
private:
    int material();
    int mobility();
};

#endif //ANTICHESSAI_EVALUATE_H
