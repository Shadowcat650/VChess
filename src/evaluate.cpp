//
// Created by ShadowCat650 on 3/17/23.
//

#include "evaluate.h"

S8 evaluate_position(board state) {
    S8 totalPiecesWhite = countOnes(state.Board.WhitePieces);
    S8 white_material = countOnes(state.Board.WhitePawns);
    white_material += 3 * (countOnes(state.Board.WhiteKnights) + countOnes(state.Board.WhiteBishops));
    white_material += 5 * countOnes(state.Board.WhiteRooks);
    white_material += 9 * countOnes(state.Board.WhiteQueens);

    S8 totalPiecesBlack = countOnes(state.Board.BlackPieces);
    S8 black_material = countOnes(state.Board.BlackPawns);
    black_material += 3 * (countOnes(state.Board.BlackKnights) + countOnes(state.Board.BlackBishops));
    black_material += 5 * countOnes(state.Board.BlackRooks);
    black_material += 9 * countOnes(state.Board.BlackQueens);

    S8 whiteKingDistanceFromCenter = sqrt(pow((((63 - __builtin_ctzll(state.Board.WhiteKing)) / 8) - 3), 2) + pow((((63 - __builtin_ctzll(state.Board.WhiteKing)) % 8) - 4), 2));
    S8 blackKingDistanceFromCenter = sqrt(pow((((63 - __builtin_ctzll(state.Board.BlackKing)) / 8) - 4), 2) + pow((((63 - __builtin_ctzll(state.Board.BlackKing)) % 8) - 4), 2));

    // endgame eval
    if (totalPiecesWhite + totalPiecesBlack < 12) {
        return ((totalPiecesWhite - totalPiecesBlack) * 2) + ((whiteKingDistanceFromCenter - blackKingDistanceFromCenter) * 2) + (white_material - black_material);
    } else {
        S8 mobility = state.getMoveCount(COLOR::WHITE) - state.getMoveCount(COLOR::BLACK);
        //middlegame eval
        return ((totalPiecesWhite - totalPiecesBlack) / 4) + ((blackKingDistanceFromCenter - whiteKingDistanceFromCenter) / 2) + ((white_material - black_material) * 2) + (mobility / 3);
    }
}
