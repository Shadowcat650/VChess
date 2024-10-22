//
// Created by ShadowCat650 on 4/3/23.
//

#ifndef VELOCITYCHESS_GUI_H
#define VELOCITYCHESS_GUI_H

#include <SFML/Graphics.hpp>
#include "../board.h"
#include "../search.h"
#include "../screen.h"
#include "../uci.h"


void loop(std::string fen);

bool squareIsWhite(U64 square);

U8 getSquareFromCoordinates(int x, int y);

bool testMove(U64 move, board Game);

U64 pruneIllegal(U64 movesToPrune, board Game);

bool tryMove(Move move, board Game);

bool checkForMate(board Game);

void handleMate(board Game);

bool checkForDraw(board state);

void makeMove(Move move);

void printOpeningInstructions(COLOR forColor);


#endif //VELOCITYCHESS_GUI_H
