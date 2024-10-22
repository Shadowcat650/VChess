//
// Created by ShadowCat650 on 3/4/23.
//

#ifndef VELOCITYCHESS_BOARD_H
#define VELOCITYCHESS_BOARD_H

#include "precompute.h"
#include "definitions.h"


struct ChessBoard {
    U64 WhitePawns;
    U64 WhiteKnights;
    U64 WhiteBishops;
    U64 WhiteRooks;
    U64 WhiteQueens;
    U64 WhiteKing;

    U64 BlackPawns;
    U64 BlackKnights;
    U64 BlackBishops;
    U64 BlackRooks;
    U64 BlackQueens;
    U64 BlackKing;

    U64 EnPassantTargets;

    U64 WhitePieces;
    U64 BlackPieces;
    U64 Pieces;

    bool WhiteKingside = true;
    bool WhiteQueenside = true;

    bool BlackKingside = true;
    bool BlackQueenside = true;

    U8 HalfMoveClock;
    int Move;

    COLOR Player = COLOR::WHITE;
};

struct Move {
    U64 positions; // (the starting position | the ending position)
    PIECE movingPiece;
    COLOR color;
    SIDES castle = SIDES::NONE;
    PIECE queen = PIECE::PAWN;
};

class board {
public:
    ChessBoard Board;

    bool makeMove(Move move);

    void loadPosition(string FEN);

    U8 getMoveCount(COLOR color);

    void toStart();

    void printGame();

    U64 getPieceMoves(PIECE piece, U64 location, COLOR color);

    U64 generateAttackMap(COLOR color);

    U64 getPawnAttacks(COLOR color);

    string getFEN(bool includeData);

private:

    void _clearBoard();

    U64 _getPawnMoves(U64 location, COLOR color) const;
    U64 _getKnightMoves(U64 location, COLOR color) const;
    U64 _getBishopMoves(U64 location, COLOR color) const;
    U64 _getRookMoves(U64 location, COLOR color) const;
    U64 _getQueenMoves(U64 location, COLOR color);
    U64 _getKingMoves(U64 location, COLOR color) const;

    void _makeCaptureMove(U64 positions, COLOR color);

    void _promoteWhitePawn(U64 positions, PIECE piece);
    void _promoteBlackPawn(U64 positions, PIECE piece);

    bool _castle(COLOR color, SIDES side);
};


#endif //VELOCITYCHESS_BOARD_H
