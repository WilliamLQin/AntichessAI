#include <iostream>
#include <stdlib.h>
#include "cpp-chess/chess.h"

const int MAX_DEPTH = 6;
const bool PRINT_INFO = false;

void traverse(int depth, chess::Board &board) {
    std::cout << "DEPTH: " << depth << std::endl;
    std::cout << std::string(board) << std::endl;
    if (depth >= MAX_DEPTH) {
        return;
    }
    std::vector<chess::Move> moves = board.legal_moves();
    for (auto move : moves) {
        board.push(move);
        traverse(depth+1, board);
        board.pop();
    }
}

void play_game() {
    chess::Board::captures_compulsory = true;
    chess::Board board("1r3r2/7p/2k5/8/3K3p/8/p7/8 w - - 0 1");

    std::string input;
    std::vector<chess::Move> moves;

    while(true) {
        // AI MOVE
        moves = board.generate_legal_captures();
        if (moves.empty()) {
            moves = board.generate_legal_moves();
        }

        int moveIndex = rand() % moves.size();
        board.push(moves[moveIndex]);

        if (PRINT_INFO) {
            std::cout << "Computer plays: " << std::flush;
        }
        std::cout << std::string(moves[moveIndex]) << std::endl;

        if (PRINT_INFO) {
            std::cout << std::endl << std::string(board) << std::endl << std::endl;
        }

        if (board.is_game_over()) {
            break;
        }

        // PLAYER MOVE
        moves = board.generate_legal_captures();
        if (moves.empty()) {
            moves = board.generate_legal_moves();
        }

        if (PRINT_INFO) {
            std::cout << "Valid moves:";
            for (auto move: moves) {
                std::cout << " " << move.uci();
            }
            std::cout << std::endl;
        }

        bool found = false;
        while(!found) {
            if (PRINT_INFO) {
                std::cout << "Your move: " << std::flush;
            }
            std::cin >> input;

            try {
                chess::Move playerMove = chess::Move::from_uci(input);

                for (auto move : moves) {
                    if (move.uci() == playerMove.uci()) {
                        board.push(playerMove);
                        found = true;
                    }
                }
            } catch (...) {}

            if (!found && PRINT_INFO) {
                std::cout << "Invalid move." << std::endl;
            }
        }

        if (board.is_game_over()) {
            break;
        }
    }

    if (PRINT_INFO) {
        std::cout << std::endl << "Game over!" << std::endl;
        std::cout << std::string(board) << std::endl;
    }
}

int main() {
    srand(getpid());

//    std::cout << "Welcome to Antichess AI for CO 456" << std::endl;
//    chess::Board board;
//    traverse(0, board);

    play_game();

    return 0;
}