#include <iostream>
#include "Board/Board.h"
#include "cpp-chess/chess.h"

const int MAX_DEPTH = 6;

chess::Board board;

void traverse(int depth) {
    if (depth >= MAX_DEPTH) {
        return;
    }
    std::vector<chess::Move> moves = board.legal_moves();
    for (auto move : moves) {
        board.push(move);
        traverse(depth+1);
        board.pop();
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    Board b;
    b.hello();

    traverse(0);

    return 0;
}
