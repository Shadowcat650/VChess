//
// Created by ShadowCat650 on 3/5/23.
//

#ifndef VELOCITYCHESS_DEFINITIONS_H
#define VELOCITYCHESS_DEFINITIONS_H


using namespace std;
#include <iostream>

enum PIECE {
    PAWN,
    KNIGHT,
    ROOK,
    BISHOP,
    QUEEN,
    KING,
};

enum COLOR {
    WHITE,
    BLACK,
};

enum FEN_STAGE {
    PIECES,
    PLAYER,
    CASTLING,
    EN_PASSANT,
    HALFMOVE,
    FULLMOVE,
};

enum LOCATION {
    ZERO = 0x8000000000000000ULL,
};

enum SIDES {
    KINGSIDE,
    QUEENSIDE,
    NONE,
};


typedef uint8_t U8;
typedef uint16_t U16;
typedef uint64_t U64;
typedef int8_t S8;

struct position {
    int x;
    int y;
};

struct object {
    U8 id;
    position origin;
    int width;
    int height;
};


#endif //VELOCITYCHESS_DEFINITIONS_H
