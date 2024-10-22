//
// Created by ShadowCat650 on 3/11/23.
//

#ifndef VELOCITYCHESS_MAGIC_SEARCH_H
#define VELOCITYCHESS_MAGIC_SEARCH_H

#include "definitions.h"
#include "vector"
#include "precompute.h"
#include <random>
#include <iostream>
#include <cstdint>


void find_magics();
U64 generateMagic(int square, bool isRook);
U64 get_random();


#endif //VELOCITYCHESS_MAGIC_SEARCH_H
