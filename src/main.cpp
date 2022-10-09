#include <iostream>
#include "cpp-chess/chess.h"

const int MAX_DEPTH = 3;

void traverse(int depth, chess::Board &board) {
    if (depth >= MAX_DEPTH) {
        return;
    }
    std::cout << "DEPTH: " << depth << std::endl;
    std::cout << board.fen() << std::endl << std::endl;
    std::vector<chess::Move> moves = board.legal_moves();
    for (auto move : moves) {
        board.push(move);
        traverse(depth+1, board);
        board.pop();
    }
}

int main() {
    std::cout << "Welcome to Antichess AI for CO 456" << std::endl;

    chess::Board board;
    chess::Board::captures_compulsory = true;

    traverse(0, board);

    return 0;
}
