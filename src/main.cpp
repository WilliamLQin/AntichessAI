#include <iostream>
#include <string>
#include <vector>
#include "cpp-chess/chess.h"
#include "search/search.h"

bool CLI_MODE = false;

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

    if (CLI_MODE) {
        std::cout << "Enter the AI's color: " << std::flush;
    }
    
    std::cin >> input;
    
    if (CLI_MODE) {
        std::cout << std::endl << "Starting board:" << std::endl;
        std::cout << std::string(board) << std::endl << std::endl;
    }
    
    // player makes a move first
    if (input == "black") {
        playerTurn(board);
    }

    while(!board.is_game_over()) {
        // AI MOVE
        chess::Move ai_move = search.best_move();
        board.push(ai_move);

        if (CLI_MODE) {
            std::cout << "Computer plays: " << std::flush;
        }
        std::cout << std::string(ai_move) << std::endl;
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

int main(int argc, char** argv) {
    srand(time(nullptr));

    if (argc > 1) {
        if (strcmp(argv[1], "cli") == 0) {
            CLI_MODE = true;
            std::cout << "Welcome to the CO456 Antichess AI" << std::endl;
        }
    }
    play_game();

    return 0;
}
