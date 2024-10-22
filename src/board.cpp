//
// Created by ShadowCat650 on 3/4/23.
//

#include "board.h"

bool board::makeMove(Move move) {
    (Board.Player == COLOR::WHITE) ? Board.Player = COLOR::BLACK : Board.Player = COLOR::WHITE;
    if (move.castle != SIDES::NONE) {
        return _castle(move.color, move.castle);
    }
    if (move.color == COLOR::WHITE) {
        switch (move.movingPiece) {
            case PAWN:
                Board.HalfMoveClock = 0;
                if ((Board.EnPassantTargets & move.positions) != 0) {
                    Board.BlackPawns ^= Board.EnPassantTargets << 8;
                    Board.BlackPieces ^= Board.EnPassantTargets << 8;
                }
                Board.EnPassantTargets = 0;
                if ((move.positions & 0xFF00000000ULL) != 0 && (move.positions & 0xFF000000000000ULL) != 0) {
                    Board.EnPassantTargets = (move.positions & 0xFF000000000000ULL) >> 8;
                }
                if (move.queen != PIECE::PAWN) {
                    Board.WhitePawns ^= (move.positions & 0xff00ULL);
                    _promoteWhitePawn(move.positions, move.queen);
                    break;
                } else {
                    Board.WhitePawns ^= move.positions;
                }
                break;
            case KNIGHT:
                Board.WhiteKnights ^= move.positions;
                break;
            case BISHOP:
                Board.WhiteBishops ^= move.positions;
                break;
            case ROOK:
                if ((move.positions & 0x8000000000000000ULL) != 0 && (Board.WhiteRooks & 0x8000000000000000ULL) != 0) {
                    Board.WhiteQueenside = false;
                }
                if ((move.positions & 0x100000000000000ULL) != 0 && (Board.WhiteRooks & 0x100000000000000ULL) != 0) {
                    Board.WhiteKingside = false;
                }
                Board.WhiteRooks ^= move.positions;
                break;
            case QUEEN:
                Board.WhiteQueens ^= move.positions;
                break;
            case KING:
                if ((Board.WhiteKing & 0x800000000000000ULL) != 0) {
                    Board.WhiteKingside = false;
                    Board.WhiteQueenside = false;
                }
                Board.WhiteKing ^= move.positions;
                break;
        }
        if (move.movingPiece != PIECE::PAWN) {
            Board.EnPassantTargets = 0;
        }
        Board.WhitePieces ^= move.positions;
        if ((Board.BlackPieces & move.positions) != 0) {
            _makeCaptureMove(move.positions, COLOR::BLACK);
            Board.HalfMoveClock = 0;
        } else {
            if (move.movingPiece != PIECE::PAWN) {
                Board.HalfMoveClock++;
            }
        }
        Board.Pieces = Board.WhitePieces | Board.BlackPieces;
        if ((generateAttackMap(COLOR::BLACK) & Board.WhiteKing) != 0) { // if king is in check, return false to indicate invalid move
            return false;
        } else {
            return true;
        }
    } else {
        Board.Move++;
        switch (move.movingPiece) {
            case PAWN:
                if ((Board.EnPassantTargets & move.positions) != 0) {
                    Board.WhitePawns ^= Board.EnPassantTargets >> 8;
                    Board.WhitePieces ^= Board.EnPassantTargets >> 8;
                }
                Board.EnPassantTargets = 0;
                if ((move.positions & 0xFF000000ULL) != 0 && (move.positions & 0xFF00ULL) != 0) {
                    Board.EnPassantTargets = (move.positions & 0xFF000000ULL) >> 8;
                }
                if (move.queen != PIECE::PAWN) {
                    Board.BlackPawns ^= (move.positions & 0xff000000000000ULL);
                    _promoteBlackPawn(move.positions, move.queen);
                    break;
                } else {
                    Board.BlackPawns ^= move.positions;
                }
                break;
            case KNIGHT:
                Board.BlackKnights ^= move.positions;
                break;
            case BISHOP:
                Board.BlackBishops ^= move.positions;
                break;
            case ROOK:
                Board.BlackRooks ^= move.positions;
                if ((move.positions & 0x80ULL) != 0 && (Board.WhiteRooks & 0x80ULL) != 0) {
                    Board.BlackQueenside = false;
                }
                if ((move.positions & 0x1ULL) != 0 && (Board.WhiteRooks & 0x1ULL) != 0) {
                    Board.BlackKingside = false;
                }
                break;
            case QUEEN:
                Board.BlackQueens ^= move.positions;
                break;
            case KING:
                if ((Board.BlackKing & 0x8ULL) != 0) {
                    Board.BlackKingside = false;
                    Board.BlackQueenside = false;
                }
                Board.BlackKing ^= move.positions;
                break;
        }
        if (move.movingPiece != PIECE::PAWN) {
            Board.EnPassantTargets = 0;
        }
        Board.BlackPieces ^= move.positions;
        if ((Board.WhitePieces & move.positions) != 0) {
            _makeCaptureMove(move.positions, COLOR::WHITE);
        } else {
            if (move.movingPiece != PIECE::PAWN) {
                Board.HalfMoveClock++;
            }
        }
        Board.Pieces = Board.WhitePieces | Board.BlackPieces;
        if ((generateAttackMap(COLOR::WHITE) & Board.BlackKing) != 0) { // if king is in check, return false to indicate invalid move
            return false;
        } else {
            return true;
        }
    }
}

bool board::_castle(COLOR color, SIDES side) {
    Board.EnPassantTargets = 0;
    if (color == COLOR::WHITE) {
        if (side == SIDES::KINGSIDE) {
            if ((Board.Pieces & 0x600000000000000ULL) == 0) {
                if ((Board.WhiteRooks & 0x100000000000000ULL) != 0) {
                    if ((generateAttackMap(COLOR::BLACK) & 0xe00000000000000ULL) == 0) {
                        Board.WhiteKing >>= 2;
                        Board.WhiteRooks ^= 0x500000000000000ULL;
                        Board.WhitePieces ^= 0xF00000000000000ULL;
                        Board.Pieces ^= 0xF00000000000000ULL;
                        Board.WhiteKingside = false;
                        Board.WhiteQueenside = false;
                        return true;
                    }
                }
            }
        } else {
            if ((Board.Pieces & 0x7000000000000000ULL) == 0) {
                if ((Board.WhiteRooks & 0x8000000000000000ULL) != 0) {
                    if ((generateAttackMap(COLOR::BLACK) & 0x3800000000000000ULL) == 0) {
                        Board.WhiteKing <<= 2;
                        Board.WhiteRooks ^= 0x9000000000000000ULL;
                        Board.WhitePieces ^= 0xB800000000000000ULL;
                        Board.Pieces ^= 0xB800000000000000ULL;
                        Board.WhiteKingside = false;
                        Board.WhiteQueenside = false;
                        return true;
                    }
                }
            }
        }
    } else {
        if (side == SIDES::KINGSIDE) {
            if ((Board.Pieces & 0x6ULL) == 0) {
                if ((Board.BlackRooks & 0x1ULL) != 0) {
                    if ((generateAttackMap(COLOR::WHITE) & 0xeULL) == 0) {
                        Board.BlackKing >>= 2;
                        Board.BlackRooks ^= 0x5ULL;
                        Board.BlackPieces ^= 0xFULL;
                        Board.Pieces ^= 0xFULL;
                        Board.BlackKingside = false;
                        Board.BlackQueenside = false;
                        return true;
                    }
                }
            }
        } else {
            if ((Board.Pieces & 0x70ULL) == 0) {
                if ((Board.BlackRooks & 0x80ULL) != 0) {
                    if ((generateAttackMap(COLOR::WHITE) & 0x38ULL) == 0) {
                        Board.BlackKing <<= 2;
                        Board.BlackRooks ^= 0x90ULL;
                        Board.BlackPieces ^= 0xB8ULL;
                        Board.Pieces ^= 0xB8ULL;
                        Board.BlackKingside = false;
                        Board.BlackQueenside = false;
                        return true;
                    }
                }
            }
        }
    }
    return false; // return false if castling isn't legal
}

void board::_makeCaptureMove(U64 positions, COLOR color) {
    if (color == COLOR::WHITE) {
        Board.WhitePieces ^= (Board.WhitePieces & positions);
        Board.WhiteKnights ^= (Board.WhiteKnights & positions);
        Board.WhitePawns ^= (Board.WhitePawns & positions);
        Board.WhiteRooks ^= (Board.WhiteRooks & positions);
        Board.WhiteBishops ^= (Board.WhiteBishops & positions);
        Board.WhiteQueens ^= (Board.WhiteQueens & positions);
    } else {
        Board.BlackPieces ^= (Board.BlackPieces & positions);
        Board.BlackKnights ^= (Board.BlackKnights & positions);
        Board.BlackPawns ^= (Board.BlackPawns & positions);
        Board.BlackRooks ^= (Board.BlackRooks & positions);
        Board.BlackBishops ^= (Board.BlackBishops & positions);
        Board.BlackQueens ^= (Board.BlackQueens & positions);
    }
}

U64 board::getPieceMoves(PIECE piece, U64 location, COLOR color) {
    switch (piece) {
        case PAWN:
            return _getPawnMoves(location, color);
        case KNIGHT:
            return _getKnightMoves(location, color);
        case ROOK:
            return _getRookMoves(location, color);
        case BISHOP:
            return _getBishopMoves(location, color);
        case QUEEN:
            return _getQueenMoves(location, color);
        case KING:
            return _getKingMoves(location, color);
    }
    return 0;
}


void board::_promoteWhitePawn(U64 positions, PIECE piece) {
    switch (piece) {
        case ROOK:
            Board.WhiteRooks |= (positions & 0xFFULL);
            break;
        case BISHOP:
            Board.WhiteBishops |= (positions & 0xFFULL);
            break;
        case KNIGHT:
            Board.WhiteKnights |= (positions & 0xFFULL);
            break;
        case QUEEN:
            Board.WhiteQueens |= (positions & 0xFFULL);
            break;
        default:
            break;
    }
}


void board::_promoteBlackPawn(U64 positions, PIECE piece) {
    switch (piece) {
        case ROOK:
            Board.BlackRooks |= (positions & 0xFF00000000000000ULL);
            break;
        case BISHOP:
            Board.BlackBishops |= (positions & 0xFF00000000000000ULL);
            break;
        case KNIGHT:
            Board.BlackKnights |= (positions & 0xFF00000000000000ULL);
            break;
        case QUEEN:
            Board.BlackQueens |= (positions & 0xFF00000000000000ULL);
            break;
        default:
            break;
    }
}

U64 board::generateAttackMap(COLOR color) {
    U64 attackMap = 0;
    if (color == COLOR::WHITE) {
        U64 pieceLocations = Board.WhiteKnights;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            attackMap |= _getKnightMoves(lowest_piece, COLOR::WHITE);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.WhiteRooks;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            attackMap |= _getRookMoves(lowest_piece, COLOR::WHITE);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.WhiteBishops;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            attackMap |= _getBishopMoves(lowest_piece, COLOR::WHITE);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.WhiteQueens;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            attackMap |= _getQueenMoves(lowest_piece, COLOR::WHITE);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.WhitePawns;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            attackMap |= lowest_piece >> 9;
            attackMap |= lowest_piece >> 7;
            pieceLocations ^= lowest_piece;
        }
        attackMap |= _getKingMoves(Board.WhiteKing, COLOR::WHITE);
    } else {
        U64 pieceLocations = Board.BlackKnights;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            attackMap |= _getKnightMoves(lowest_piece, COLOR::BLACK);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.BlackRooks;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            attackMap |= _getRookMoves(lowest_piece, COLOR::BLACK);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.BlackBishops;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            attackMap |= _getBishopMoves(lowest_piece, COLOR::BLACK);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.BlackQueens;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            attackMap |= _getQueenMoves(lowest_piece, COLOR::BLACK);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.BlackPawns;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            attackMap |= lowest_piece << 9;
            attackMap |= lowest_piece << 7;
            pieceLocations ^= lowest_piece;
        }
        attackMap |= _getKingMoves(Board.BlackKing, COLOR::BLACK);
    }
    return attackMap;
}

U8 board::getMoveCount(COLOR color) {
    U64 moveMap = 0;
    if (color == COLOR::WHITE) {
        U64 pieceLocations = Board.WhiteKnights;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            moveMap |= _getKnightMoves(lowest_piece, COLOR::WHITE);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.WhiteRooks;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            moveMap |= _getRookMoves(lowest_piece, COLOR::WHITE);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.WhiteBishops;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            moveMap |= _getBishopMoves(lowest_piece, COLOR::WHITE);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.WhiteQueens;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            moveMap |= _getQueenMoves(lowest_piece, COLOR::WHITE);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.WhitePawns;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            moveMap |= _getPawnMoves(lowest_piece, COLOR::WHITE);
            pieceLocations ^= lowest_piece;
        }
        moveMap |= _getKingMoves(Board.WhiteKing, COLOR::WHITE);
    } else {
        U64 pieceLocations = Board.BlackKnights;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            moveMap |= _getKnightMoves(lowest_piece, COLOR::BLACK);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.BlackRooks;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            moveMap |= _getRookMoves(lowest_piece, COLOR::BLACK);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.BlackBishops;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            moveMap |= _getBishopMoves(lowest_piece, COLOR::BLACK);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.BlackQueens;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            moveMap |= _getQueenMoves(lowest_piece, COLOR::BLACK);
            pieceLocations ^= lowest_piece;
        }
        pieceLocations = Board.BlackPawns;
        while (pieceLocations != 0) {
            U64 lowest_piece = getLowestBit64(pieceLocations);
            moveMap |= _getPawnMoves(lowest_piece, COLOR::BLACK);
            pieceLocations ^= lowest_piece;
        }
        moveMap |= _getKingMoves(Board.BlackKing, COLOR::BLACK);
    }
    return countOnes(moveMap);
}

U64 board::getPawnAttacks(COLOR color) {
    U64 attacks = 0;
    if (color == COLOR::WHITE) {
        U64 pawnLocations = Board.WhitePawns;
        while (pawnLocations != 0) {
            U64 lowest_piece = getLowestBit64(pawnLocations);
            attacks |= (lowest_piece >> 7);
            attacks |= (lowest_piece >> 9);
            pawnLocations ^= lowest_piece;
        }
    } else {
        U64 pawnLocations = Board.BlackPawns;
        while (pawnLocations != 0) {
            U64 lowest_piece = getLowestBit64(pawnLocations);
            attacks |= (lowest_piece << 7);
            attacks |= (lowest_piece << 9);
            pawnLocations ^= lowest_piece;
        }
    }
    return attacks;
}

U64 board::_getPawnMoves(U64 location, COLOR color) const {
    U64 moves = 0;
    if (color == COLOR::WHITE) {
        if ((Board.Pieces & (location >> 8)) == 0) {
            moves = location >> 8;
            if ((location & 0xFF000000000000) != 0) {
                if ((Board.Pieces & (location >> 16)) == 0) {
                    moves |= (location >> 16);
                }
            }
        }
        if ((location & 0x8080808080808080ULL) == 0) {
            moves |= ((location >> 7) & (Board.BlackPieces | Board.EnPassantTargets));
        }
        if ((location & 0x101010101010101ULL) == 0) {
            moves |= ((location >> 9) & (Board.BlackPieces | Board.EnPassantTargets));
        }
    } else {
        if ((Board.Pieces & (location << 8)) == 0) {
            moves = location << 8;
            if ((location & 0xFF00) != 0) {
                if ((Board.Pieces & (location << 16)) == 0) {
                    moves |= (location << 16);
                }
            }
        }
        if ((location & 0x101010101010101ULL) == 0) {
            moves |= ((location << 7) & (Board.WhitePieces | Board.EnPassantTargets));
        }
        if ((location & 0x8080808080808080ULL) == 0) {
            moves |= ((location << 9) & (Board.WhitePieces | Board.EnPassantTargets));
        }
    }
    return moves;
}


U64 board::_getKnightMoves(U64 location, COLOR color) const {
    U8 square = 63 - __builtin_ctzll(location);
    if (color == COLOR::WHITE) {
        return Precomputed.KnightAttackTable[square] ^ (Board.WhitePieces & Precomputed.KnightAttackTable[square]);
    } else {
        return Precomputed.KnightAttackTable[square] ^ (Board.BlackPieces & Precomputed.KnightAttackTable[square]);
    }
}

U64 board::_getBishopMoves(U64 location, COLOR color) const {
    U8 square = 63 - __builtin_ctzll(location);
    U64 attacks = Precomputed.BishopAttackTable[square][(((Board.Pieces ^ location) & Precomputed.BishopMasks[square]) * BishopMagics[square]) >> BishopMagicShifts[square]];
    if (color == COLOR::WHITE) {
        return attacks ^ (attacks & Board.WhitePieces);
    } else {
        return attacks ^ (attacks & Board.BlackPieces);
    }
}

U64 board::_getRookMoves(U64 location, COLOR color) const {
    U8 square = 63 - __builtin_ctzll(location);
    U64 attacks = Precomputed.RookAttackTable[square][(((Board.Pieces ^ location) & Precomputed.RookMasks[square]) * RookMagics[square]) >> RookMagicShifts[square]];
    if (color == COLOR::WHITE) {
        return attacks ^ (attacks & Board.WhitePieces);
    } else {
        return attacks ^ (attacks & Board.BlackPieces);
    }
}

U64 board::_getQueenMoves(U64 location, COLOR color) {
    return _getBishopMoves(location, color) | _getRookMoves(location, color);
}

U64 board::_getKingMoves(U64 location, COLOR color) const {
    U8 square = 63 - __builtin_ctzll(location);
    if (color == COLOR::WHITE) {
        return Precomputed.KingAttackTable[square] ^ (Precomputed.KingAttackTable[square] & Board.WhitePieces);
    } else {
        return Precomputed.KingAttackTable[square] ^ (Precomputed.KingAttackTable[square] & Board.BlackPieces);
    }
}

void board::toStart() {
    loadPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 0");
}

void board::loadPosition(string FEN) {

    FEN_STAGE stage = PIECES;

    U8 position = 56;

    map<U8, U64> en_passant_first_round;
    bool en_passant_first_round_complete = false;

    _clearBoard();

    for (char currentCharacter : FEN) {
        switch (stage) {
            case PIECES:
                switch (currentCharacter) {
                    case 'P':
                        Board.WhitePawns |= (LOCATION::ZERO >> position);
                        position += 1;
                        break;
                    case 'N':
                        Board.WhiteKnights |= (LOCATION::ZERO >> position);
                        position += 1;
                        break;
                    case 'K':
                        Board.WhiteKing |= (LOCATION::ZERO >> position);
                        position += 1;
                        break;
                    case 'Q':
                        Board.WhiteQueens |= (LOCATION::ZERO >> position);
                        position += 1;
                        break;
                    case 'B':
                        Board.WhiteBishops |= (LOCATION::ZERO >> position);
                        position += 1;
                        break;
                    case 'R':
                        Board.WhiteRooks |= (LOCATION::ZERO >> position);
                        position += 1;
                        break;
                    case 'p':
                        Board.BlackPawns |= (LOCATION::ZERO >> position);
                        position += 1;
                        break;
                    case 'n':
                        Board.BlackKnights |= (LOCATION::ZERO >> position);
                        position += 1;
                        break;
                    case 'k':
                        Board.BlackKing |= (LOCATION::ZERO >> position);
                        position += 1;
                        break;
                    case 'q':
                        Board.BlackQueens |= (LOCATION::ZERO >> position);
                        position += 1;
                        break;
                    case 'b':
                        Board.BlackBishops |= (LOCATION::ZERO >> position);
                        position += 1;
                        break;
                    case 'r':
                        Board.BlackRooks |= (LOCATION::ZERO >> position);
                        position += 1;
                        break;
                    case '/':
                        position -= 16;
                        break;
                    case '1':
                        position += 1;
                        break;
                    case '2':
                        position += 2;
                        break;
                    case '3':
                        position += 3;
                        break;
                    case '4':
                        position += 4;
                        break;
                    case '5':
                        position += 5;
                        break;
                    case '6':
                        position += 6;
                        break;
                    case '7':
                        position += 7;
                        break;
                    case '8':
                        position += 8;
                        break;
                    default:
                        stage = PLAYER;
                }
                break;
            case PLAYER:
                if (currentCharacter == 'w') {
                    Board.Player = COLOR::WHITE;
                } else if (currentCharacter == 'b') {
                    Board.Player = COLOR::BLACK;
                } else {
                    stage = CASTLING;
                }
                break;
            case CASTLING:
                if (currentCharacter == 'K') {
                    Board.WhiteKingside = true;
                } else if (currentCharacter == 'Q') {
                    Board.WhiteQueenside = true;
                } else if (currentCharacter == 'k') {
                    Board.BlackKingside = true;
                } else if (currentCharacter == 'q') {
                    Board.BlackQueenside = true;
                } else if (currentCharacter == '-') {
                    break;
                } else {
                    stage = EN_PASSANT;
                }
                break;
            case EN_PASSANT:
                if (!en_passant_first_round_complete) {
                    if (currentCharacter == '-') {
                        en_passant_first_round_complete = true;
                        break;
                    }
                    en_passant_first_round = Precomputed.CoordinatesToBitmap[currentCharacter];
                    en_passant_first_round_complete = true;
                } else {
                    switch (currentCharacter) {
                        case '1':
                            Board.EnPassantTargets = en_passant_first_round[0];
                            break;
                        case '2':
                            Board.EnPassantTargets = en_passant_first_round[1];
                            break;
                        case '3':
                            Board.EnPassantTargets = en_passant_first_round[2];
                            break;
                        case '4':
                            Board.EnPassantTargets = en_passant_first_round[3];
                            break;
                        case '5':
                            Board.EnPassantTargets = en_passant_first_round[4];
                            break;
                        case '6':
                            Board.EnPassantTargets = en_passant_first_round[5];
                            break;
                        case '7':
                            Board.EnPassantTargets = en_passant_first_round[6];
                            break;
                        case '8':
                            Board.EnPassantTargets = en_passant_first_round[7];
                            break;
                        default:
                            stage = HALFMOVE;
                            break;
                    }
                }
                break;
            case HALFMOVE:
                switch (currentCharacter) {
                    case '1':
                        Board.HalfMoveClock = (Board.HalfMoveClock * 10) + 1;
                        break;
                    case '2':
                        Board.HalfMoveClock = (Board.HalfMoveClock * 10) + 2;
                        break;
                    case '3':
                        Board.HalfMoveClock = (Board.HalfMoveClock * 10) + 3;
                        break;
                    case '4':
                        Board.HalfMoveClock = (Board.HalfMoveClock * 10) + 4;
                        break;
                    case '5':
                        Board.HalfMoveClock = (Board.HalfMoveClock * 10) + 5;
                        break;
                    case '6':
                        Board.HalfMoveClock = (Board.HalfMoveClock * 10) + 6;
                        break;
                    case '7':
                        Board.HalfMoveClock = (Board.HalfMoveClock * 10) + 7;
                        break;
                    case '8':
                        Board.HalfMoveClock = (Board.HalfMoveClock * 10) + 8;
                        break;
                    case '9':
                        Board.HalfMoveClock = (Board.HalfMoveClock * 10) + 9;
                        break;
                    case '0':
                        Board.HalfMoveClock = (Board.HalfMoveClock * 10) + 0;
                        break;
                    default:
                        stage = FULLMOVE;
                        break;
                }
                break;
            case FULLMOVE:
                switch (currentCharacter) {
                    case '1':
                        Board.Move = (Board.Move * 10) + 1;
                        break;
                    case '2':
                        Board.Move = (Board.Move * 10) + 2;
                        break;
                    case '3':
                        Board.Move = (Board.Move * 10) + 3;
                        break;
                    case '4':
                        Board.Move = (Board.Move * 10) + 4;
                        break;
                    case '5':
                        Board.Move = (Board.Move * 10) + 5;
                        break;
                    case '6':
                        Board.Move = (Board.Move * 10) + 6;
                        break;
                    case '7':
                        Board.Move = (Board.Move * 10) + 7;
                        break;
                    case '8':
                        Board.Move = (Board.Move * 10) + 8;
                        break;
                    case '9':
                        Board.Move = (Board.Move * 10) + 9;
                        break;
                    case '0':
                        Board.Move = (Board.Move * 10) + 0;
                        break;
                    default:
                        break;
                }
                break;
        }
    }
    Board.WhitePieces = Board.WhitePawns | Board.WhiteKnights | Board.WhiteBishops | Board.WhiteRooks | Board.WhiteQueens | Board.WhiteKing;
    Board.BlackPieces = Board.BlackPawns | Board.BlackKnights | Board.BlackBishops | Board.BlackRooks | Board.BlackQueens | Board.BlackKing;

    Board.Pieces = Board.WhitePieces | Board.BlackPieces;
}

void board::_clearBoard() {
    Board.WhitePawns = 0;
    Board.WhiteKnights = 0;
    Board.WhiteBishops = 0;
    Board.WhiteRooks = 0;
    Board.WhiteQueens = 0;
    Board.WhiteKing = 0;

    Board.BlackPawns = 0;
    Board.BlackKnights = 0;
    Board.BlackBishops = 0;
    Board.BlackRooks = 0;
    Board.BlackQueens = 0;
    Board.BlackKing = 0;

    Board.EnPassantTargets = 0;

    Board.WhitePieces = 0;
    Board.BlackPieces = 0;
    Board.Pieces = 0;

    Board.WhiteKingside = true;
    Board.WhiteQueenside = true;

    Board.BlackKingside = true;
    Board.BlackQueenside = true;

    Board.HalfMoveClock = 0;
    Board.Move = 0;

    Board.Player = COLOR::WHITE;
}


string board::getFEN(bool includeData) {
    string fen = "";
    for (int rank = 0; rank < 8; rank++) {
        int blank = 0;
        for (int file = 7; file >= 0; file--) {
            int square = (rank * 8) + file;
            if (Board.WhitePawns & (1ULL << square)) {
                if (blank != 0) {
                    fen += to_string(blank);
                    blank = 0;
                }
                fen += "P";
            }
            else if (Board.WhiteKnights & (1ULL << square)) {
                if (blank != 0) {
                    fen += to_string(blank);
                    blank = 0;
                }
                fen += "N";
            }
            else if (Board.WhiteBishops & (1ULL << square)) {
                if (blank != 0) {
                    fen += to_string(blank);
                    blank = 0;
                }
                fen += "B";
            }
            else if (Board.WhiteRooks & (1ULL << square)) {
                if (blank != 0) {
                    fen += to_string(blank);
                    blank = 0;
                }
                fen += "R";
            }
            else if (Board.WhiteQueens & (1ULL << square)) {
                if (blank != 0) {
                    fen += to_string(blank);
                    blank = 0;
                }
                fen += "Q";
            }
            else if (Board.WhiteKing & (1ULL << square)) {
                if (blank != 0) {
                    fen += to_string(blank);
                    blank = 0;
                }
                fen += "K";
            } else if (Board.BlackPawns & (1ULL << square)) {
                if (blank != 0) {
                    fen += to_string(blank);
                    blank = 0;
                }
                fen += "p";
            }
            else if (Board.BlackKnights & (1ULL << square)) {
                if (blank != 0) {
                    fen += to_string(blank);
                    blank = 0;
                }
                fen += "n";
            }
            else if (Board.BlackBishops & (1ULL << square)) {
                if (blank != 0) {
                    fen += to_string(blank);
                    blank = 0;
                }
                fen += "b";
            }
            else if (Board.BlackRooks & (1ULL << square)) {
                if (blank != 0) {
                    fen += to_string(blank);
                    blank = 0;
                }
                fen += "r";
            }
            else if (Board.BlackQueens & (1ULL << square)) {
                if (blank != 0) {
                    fen += to_string(blank);
                    blank = 0;
                }
                fen += "q";
            }
            else if (Board.BlackKing & (1ULL << square)) {
                if (blank != 0) {
                    fen += to_string(blank);
                    blank = 0;
                }
                fen += "k";
            } else {
                blank += 1;
            }
        }

        if (blank != 0) {
            fen += to_string(blank);
        }
        if (rank != 7) {
            fen += "/";
        }
    }

    if (includeData) {

        fen += " ";
        if (Board.Player == COLOR::WHITE) {
            fen += "w ";
        } else {
            fen += "b ";
        }

        bool castle = false;
        if (Board.WhiteKingside) {
            fen += "K";
            castle = true;
        }
        if (Board.WhiteQueenside) {
            fen += "Q";
            castle = true;
        }
        if (Board.BlackKingside) {
            fen += "k";
            castle = true;
        }
        if (Board.BlackQueenside) {
            fen += "q";
            castle = true;
        }

        if (!castle) {
            fen += "- ";
        } else {
            fen += " ";
        }
    }

//    if (Board.EnPassantTargets != 0) {
//        fen += int_to_location_string[getLowestBit64(Board.EnPassantTargets)];
//    }
    return fen;
}

void board::printGame() {
    cout << "\n";
    for (int rank = 0; rank < 8; rank++) {
        cout << 8 - rank << " ";
        for (int file = 7; file >= 0; file--) {
            int square = rank * 8 + file;
            bool whitePiece = false;
            bool blackPiece = false;

            // Check if there is a white piece on this square
            if (Board.WhitePawns & (1ULL << square)) {
                cout << "P ";
                whitePiece = true;
            }
            else if (Board.WhiteKnights & (1ULL << square)) {
                cout << "N ";
                whitePiece = true;
            }
            else if (Board.WhiteBishops & (1ULL << square)) {
                cout << "B ";
                whitePiece = true;
            }
            else if (Board.WhiteRooks & (1ULL << square)) {
                cout << "R ";
                whitePiece = true;
            }
            else if (Board.WhiteQueens & (1ULL << square)) {
                cout << "Q ";
                whitePiece = true;
            }
            else if (Board.WhiteKing & (1ULL << square)) {
                cout << "K ";
                whitePiece = true;
            }

            // Check if there is a black piece on this square
            if (Board.BlackPawns & (1ULL << square)) {
                cout << "p ";
                blackPiece = true;
            }
            else if (Board.BlackKnights & (1ULL << square)) {
                cout << "n ";
                blackPiece = true;
            }
            else if (Board.BlackBishops & (1ULL << square)) {
                cout << "b ";
                blackPiece = true;
            }
            else if (Board.BlackRooks & (1ULL << square)) {
                cout << "r ";
                blackPiece = true;
            }
            else if (Board.BlackQueens & (1ULL << square)) {
                cout << "q ";
                blackPiece = true;
            }
            else if (Board.BlackKing & (1ULL << square)) {
                cout << "k ";
                blackPiece = true;
            }

            // If there is no piece on this square, print an empty space
            if (!whitePiece && !blackPiece) {
                cout << "- ";
            }
        }
        cout << endl;
    }

    cout << "  A B C D E F G H" << endl;
}
