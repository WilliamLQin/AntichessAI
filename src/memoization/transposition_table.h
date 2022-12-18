//
// Created by William Qin on 2022-12-17.
//

#ifndef ANTICHESSAI_TRANSPOSITION_TABLE_H
#define ANTICHESSAI_TRANSPOSITION_TABLE_H

#include "../cpp-chess/chess.h"

#define TT_EXACT 'p'

// Alpha = All node, upper bound
#define TT_ALPHA 'a'

// Beta = Cut node, lower bound
#define TT_BETA 'b'

class TranspositionTable
{
public:
    struct TTEntry {
        unsigned long long key;
        int eval;
        int depth;
        char nodeType;
        char move_uci[7];
    };
private:
    constexpr static int TT_SIZE = 16777216; // 2^24
    chess::Board &board;
    unsigned long long int currentHash = 0;
    struct TTEntry* tt;
    std::vector<unsigned long long int> hashStack;

    void computeHashFromScratch();
public:

    TranspositionTable(chess::Board &b);
    // REPLACES board.push(m): push move and update the zobrist hash
    void push(chess::Move m);
    // REPLACES board.pop(m): pop a move to restore the zobrist hash from the stack
    void pop();
    // cache an evaluation
    void storeEval(int eval, int depth, char nodeType, const char* bestResponse);
    // load the current board's evaluation
    std::optional<TranspositionTable::TTEntry> loadEval();
};


#endif //ANTICHESSAI_TRANSPOSITION_TABLE_H
