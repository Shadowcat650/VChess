//
// Created by ShadowCat650 on 4/7/23.
//

#ifndef VELOCITYCHESS_BOOK_H
#define VELOCITYCHESS_BOOK_H
#include "board.h"
#include "opening.h"

#include <algorithm>
#include <random>

using namespace std;

class book {
public:
    Move getBookMove(board state);
    
    void initOpenings();
private:
    vector<opening> openings;
};


#endif //VELOCITYCHESS_BOOK_H
