//
// Created by William Qin on 2022-12-17.
//

#include "transposition_table.h"

#include "zobrist_hashes.cpp"

TranspositionTable::TranspositionTable(chess::Board &b) : board(b), hashStack(10)
{
    // Allocate tt on heap if needed
    tt = new struct TTEntry[TT_SIZE];

    // initialize current hash
    computeHashFromScratch();
    hashStack.push_back(currentHash);
}

void TranspositionTable::computeHashFromScratch() {
    currentHash = 0;
    for (auto square: chess::SQUARES) {
        std::optional<chess::Piece> piece_at_square = board.piece_at(square);
        if (piece_at_square != std::nullopt) {
            currentHash ^= getHashForPieceOnSquare(piece_at_square->color, piece_at_square->piece_type, square);
        }
    }
    currentHash ^= getHashForSideToMove(board.turn);
    currentHash ^= getHashForCastlingRights(board.castling_rights);
    currentHash ^= getHashForEnPassant(board.ep_square);
}

// BEFORE pushing a move to the board, call this to update the zobrist hash
void TranspositionTable::push(chess::Move m)
{
    // If special case, just reevaluate the hash
    if (board.is_en_passant(m) || board.is_castling(m)) {
        board.push(m);
        computeHashFromScratch();
        hashStack.push_back(currentHash);
        return;
    }

    // In normal circumstances, if capture occurs, to_piece will exist and needs to be cleared
    // In all circumstances, from_square will move to to_square
    std::optional<chess::Piece> from_piece = board.piece_at(m.from_square);
    std::optional<chess::Piece> to_piece = board.piece_at(m.to_square);
    if (to_piece != std::nullopt) { // capture occurs
        currentHash ^= getHashForPieceOnSquare(to_piece->color, to_piece->piece_type, m.to_square);
    }
    if (from_piece != std::nullopt) { // movement of piece
        currentHash ^= getHashForPieceOnSquare(from_piece->color, from_piece->piece_type, m.from_square);
        currentHash ^= getHashForPieceOnSquare(from_piece->color, from_piece->piece_type, m.to_square);
    }

    currentHash ^= getHashForSideToMove(board.turn);
    currentHash ^= getHashForCastlingRights(board.castling_rights);
    currentHash ^= getHashForEnPassant(board.ep_square);

    board.push(m);

    currentHash ^= getHashForSideToMove(board.turn);
    currentHash ^= getHashForCastlingRights(board.castling_rights);
    currentHash ^= getHashForEnPassant(board.ep_square);

    hashStack.push_back(currentHash);
}

// pop a move to the transposition table to update the zobrist hash
void TranspositionTable::pop()
{
    hashStack.pop_back();
    currentHash = hashStack.back();

    board.pop();
}

// cache an evaluation
void TranspositionTable::storeEval(int eval, int depth, char nodeType, const char* bestResponse)
{
    // Always replace policy
    tt[currentHash % TT_SIZE].key = currentHash;
    tt[currentHash % TT_SIZE].eval = eval;
    tt[currentHash % TT_SIZE].depth = depth;
    tt[currentHash % TT_SIZE].nodeType = nodeType;
    memcpy(tt[currentHash % TT_SIZE].move_uci, bestResponse, 7);
}

// load the current board's evaluation
std::optional<TranspositionTable::TTEntry> TranspositionTable::loadEval()
{
    TTEntry ret = tt[currentHash % TT_SIZE];
    if (currentHash == ret.key)
    {
        return ret;
    }
    else
    {
        return std::nullopt;
    }
}
