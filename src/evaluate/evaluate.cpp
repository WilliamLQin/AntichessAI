//
// Created by William Qin on 2022-10-11.
//

#include "evaluate.h"

// convention: black evaluates to negative in sub-methods until return in final evaluate

int Evaluate::material() {
    int ret = 0;

    std::vector<chess::Square> wp = board.pieces(chess::PAWN, chess::WHITE);
    std::vector<chess::Square> bp = board.pieces(chess::PAWN, chess::BLACK);
    std::vector<chess::Square> wb = board.pieces(chess::BISHOP, chess::WHITE);
    std::vector<chess::Square> bb = board.pieces(chess::BISHOP, chess::BLACK);
    std::vector<chess::Square> wn = board.pieces(chess::KNIGHT, chess::WHITE);
    std::vector<chess::Square> bn = board.pieces(chess::KNIGHT, chess::BLACK);
    std::vector<chess::Square> wr = board.pieces(chess::ROOK, chess::WHITE);
    std::vector<chess::Square> br = board.pieces(chess::ROOK, chess::BLACK);
    std::vector<chess::Square> wq = board.pieces(chess::QUEEN, chess::WHITE);
    std::vector<chess::Square> bq = board.pieces(chess::QUEEN, chess::BLACK);
    std::vector<chess::Square> wk = board.pieces(chess::KING, chess::WHITE);
    std::vector<chess::Square> bk = board.pieces(chess::KING, chess::BLACK);
    
    ret += wp.size() * 10;
    ret += wb.size() * 29;
    ret += wn.size() * 31;
    ret += wr.size() * 50;
    ret += wq.size() * 90;
    
    ret -= bp.size() * 10;
    ret -= bb.size() * 29;
    ret -= bn.size() * 31;
    ret -= br.size() * 50;
    ret -= bq.size() * 90;

    return ret;
}

int Evaluate::mobility() {
    chess::Bitboard not_pawn_squares = chess::BB_ALL & ~board.pawns;

    int ret = 0;
    chess::Color prev_turn = board.turn;

    board.turn = chess::WHITE;
    std::vector<chess::Move> white_moves = board.generate_pseudo_legal_moves(not_pawn_squares);

    // TODO: adjust mobility weight of 0.5
    ret -= 0.5 * white_moves.size();

    board.turn = chess::BLACK;
    std::vector<chess::Move> black_moves = board.generate_pseudo_legal_moves(not_pawn_squares);

    // TODO: adjust mobility weight of 0.5
    ret += 0.5 * black_moves.size();

    board.turn = prev_turn;

    return ret;
}

int Evaluate::evaluate(chess::Color color) {
    
    // checkmate
    if (board.is_checkmate()) {
        if (board.turn == chess::WHITE) {
            if (color == chess::WHITE) {
                return EVAL_MIN;
            }
            else {
                return EVAL_MAX;
            }
        }
        else {
            if (color == chess::WHITE) {
                return EVAL_MAX;
            }
            else {
                return EVAL_MIN;
            }
        }
    }
    // stalemate
    if (board.is_stalemate()) {
        return 0;
    }

    int ret = material();
    ret += mobility();
    
    return ret * (color == chess::WHITE ? 1 : -1);
}


