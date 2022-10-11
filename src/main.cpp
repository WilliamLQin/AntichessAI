#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "cpp-chess/chess.h"
#include "search/search.h"

const bool CLI_MODE = false;

void playerTurn(chess::Board& board) {
    std::string input;
    std::vector<chess::Move> moves;

    moves = board.generate_legal_captures();
    if (moves.empty()) {
        moves = board.generate_legal_moves();
    }

    if (CLI_MODE) {
        std::cout << "Valid moves:";
        for (auto move: moves) {
            std::cout << " " << move.uci();
        }
        std::cout << std::endl;
    }

    bool found = false;
    while(!found) {
        if (CLI_MODE) {
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

        if (!found) {
            if (CLI_MODE) {
                std::cout << "Invalid move." << std::endl;
            } else {
                std::cout << "invalid" << std::endl;
                exit(1);
            }
        }
    }
}

void play_game() {
    chess::Board::captures_compulsory = true; // this doesn't actually do anything
    chess::Board board;

    Search search(board);

    std::string input;
    std::vector<chess::Move> moves;

    if (CLI_MODE) {
        std::cout << "Starting board:" << std::endl;
        std::cout << std::string(board) << std::endl << std::endl;
    }

    std::cin >> input;

    // player makes a move first
    if (input == "black") {
        playerTurn(board);
    }

    while(!board.is_game_over()) {
        // AI MOVE
        moves = board.generate_legal_captures();
        if (moves.empty()) {
            moves = board.generate_legal_moves();
        }

        int moveIndex = rand() % moves.size();
        board.push(moves[moveIndex]);

        if (CLI_MODE) {
            std::cout << "Computer plays: " << std::flush;
        }
        std::cout << std::string(moves[moveIndex]) << std::endl;

        if (CLI_MODE) {
            std::cout << std::endl << std::string(board) << std::endl << std::endl;
        }

        if (board.is_game_over()) {
            break;
        }

        // PLAYER MOVE
        playerTurn(board);
    }

    if (CLI_MODE) {
        std::cout << std::endl << "Game over!" << std::endl;
        std::cout << std::string(board) << std::endl;
    }
}

int main() {
    srand(time(nullptr));

    play_game();

    return 0;
}
