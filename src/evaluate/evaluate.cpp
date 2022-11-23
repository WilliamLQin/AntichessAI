//
// Created by William Qin on 2022-10-11.
//

#include "evaluate.h"

int Evaluate::evaluate(chess::Color color) {
    
    // checkmate
    if (this->board.is_checkmate()) {
        if (this->board.turn == chess::WHITE) {
            if (color == chess::WHITE) {
                return INT_MIN;
            }
            else {
                return INT_MAX;
            }
        }
        else {
            if (color == chess::WHITE) {
                return INT_MAX;
            }
            else {
                return INT_MIN;
            }
        }
    }

    // else, count material
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
    ret += wk.size() * 500;
    
    ret -= bp.size() * 10;
    ret -= bb.size() * 29;
    ret -= bn.size() * 31;
    ret -= br.size() * 50;
    ret -= bq.size() * 90;
    ret -= bk.size() * 500;
    
    return ret * (color == chess::WHITE ? 1 : -1);
}
