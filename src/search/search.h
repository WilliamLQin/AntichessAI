#ifndef SEARCH_H
#define SEARCH_H

#include "../cpp-chess/chess.h"

class Search {
    chess::Board &board;
public:
    Search(chess::Board &b) : board(b) {};
};


#endif // SEARCH_H