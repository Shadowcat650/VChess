//
// Created by ShadowCat650 on 4/7/23.
//

#ifndef VELOCITYCHESS_OPENING_H
#define VELOCITYCHESS_OPENING_H
#include "board.h"

struct positionMove {
    string position;
    Move move;
};

class opening {
public:
    opening(string openingName);
    vector<positionMove> openingPositions;
private:
    void vienna();
    void caro();
    void london();
    void sicilian();
    void queensGambit();
    void italian();
    void french();
    void scandinavian();
};


#endif //VELOCITYCHESS_OPENING_H
