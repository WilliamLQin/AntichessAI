#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "cpp-chess/chess.h"
#include "search/search.h"
#include "evaluate/evaluate.h"
#include "timer/timer.h"
#include "memoization/transposition_table.h"

void playerTurn(chess::Board& board, TranspositionTable &tt_obj) {
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
                    tt_obj.push(playerMove);
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

void play_game(std::string cli_input) {
    chess::Board::captures_compulsory = true; // this doesn't actually do anything
    chess::Board board;
    Timer timer;

    std::string input;

#ifdef CLI_MODE
    Evaluate evaluator(board);
#endif

    if (cli_input.empty()) {
#ifdef CLI_MODE
        std::cout << "Enter the AI's color: " << std::flush;
#endif
        std::cin >> input;
    }
    else {
#ifdef CLI_MODE
        std::cout << "Received color " << cli_input << " from command line." << std::endl;
#endif
        input = cli_input;
    }
    
#ifdef CLI_MODE
    std::cout << std::endl << "Starting board:" << std::endl;
    std::cout << std::string(board) << std::endl << std::endl;
#endif

    std::vector<chess::Move> openingWhite = { chess::Move::from_uci("h2h3"), chess::Move::from_uci("b2b3") };
    std::vector<chess::Move> openingBlack = { chess::Move::from_uci("h7h6"), chess::Move::from_uci("b7b6") };
    int openingIndex = 0;
    int TOTAL_OPENING_MOVES = 2;

    chess::Color color = (input == "black" ? chess::BLACK : chess::WHITE);

    TranspositionTable tt_obj(board);
    Search search(board, timer, tt_obj, color);
    
    // player makes a move first
    if (color == chess::BLACK) {
        playerTurn(board, tt_obj);
    }

    while(!board.is_game_over(true)) {
#ifdef CLI_MODE
        std::cout << std::endl << std::string(board) << std::endl << std::endl;
        std::cout << std::fixed << std::setprecision(2)
                  << "Evaluation: " << float(evaluator.evaluate(chess::WHITE)) / 100.0 << std::endl;
        system("read"); // MAC and LINUX ONLY
#endif

        // AI MOVE
        timer.startTurn();

        chess::Move ai_move = chess::Move::null();
        if (openingIndex < TOTAL_OPENING_MOVES)
        {
            ai_move = color == chess::WHITE ? openingWhite[openingIndex] : openingBlack[openingIndex];
            openingIndex += 1;
        }
        else
        {
            ai_move = search.best_move();
        }
        tt_obj.push(ai_move);

#ifdef CLI_MODE
        std::cout << "Computer plays: " << std::flush;
#endif
        std::cout << std::string(ai_move) << std::endl; // OUTPUT MOVE
        timer.endTurn();
        // END AI MOVE

#ifdef CLI_MODE
        std::cout << std::endl << std::string(board) << std::endl << std::endl;
        std::cout << std::fixed << std::setprecision(2)
                    << "Evaluation: " << float(evaluator.evaluate(chess::WHITE)) / 100.0 << std::endl;
        std::cout << std::fixed << std::setprecision(3)
                    << "Elapsed time: " << timer.getUsedTime() << std::endl;
#endif

        if (board.is_game_over(true)) {
            break;
        }

        // PLAYER MOVE
        playerTurn(board, tt_obj);
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

#ifdef LICHESS_MODE
    std::string cli_input("");
#else
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " ai_color" << std::endl;
        exit(1);
    }
    std::string cli_input(argv[1]);
#endif

    play_game(cli_input);

    return 0;
}
