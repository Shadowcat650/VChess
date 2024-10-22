//
// Created by ShadowCat650 on 3/5/23.
//

#ifndef VELOCITYCHESS_MISC_H
#define VELOCITYCHESS_MISC_H

using namespace std;
#include <iostream>
#include "vector"
#include "definitions.h"


inline U64 getLowestBit64(U64 num) {
    return (~num + 1) & num;
}

inline U8 countOnes(U64 num) {
    return __builtin_popcountll(num);
}

void printBinaryInGrid(U64 n);
vector<U64> breakBitboard(U64 board);


#endif //VELOCITYCHESS_MISC_H
