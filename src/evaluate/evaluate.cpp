//
// Created by William Qin on 2022-10-11.
//

#include "evaluate.h"

#include "piece_tables.cpp"

int bit_table[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};

int countSetBits(unsigned long long int n)
{
    return (bit_table[n & 0xff] +
            bit_table[(n >> 8) & 0xff] +
            bit_table[(n >> 16) & 0xff] +
            bit_table[(n >> 24) & 0xff] +
            bit_table[(n >> 32) & 0xff] +
            bit_table[(n >> 40) & 0xff] +
            bit_table[(n >> 48) & 0xff] +
            bit_table[(n >> 56) & 0xff]);
}

#include <iostream>

// convention: black evaluates to negative in sub-methods until return in final evaluate

int Evaluate::material(bool &is_endgame) {
    int ret = 0;

    int white_material = 0;

    white_material += (countSetBits(board.bishops & board.occupied_co[chess::WHITE])) * 300;
    white_material += (countSetBits(board.knights & board.occupied_co[chess::WHITE])) * 300;
    white_material += (countSetBits(board.rooks & board.occupied_co[chess::WHITE])) * 500;
    white_material += (countSetBits(board.queens & board.occupied_co[chess::WHITE])) * 900;

    int black_material = 0;

    black_material += (countSetBits(board.bishops & board.occupied_co[chess::BLACK])) * 300;
    black_material += (countSetBits(board.knights & board.occupied_co[chess::BLACK])) * 300;
    black_material += (countSetBits(board.rooks & board.occupied_co[chess::BLACK])) * 500;
    black_material += (countSetBits(board.queens & board.occupied_co[chess::BLACK])) * 900;

    // 13 points of material or less (not including pawns)
    is_endgame = white_material <= 1300 && black_material <= 1300;

    white_material += (countSetBits(board.pawns & board.occupied_co[chess::WHITE])) * 100;
    black_material += (countSetBits(board.pawns & board.occupied_co[chess::BLACK])) * 100;

    ret = white_material - black_material;

    return ret;
}

int Evaluate::piece_positions(const bool &is_endgame) { // TODO: is_endgame
    int ret = 0;
    for (auto square: chess::SQUARES) {
        std::optional<chess::Piece> piece_at_square = board.piece_at(square);
        if (piece_at_square != std::nullopt) {
            ret += (piece_at_square->color == chess::WHITE ? 1 : -1)
                    * piece_table[is_endgame][piece_at_square->color][piece_at_square->piece_type - 1][square];
        }
    }

    return ret;
}

int Evaluate::mobility(const bool &is_endgame) {
    chess::Bitboard not_pawn_squares = chess::BB_ALL & ~board.pawns;

    int ret = 0;
    chess::Color prev_turn = board.turn;

    board.turn = chess::WHITE;
    std::vector<chess::Move> white_moves = board.generate_pseudo_legal_moves(not_pawn_squares);

    // TODO: adjust mobility weight of 5
    int mobility_weight = is_endgame ? 5 : -5;

    ret += mobility_weight * white_moves.size();

    board.turn = chess::BLACK;
    std::vector<chess::Move> black_moves = board.generate_pseudo_legal_moves(not_pawn_squares);

    ret -= mobility_weight * black_moves.size();

    board.turn = prev_turn;

    return ret;
}

int Evaluate::evaluate(chess::Color color) {
    
    // game over
    if (board.is_game_over(true)) {
        if (board.is_checkmate()) {
            if (board.turn == chess::WHITE) {
                if (color == chess::WHITE) {
                    return EVAL_MIN; // white lost, we are white
                } else {
                    return EVAL_MAX; // white lost, we are black
                }
            } else {
                if (color == chess::WHITE) {
                    return EVAL_MAX; // black lost, we are white
                } else {
                    return EVAL_MIN; // black lost, we are black
                }
            }
        }
        // draw
        return 0;
    }

    // rest of evaluate 
    bool is_endgame = false;
    int ret = material(is_endgame);
    //ret += mobility(is_endgame);
    ret += piece_positions(is_endgame);
    
    return ret * (color == chess::WHITE ? 1 : -1);
}


