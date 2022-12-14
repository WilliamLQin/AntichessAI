//
// Created by William Qin on 2022-12-20.
//

// piece tables from https://www.chessprogramming.org/Simplified_Evaluation_Function#Piece-Square_Tables
// positive val is good for player in question
// a1 is first array elem, flipped vertically from white's perspective

int piece_table_blank[64] = {
        0, 0, 0, 0, 0, 0, 0,0,
        0, 0, 0, 0, 0, 0, 0,0,
        0, 0, 0, 0, 0, 0, 0,0,
        0, 0, 0, 0, 0, 0, 0,0,
        0, 0, 0, 0, 0, 0, 0,0,
        0, 0, 0, 0, 0, 0, 0,0,
        0, 0, 0, 0, 0, 0, 0,0,
        0, 0, 0, 0, 0, 0, 0,0,
};

int piece_table_white_pawn_mid[64] = {
        0,  0,  0,  0,  0,  0,  0,  0, // a1, b1, ....
        5, 10, 20, 20, 20, 10, 10,  5, // a2, b2, ...
        10, 0, 0,  0,  0,  0,  0,  10,
        0,  0,  0,  0,  0,  0,  0,  0,
        10,  10, 10, 10, 10, 10,  10,  10,
        30, 30, 30, 30, 30, 30, 30, 30,
        50, 50, 50, 50, 50, 50, 50, 50,
        0,  0,  0,  0,  0,  0,  0,  0
};

int piece_table_white_pawn_end[64] = {
        0,  0,  0,  0,  0,  0,  0,  0, // a1, b1, ....
        0,  0,  0,  0,  0,  0,  0,  0,
        10, 10, 10,  10,  10,  10,  10,  10,
        20, 20, 20, 20, 20, 20, 20, 30,
        30, 30, 30, 30, 30, 30, 30, 30,
        50, 50, 50, 50, 50, 50, 50, 50,
        80, 80, 80, 80, 80, 80, 80, 80,
        0,  0,  0,  0,  0,  0,  0,  0
};

int piece_table_black_pawn_mid[64] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        50, 50, 50, 50, 50, 50, 50, 50,
        30, 30, 30, 30, 30, 30, 30, 30,
        10,  10, 10, 10, 10, 10,  10,  10,
        0,  0,  0,  0,  0,  0,  0,  0,
        10, 0, 0,  0,  0,  0,  0,  10,
        5, 10, 20, 20, 20, 10, 10,  5,
        0,  0,  0,  0,  0,  0,  0,  0
};

int piece_table_black_pawn_end[64] = {
        0,  0,  0,  0,  0,  0,  0,  0, // a1, b1, ....
        80, 80, 80, 80, 80, 80, 80, 80,
        50, 50, 50, 50, 50, 50, 50, 50,
        30, 30, 30, 30, 30, 30, 30, 30,
        20, 20, 20, 20, 20, 20, 20, 30,
        10, 10, 10,  10,  10,  10,  10,  10,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0
};

int piece_table_white_knight_end[64] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50
};

int piece_table_black_knight_end[64] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50
};

int piece_table_white_bishop[64] = {
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10, 10,  0,  0,  0,  0, 10,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -20,-10,-10,-10,-10,-10,-10,-20,
};

int piece_table_black_bishop[64] = {
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10, 10,  0,  0,  0,  0, 10,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -20,-10,-10,-10,-10,-10,-10,-20,
};

int piece_table_white_rook[64] = {
        0,  0,  0,  5,  5,  0,  0,  0,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        5, 10, 10, 10, 10, 10, 10,  5,
        0,  0,  0,  0,  0,  0,  0,  0,
};

int piece_table_black_rook[64] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        5, 10, 10, 10, 10, 10, 10,  5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        0,  0,  0,  5,  5,  0,  0,  0
};

int piece_table_white_queen[64] = {
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
};

int piece_table_black_queen[64] = {
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
};

int piece_table_white_king_mid[64] = {
        20, 30, 10,  0,  0, 10, 30, 20,
        20, 20,  -10,  -10,  -10,  -10, 20, 20,
        -10,-20,-20,-20,-20,-20,-20,-10,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30
};

int piece_table_black_king_mid[64] = {
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -10,-20,-20,-20,-20,-20,-20,-10,
        20, 20,  -10,  -10,  -10,  -10, 20, 20,
        20, 30, 10,  0,  0, 10, 30, 20
};

int piece_table_white_king_end[64] = {
        -50,-40,-30,-20,-20,-30,-40,-50,
        -30,-30,  0,  0,  0,  0,-30,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-20,-10,  0,  0,-10,-20,-30,
        -50,-30,-30,-30,-30,-30,-30,-50
};

int piece_table_black_king_end[64] = {
        -50,-40,-30,-20,-20,-30,-40,-50,
        -30,-20,-10,  0,  0,-10,-20,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-30,  0,  0,  0,  0,-30,-30,
        -50,-30,-30,-30,-30,-30,-30,-50
};

int* piece_table_white_mid[6] = {
        piece_table_white_pawn_mid,
        piece_table_blank,
        piece_table_white_bishop,
        piece_table_white_rook,
        piece_table_white_queen,
        piece_table_white_king_mid,
};

int* piece_table_black_mid[6] = {
        piece_table_black_pawn_mid,
        piece_table_blank,
        piece_table_black_bishop,
        piece_table_black_rook,
        piece_table_black_queen,
        piece_table_black_king_mid,
};

int* piece_table_white_end[6] = {
        piece_table_white_pawn_end,
        piece_table_white_knight_end,
        piece_table_white_bishop,
        piece_table_white_rook,
        piece_table_white_queen,
        piece_table_white_king_end,
};

int* piece_table_black_end[6] = {
        piece_table_black_pawn_end,
        piece_table_black_knight_end,
        piece_table_black_bishop,
        piece_table_black_rook,
        piece_table_black_queen,
        piece_table_black_king_end,
};

int** piece_table_mid[2] = {
        piece_table_black_mid,
        piece_table_white_mid,
};

int** piece_table_end[2] = {
        piece_table_black_end,
        piece_table_white_end,
};

int*** piece_table[2] = {
        piece_table_mid,
        piece_table_end,
};
