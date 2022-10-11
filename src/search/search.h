#ifndef SEARCH_H
#define SEARCH_H

#include "../cpp-chess/chess.h"

class Search {
    chess::Board &board;
public:
    explicit Search(chess::Board &b) : board(b) {};
    chess::Move best_move();
};

#endif // SEARCH_H