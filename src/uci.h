//
// Created by ShadowCat650 on 3/22/23.
//

#ifndef VELOCITYCHESS_UCI_H
#define VELOCITYCHESS_UCI_H
#include "board.h"
#include "search.h"
#include "precompute.h"


void parse_string(string input);

void id();

void uci();

void isReady();

void go();

void position(string input);

void newGame();

void setOption(string input);

string getStringForMove(Move move, board Board);

PIECE findPieceMoving(U64 position);


#endif //VELOCITYCHESS_UCI_H

/// ALWAYS BE ABLE TO PROCESS COMMANDS FROM GUI
/// END ALL OUTPUTS WITH \n
/// WHITE SPACE BETWEEN INPUTS IS IGNORED
/// NEVER THINK/PONDER BEFORE RECEIVING "go" COMMAND
/// MOVE FOR MAT IS IN LONG ALGEBRAIC NOTATION
/// ENGINE PRECOMPUTES AND WAITS FOR "isready" OR "setoptions"




/// GUI TO ENGINE

// "uci", very first command after program boot. Tells engine to use uci mode.
// After being received, engine identifies with "id" command, sets options with "options" command, then sends "uciok"

// "debug [on/off], turned off by default, when received, start sending additional info to GUI with "info string" command.

// "isready", used to ping the engine, the engine must always return "readyok", but it can wait to finish initializing to do so

// "setoption name <id> [value <x>]", sets options for the engine.

// "registration", registers engine

// "ucinewgame" sent when the next search will be for a new game

// position [fen <fenstring> | startpos ]  moves <move1> .... <movei>, set the position

