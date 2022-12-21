//
// Created by William Qin on 2022-10-11.
//

#include "evaluate.h"

#include "piece_tables.cpp"

// convention: black evaluates to negative in sub-methods until return in final evaluate

int Evaluate::material(bool &is_endgame) {
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
    
    int white_material = 0;

    white_material += ((int)wp.size()) * 100;
    white_material += ((int)wb.size()) * 300;
    white_material += ((int)wn.size()) * 300;
    white_material += ((int)wr.size()) * 500;
    white_material += ((int)wq.size()) * 900;

    int black_material = 0;
    
    black_material += ((int)bp.size()) * 100;
    black_material += ((int)bb.size()) * 300;
    black_material += ((int)bn.size()) * 300;
    black_material += ((int)br.size()) * 500;
    black_material += ((int)bq.size()) * 900;

    // 13 points of material or less (not including pawns)
    is_endgame = (white_material - ((int)wp.size()) * 100) <= 1300 && (black_material - ((int)bp.size()) * 100) <= 1300;

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
    if (board.is_game_over(true) || board.is_repetition(2)) {
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
        return -80; // we want to avoid draw
    }

    // rest of evaluate 
    bool is_endgame = false;
    int ret = material(is_endgame);
    //ret += mobility(is_endgame);
    ret += piece_positions(is_endgame);
    
    return ret * (color == chess::WHITE ? 1 : -1);
}


