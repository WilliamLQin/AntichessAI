//
// Created by William Qin on 2022-10-11.
//

#include <iostream>
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

int Evaluate::piece_positions(const bool &is_endgame) {
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

int Evaluate::check_file_for_pawns(chess::Square pawn_starting_square, chess::Square king_square, chess::Color color) {
    // positive points here = good, regardless of player
    // +300 for each pawn 1-2 squares forward from the king 
    // -100 for each pawn more than 2 squares foward from the king
    // +50 for each pawn beside or 1 step behind the king
    // +0 for each pawn more than 1 step behind the king
    // -200 for any missing pawn that doesn't open file where king is
    // -300 for any missing pawn that creates open file where king is

    int ret = 0;
    int squares_forward_from_king = 1;
    bool pawn_found = 0;
    chess::Square pawn_square = pawn_starting_square;
    std::optional<chess::Piece> piece_at_square;
    if (color == chess::WHITE) {
        while (pawn_square < 56) { // check forwards, before last rank
            piece_at_square = board.piece_at(pawn_square);
            if (piece_at_square != std::nullopt && piece_at_square->piece_type == 1 && piece_at_square->color == chess::WHITE) {
                if (squares_forward_from_king <= 2) {
                    ret += 300;
                }
                else {
                    ret -= 100;
                }
                pawn_found = 1;
                break;
            }
            squares_forward_from_king++;
            pawn_square += 8; // next square forward
        }
        if (!pawn_found) { // check backwards until 2nd rank
            pawn_square = pawn_starting_square - 8;
            squares_forward_from_king = 0;
            while (pawn_square >= 8) {
                piece_at_square = board.piece_at(pawn_square);
                if (piece_at_square != std::nullopt && piece_at_square->piece_type == 1 && piece_at_square->color == chess::WHITE) {
                    if (squares_forward_from_king >= -1) {
                        ret += 50;
                    }
                    else {
                        ret += 0;
                    }
                    pawn_found = 1;
                    break;
                }
                squares_forward_from_king--;
                pawn_square -= 8; // next square backward
            }
        }
        if (!pawn_found) { // missing pawn 
            if (pawn_starting_square % 8 != king_square % 8) {  // doesn't create open file where king is
                ret -= 200;
            }
            else { // creates open file where king is
                ret -= 300;
            }
        }
    }
    else { // black
        while (pawn_square >= 8) { // before last rank
            piece_at_square = board.piece_at(pawn_square);
            if (piece_at_square != std::nullopt && piece_at_square->piece_type == 1 && piece_at_square->color == chess::BLACK) {
                if (squares_forward_from_king <= 2) {
                    ret += 300;
                }
                else {
                    ret -= 100;
                }
                pawn_found = 1;
                break;
            }
            squares_forward_from_king++;
            pawn_square -= 8; // next square forward
        }
        if (!pawn_found) { // check backwards until 2nd rank
            pawn_square = pawn_starting_square + 8;
            squares_forward_from_king = 0;
            while (pawn_square < 56) {
                piece_at_square = board.piece_at(pawn_square);
                if (piece_at_square != std::nullopt && piece_at_square->piece_type == 1 && piece_at_square->color == chess::BLACK) {
                    if (squares_forward_from_king >= -1) {
                        ret += 50;
                    }
                    else {
                        ret += 0;
                    }
                    pawn_found = 1;
                    break;
                }
                squares_forward_from_king--;
                pawn_square += 8; // next square backward
            }
        }
        if (!pawn_found) { // missing pawn
            if (pawn_starting_square % 8 != king_square % 8) {  // doesn't create open file where king is
                ret -= 200;
            }
            else { // creates open file where king is
                ret -= 300;
            }
        }
    }
    return ret;
}

/* 
pawn shield after castle
consider the pawns closest to the king in the 3 files to the left, right, and where the king is (use closest pawns to avoid counting doubled pawns)
*/
int Evaluate::pawn_shield() {
    int ret = 0;
    chess::Bitboard white_pawns = board.pieces_mask(1, chess::WHITE);
    chess::Bitboard black_pawns = board.pieces_mask(1, chess::BLACK);
    std::optional<chess::Square> white_king = board.king(chess::WHITE);
    std::optional<chess::Square> black_king = board.king(chess::BLACK);

    if (white_king != std::nullopt && black_king != std::nullopt) {
        chess::Square white_king_square = white_king.value();
        chess::Square black_king_square = black_king.value();

        // assumes a side only gets/loses points if they've castled
        if (board.has_castled[chess::WHITE]) {
            // check pawn structure as far as king on 3rd last rank
            if (white_king_square >= 0 && white_king_square < 48) {
                chess::Square pawn_starting_square = -1;
                if (white_king_square % 8 != 0) {
                    // check closest pawn in left file from king
                    pawn_starting_square = white_king_square + 7; // square immediately forward to the left
                    ret += check_file_for_pawns(pawn_starting_square, white_king_square, chess::WHITE);
                }
                // check closest pawn in center file where king is
                pawn_starting_square = white_king_square + 8; // square immediately forward
                ret += check_file_for_pawns(pawn_starting_square, white_king_square, chess::WHITE);
                if (white_king_square % 8 != 7) {
                    // check closest pawn in right file from king
                    pawn_starting_square = white_king_square + 9; // square immediately forward to the right
                    ret += check_file_for_pawns(pawn_starting_square, white_king_square, chess::WHITE);
                }
            }
        }
        if (board.has_castled[chess::BLACK]) {
            // check pawn structure as far as king on 3rd last rank
            if (black_king_square >= 16) {
                chess::Square pawn_starting_square = -1;
                if (black_king_square % 8 != 7) {
                    // check closest pawn in left file from king
                    pawn_starting_square = black_king_square - 7; // square immediately forward to the left
                    ret -= check_file_for_pawns(pawn_starting_square, black_king_square, chess::BLACK);
                }
                // check closest pawn in center file where king is
                pawn_starting_square = black_king_square - 8; // square immediately forward
                ret -= check_file_for_pawns(pawn_starting_square, black_king_square, chess::BLACK);
                if (black_king_square % 8 != 0) {
                    // check closest pawn in right file from king
                    pawn_starting_square = black_king_square - 9; // square immediately forward to the right
                    ret -= check_file_for_pawns(pawn_starting_square, black_king_square, chess::BLACK);
                }
            }
        }
    }
    return ret;
}

int Evaluate::king_safety() {
    int ret = 0;
    ret += pawn_shield();
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
    ret += king_safety();
    
    return ret * (color == chess::WHITE ? 1 : -1);
}


