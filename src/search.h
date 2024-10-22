//
// Created by ShadowCat650 on 3/17/23.
//

#ifndef VELOCITYCHESS_SEARCH_H
#define VELOCITYCHESS_SEARCH_H
#include "evaluate.h"
#include "board.h"
#include <chrono>
#include <thread>
#include <mutex>
#include "unordered_map"
#include "future"
#include <atomic>
#include "book.h"


struct move_score_nodes {
    int score;
    Move move;
    int nodes;
};

struct move_nodes {
    Move move;
    int nodes;
};

    const S8 INF = 127;

    void setDepth(int depth);

    int getDepth();

    move_nodes find_best_move(board state, int depth, vector<string> statesVisited);

    S8 minimax(board state, U8 depth, S8 alpha, S8 beta, bool maximizer, int &nodes);

    move_score_nodes score_moves(board state, vector<Move> moves);

    string number_to_chess_coords(int num);

    void getMovesForPosition(board state, COLOR color, vector<Move> &locationForMoves);

    bool checkForMate(board Game);

    bool tryMove(Move move, board Game);

    bool staleMate(board Game);

    Move getFastestMate(vector<Move> tryMates, board state);

    int mateCount(board state, int count, int depth);

    S8 getScorePrediction(board state, Move move);

    bool checkForRepetition(board newState);

    void initBook();

#endif //VELOCITYCHESS_SEARCH_H
