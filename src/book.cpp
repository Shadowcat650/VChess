//
// Created by ShadowCat650 on 4/7/23.
//

#include "book.h"

void book::initOpenings() {
    openings = {};
    openings.emplace_back("vienna");
    openings.emplace_back("scandinavian");
    openings.emplace_back("caro");
    openings.emplace_back("london");
    openings.emplace_back("queensGambit");
    openings.emplace_back("italian");
}

Move book::getBookMove(board state) {

    std::random_device rd;
    std::mt19937 gen(rd());

    string fen = state.getFEN(true);
    shuffle(openings.begin(), openings.end(), gen);
    for (opening o : openings) {
        for (positionMove pm : o.openingPositions) {
            if (pm.position == fen) {
                return pm.move;
            }
        }
    }
    return {0, PAWN, WHITE};
}