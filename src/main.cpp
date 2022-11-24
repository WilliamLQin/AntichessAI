#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "cpp-chess/chess.h"
#include "search/search.h"
#include "evaluate/evaluate.h"

void playerTurn(chess::Board& board) {
    std::string input;
    std::vector<chess::Move> moves;

    moves = board.generate_legal_captures();
    if (moves.empty()) {
        moves = board.generate_legal_moves();
    }

#ifdef CLI_MODE
    std::cout << "Valid moves:";
    for (auto move: moves) {
        std::cout << " " << move.uci();
    }
    std::cout << std::endl;
#endif

    bool found = false;
    while(!found) {
#ifdef CLI_MODE
        std::cout << "Your move: " << std::flush;
#endif
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
#ifdef CLI_MODE
            std::cout << "Invalid move." << std::endl;
#else 
            std::cout << "invalid" << std::endl;
            exit(1);
#endif
        }
    }
}

void play_game() {
    chess::Board::captures_compulsory = true; // this doesn't actually do anything
    chess::Board board;

    Search search(board);

    std::string input;

#ifdef CLI_MODE
    Evaluate evaluator(board);
    std::cout << "Enter the AI's color: " << std::flush;
#endif
    
    std::cin >> input;
    
#ifdef CLI_MODE
    std::cout << std::endl << "Starting board:" << std::endl;
    std::cout << std::string(board) << std::endl << std::endl;
#endif
    
    // player makes a move first
    if (input == "black") {
        playerTurn(board);
    }

    while(!board.is_game_over(true)) {
        // AI MOVE
        chess::Move ai_move = search.best_move();
        board.push(ai_move);

#ifdef CLI_MODE
        std::cout << "Computer plays: " << std::flush;
#endif
        std::cout << std::string(ai_move) << std::endl;
#ifdef CLI_MODE
        std::cout << std::endl << std::string(board) << std::endl << std::endl;
        std::cout << std::fixed << std::setprecision(2) << "Evaluation: " << float(evaluator.evaluate(chess::WHITE)) / 100.0 << std::endl;
#endif

        if (board.is_game_over()) {
            break;
        }

        // PLAYER MOVE
        playerTurn(board);
    }

#ifdef CLI_MODE
    std::cout << std::endl << "Game over!" << std::endl;
    std::cout << std::string(board) << std::endl;
#endif
}

int main(int argc, char** argv) {
    srand(time(nullptr));

#ifdef CLI_MODE
    std::cout << "Welcome to the CO456 Antichess AI" << std::endl;
#endif
    play_game();

    return 0;
}
