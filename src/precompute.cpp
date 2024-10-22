//
// Created by ShadowCat650 on 3/4/23.
//

#include "precompute.h"


precompute Precomputed;

void initPrecompute() {
    Precomputed.initTables();
}

void precompute::initTables() {

    _initCoordinatesToBitmap();

    _initKnightAttackTable();
    _initKingAttackTable();


    _initBishopMasks();
    _initRookMasks();

    _initRookBlockerTable();
    _initBishopBlockerTable();

    _initMuggleAttackTables();

    _initBishopAttackTable();
    _initRookAttackTable();

}

void precompute::_initCoordinatesToBitmap() {
    char letter[8] = {
            'a','b','c','d','e','f','g','h'
    };
    for (U8 square = 0; square < 64; square++) {
        U8 column = square % 8;
        U8 row = square / 8;
        CoordinatesToBitmap[letter[column]][row] = LOCATION::ZERO >> ((row * 8) + column);
    }
}

void precompute::_initKnightAttackTable() {
    for (U8 i = 0; i < 64; i++) {
        U64 position = LOCATION::ZERO >> i;
        U64 attackedSquares = 0;
        if ((position & 0x10101010101FFFF) == 0) {
            attackedSquares |= (position >> 17);
        }
        if ((position & 0x808080808080FFFF) == 0) {
            attackedSquares |= (position >> 15);
        }
        if ((position & 0x3030303030303FF) == 0) {
            attackedSquares |= (position >> 10);
        }
        if ((position & 0xC0C0C0C0C0C040FF) == 0) {
            attackedSquares |= (position >> 6);
        }
        if ((position & 0xFF03030303030303) == 0) {
            attackedSquares |= (position << 6);
        }
        if ((position & 0xFFC0C0C0C0C0C0C0) == 0) {
            attackedSquares |= (position << 10);
        }
        if ((position & 0xFFFF010101010101) == 0) {
            attackedSquares |= (position << 15);
        }
        if ((position & 0xFFFF808080808080) == 0) {
            attackedSquares |= (position << 17);
        }
        KnightAttackTable[i] = attackedSquares;
    }
}

void precompute::_initKingAttackTable() {
    for (U8 i = 0; i < 64; i++) {
        U64 position = LOCATION::ZERO >> i;
        U64 attackedSquares = 0;
        if ((position & 0x101010101010101ULL) == 0) { // right
            attackedSquares = attackedSquares | (position >> 1);
        }
        if ((position & 0x8080808080808080ULL) == 0) { // left
            attackedSquares = attackedSquares | (position << 1);
        }
        if ((position & 0xFFULL) == 0) { // up
            attackedSquares = attackedSquares | (position >> 8);
        }
        if ((position & 0xFF00000000000000ULL) == 0) { // down
            attackedSquares = attackedSquares | (position << 8);
        }
        if ((position & 0x80808080808080FFULL) == 0) { // right up
            attackedSquares = attackedSquares | (position >> 7);
        }
        if ((position & 0x1010101010101FFULL) == 0) { // left up
            attackedSquares = attackedSquares | (position >> 9);
        }
        if ((position & 0xFF01010101010101ULL) == 0) { // right down
            attackedSquares = attackedSquares | (position << 7);
        }
        if ((position & 0xFF80808080808080ULL) == 0) { // left down
            attackedSquares = attackedSquares | (position << 9);
        }
        KingAttackTable[i] = attackedSquares;
    }
}

void precompute::_initRookMasks() {
    for (U8 square = 0; square < 64; square++) {
        U64 mask = 0;
        U64 pos = LOCATION::ZERO >> square;
        // left
        for (int shift = 1; pos << shift != 0; shift+=1) {
            if (square % 8 == 0 || square % 8 == 1) {
                break;
            }
            mask |= pos << shift;
            if ((square - shift) % 8 == 1) {
                break;
            }
        }
        // right
        for (int shift = 1; pos >> shift != 0; shift+=1) {
            if (square % 8 == 7 || square % 8 == 6) {
                break;
            }
            mask |= pos >> shift;
            if ((square + shift) % 8 == 6) {
                break;
            }
        }
        // up
        for (int shift = 8; pos >> shift != 0; shift+=8) {
            if (square / 8 == 7 || square / 8 == 6) {
                break;
            }
            mask |= pos >> shift;
            if ((square + shift) / 8 == 6) {
                break;
            }
        }
        // check down
        for (int shift = 8; pos << shift != 0; shift+=8) {
            if (square / 8 == 0 || square / 8 == 1) {
                break;
            }
            mask |= pos << shift;
            if ((square - shift) / 8 == 1) {
                break;
            }
        }
        RookMasks[square] = mask;
    }
}


void precompute::_initBishopMasks() {
    for (int square = 0; square < 64; square++) {
        U64 mask = 0;
        U64 pos = LOCATION::ZERO >> square;
        // left-up
        for (int shift = 7; pos >> shift != 0; shift+=7) {
            if (square % 8 == 0 || square / 8 == 7 || square % 8 == 1 || square / 8 == 6) {
                break;
            }
            mask |= pos >> shift;
            if ((square + shift) % 8 == 1 || (square + shift) / 8 == 6) {
                break;
            }
        }
        // right-down
        for (int shift = 7; pos << shift != 0; shift+=7) {
            if (square % 8 == 7 || square / 8 == 0 || square % 8 == 6 || square / 8 == 1) {
                break;
            }
            mask |= pos << shift;
            if ((square - shift) % 8 == 6 || (square - shift) / 8 == 1) {
                break;
            }
        }
        // right-up
        for (int shift = 9; pos >> shift != 0; shift+=9) {
            if (square % 8 == 7 || square / 8 == 7 || square % 8 == 6 || square / 8 == 6) {
                break;
            }
            mask |= pos >> shift;
            if ((square + shift) % 8 == 6 || (square + shift) / 8 == 6) {
                break;
            }
        }
        // check left-down
        for (int shift = 9; pos << shift != 0; shift+=9) {
            if (square % 8 == 0 || square / 8 == 0 || square % 8 == 1 || square / 8 == 1) {
                break;
            }
            mask |= pos << shift;
            if ((square - shift) % 8 == 1 || (square - shift) / 8 == 1) {
                break;
            }
        }
        BishopMasks[square] = mask;
    }
}

void precompute::_initMuggleAttackTables() {
    for (U8 square = 0; square < 64; square++) {
        for (U64 Combo : RookBlockers[square]) {
            MuggleRookAttackTable[square][Combo] = _generateRookMoveSlow(Combo, square);
        }
        for (U64 Combo : BishopBlockers[square]) {
            MuggleBishopAttackTable[square][Combo] = _generateBishopMoveSlow(Combo, square);
        }
    }
}


void precompute::_initRookAttackTable() {
    for (U8 square = 0; square < 64; square++) {
        for (U64 Combo : RookBlockers[square]) {
            U16 index = (Combo * RookMagics[square]) >> RookMagicShifts[square];
            RookAttackTable[square][index] = _generateRookMoveSlow(Combo, square);
        }
    }
}

void precompute::_initBishopAttackTable() {
    for (U8 square = 0; square < 64; square++) {
        for (U64 Combo : BishopBlockers[square]) {
            U16 index = (Combo * BishopMagics[square]) >> BishopMagicShifts[square];
            BishopAttackTable[square][index] = _generateBishopMoveSlow(Combo, square);
        }
    }
}

U64 precompute::_generateRookMoveSlow(U64 blockers, U8 square) {
    U64 pos = LOCATION::ZERO >> square;
    U64 moves = 0;
    // left
    for (int shift = 1; pos << shift != 0; shift+=1) {
        if (square % 8 == 0) {
            break;
        }
        moves |= pos << shift;
        if (((pos << shift) & blockers) != 0) {
            break;
        }
        if ((square - shift) % 8 == 0) {
            break;
        }
    }
    // right
    for (int shift = 1; pos >> shift != 0; shift+=1) {
        if (square % 8 == 7) {
            break;
        }
        moves |= pos >> shift;
        if (((pos >> shift) & blockers) != 0) {
            break;
        }
        if ((square + shift) % 8 == 7) {
            break;
        }
    }
    // up
    for (int shift = 8; pos >> shift != 0; shift+=8) {
        if (square / 8 == 7) {
            break;
        }
        moves |= pos >> shift;
        if (((pos >> shift) & blockers) != 0) {
            break;
        }
        if ((square + shift) / 8 == 7) {
            break;
        }
    }
    // check down
    for (int shift = 8; pos << shift != 0; shift+=8) {
        if (square / 8 == 0) {
            break;
        }
        moves |= pos << shift;
        if (((pos << shift) & blockers) != 0) {
            break;
        }
        if ((square - shift) / 8 == 0) {
            break;
        }
    }
    return moves;
}

U64 precompute::_generateBishopMoveSlow(U64 blockers, U8 square) {
    U64 pos = LOCATION::ZERO >> square;
    U64 moves = 0;
    // left-up
    for (int shift = 7; pos >> shift != 0; shift+=7) {
        if (square % 8 == 0 || square / 8 == 7) {
            break;
        }
        moves |= pos >> shift;
        if (((pos >> shift) & blockers) != 0) {
            break;
        }
        if ((square + shift) % 8 == 0) {
            break;
        }
    }
    // right-down
    for (int shift = 7; pos << shift != 0; shift+=7) {
        if (square % 8 == 7 || square / 8 == 0) {
            break;
        }
        moves |= pos << shift;
        if (((pos << shift) & blockers) != 0) {
            break;
        }
        if ((square - shift) % 8 == 7) {
            break;
        }
    }
    // right-up
    for (int shift = 9; pos >> shift != 0; shift+=9) {
        if (square % 8 == 7 || square / 8 == 7) {
            break;
        }
        moves |= pos >> shift;
        if (((pos >> shift) & blockers) != 0) {
            break;
        }
        if ((square + shift) % 8 == 7) {
            break;
        }
    }
    // check left-down
    for (int shift = 9; pos << shift != 0; shift+=9) {
        if (square % 8 == 0 || square / 8 == 0) {
            break;
        }
        moves |= pos << shift;
        if (((pos << shift) & blockers) != 0) {
            break;
        }
        if ((square - shift) % 8 == 0) {
            break;
        }
    }
    return moves;
}


void precompute::_initRookBlockerTable() {
    for (U8 square = 0; square < 64; square++) {
        RookBlockers[square] = _getBlockersFor(square, PIECE::ROOK);
    }
}


void precompute::_initBishopBlockerTable() {
    for (U8 square = 0; square < 64; square++) {
        BishopBlockers[square] = _getBlockersFor(square, PIECE::BISHOP);
    }
}


vector<U64> precompute::_getBlockersFor(U8 square, PIECE piece) {
    U64 mask = (piece == PIECE::ROOK) ? RookMasks[square] : BishopMasks[square];
    if (mask == 0) {
        return vector<U64>{0};
    }
    U8 numberOfPotentialBlockers = countOnes(mask);
    vector<U64> potentialBlockerPositions;
    for (U8 i = 0; i < numberOfPotentialBlockers; i++) {
        potentialBlockerPositions.push_back(getLowestBit64(mask));
        mask = mask ^ getLowestBit64(mask);
    }
    vector<U64> blockerCombinations;
    for (int combination = 0; combination < pow(2, potentialBlockerPositions.size()); combination++) {
        U64 blockerCombo = 0;
        for (int bit = 0; bit < numberOfPotentialBlockers; bit++) {
            blockerCombo |= ((combination >> bit) & 1) * potentialBlockerPositions[bit];
        }
        blockerCombinations.push_back(blockerCombo);
    }
    return blockerCombinations;
}
