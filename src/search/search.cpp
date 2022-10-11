#include "search.h"
#include <cstdlib>
#include <vector>

chess::Move Search::best_move() {
    std::vector<chess::Move> moves;
    
    moves = board.generate_legal_captures();
    if (moves.empty()) {
        moves = board.generate_legal_moves();
    }

    // randomly select
    int moveIndex = rand() % moves.size();
    
    return moves[moveIndex];
}