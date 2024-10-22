//
// Created by ShadowCat650 on 3/17/23.
//

#include "search.h"

int max_depth = 0;

const int numberOfCores = thread::hardware_concurrency();

COLOR evalFor;

U8 numberOfThreads = numberOfCores - 2;


vector<string> statesPreviouslyVisited;

book openingBook;


S8 minimax(board state, U8 depth, S8 alpha, S8 beta, bool maximizer, int &nodes) {

    if (depth == 0) {
        return ((evalFor == COLOR::WHITE) ? 1 : -1) * evaluate_position(state);
    }

    if (maximizer) {

        if (alpha >= beta) {
            nodes++;
            return beta;
        }

        vector<Move> moves;
        moves.reserve(50);
        getMovesForPosition(state, state.Board.Player, moves);

        U8 scores[moves.size()];

        for (size_t i = 0; i < moves.size(); i++) {
            scores[i] = getScorePrediction(state, moves[i]);
        }

        vector<pair<Move, U8>> pairs;
        pairs.reserve(moves.size());
        for (int i = 0; i < moves.size(); i++) {
            pairs.emplace_back(moves[i], scores[i]);
        }

        sort(pairs.begin(), pairs.end(), [](pair<Move, U8> a, pair<Move, U8> b) {
            return a.second < b.second; // sort in descending order based on score
        });

        vector<Move> orderedMoves;
        orderedMoves.reserve(moves.size());
        for (auto &pair: pairs) {
            orderedMoves.push_back(pair.first);
        }


        bool madeMove = false;


        S8 bestScore = -INF;

        for (Move m : orderedMoves) {
            board newState = state;
            if (newState.makeMove(m)) {
                if (checkForRepetition(newState)) {
                    return 0;
                }
                if (state.Board.HalfMoveClock == 50) {
                    return true;
                }
                madeMove = true;
                S8 score = minimax(newState, depth-1, alpha, beta, false, nodes);

                bestScore = max(bestScore, score);
                alpha = max(alpha, score);
                if (alpha >= beta) {
                    nodes++;
                    break;
                }
            }
        }
        if (!madeMove) {
            if (checkForMate(state)) {
                if (staleMate(state)) {
                    return 0;
                }
                if (state.Board.Player == evalFor) {
                    return -INF;
                } else {
                    return INF;
                }
            }
        }
        return bestScore;
    }
    else {
        if (beta <= alpha) {
            nodes++;
            return alpha;
        }

        vector<Move> moves;
        moves.reserve(50);
        getMovesForPosition(state, state.Board.Player, moves);

        U8 scores[moves.size()];

        for (size_t i = 0; i < moves.size(); i++) {
            scores[i] = getScorePrediction(state, moves[i]);
        }

        vector<pair<Move, U8>> pairs;
        pairs.reserve(moves.size());
        for (int i = 0; i < moves.size(); i++) {
            pairs.emplace_back(moves[i], scores[i]);
        }

        sort(pairs.begin(), pairs.end(), [](pair<Move, U8> a, pair<Move, U8> b) {
            return a.second < b.second; // sort in descending order based on score
        });

        vector<Move> orderedMoves;
        orderedMoves.reserve(moves.size());
        for (auto &pair: pairs) {
            orderedMoves.push_back(pair.first);
        }

        bool madeMove = false;

        S8 bestScore = INF;


        for (Move m : orderedMoves) {
            board newState = state;
            if (newState.makeMove(m)) {
                if (checkForRepetition(newState)) {
                    return 0;
                }
                if (state.Board.HalfMoveClock == 50) {
                    return true;
                }
                madeMove = true;
                S8 score = minimax(newState, depth-1, alpha, beta, true, nodes);

                bestScore = min(bestScore, score);
                beta = min(beta, score);
                if (beta <= alpha) {
                    nodes++;
                    break;
                }
            }
        }
        if (!madeMove) {
            if (checkForMate(state)) {
                if (staleMate(state)) {
                    return 0;
                }
                if (state.Board.Player == evalFor) {
                    return -INF;
                } else {
                    return INF;
                }
            }
        }
        return bestScore;
    }
}

move_score_nodes score_moves(board state, vector<Move> moves) {

    S8 best_score = -INF;
    Move best_move;

    int nodes = 0;

    U8 scores[moves.size()];

    for (size_t i = 0; i < moves.size(); i++) {
        scores[i] = getScorePrediction(state, moves[i]);
    }


    vector<pair<Move, U8>> pairs;
    pairs.reserve(moves.size());
    for (int i = 0; i < moves.size(); i++) {
        pairs.emplace_back(moves[i], scores[i]);
    }

    sort(pairs.begin(), pairs.end(), [](pair<Move, U8> a, pair<Move, U8> b) {
        return a.second < b.second; // sort in descending order based on score
    });

    vector<Move> orderedMoves;
    orderedMoves.reserve(moves.size());
    for (auto &pair: pairs) {
        orderedMoves.push_back(pair.first);
    }

    for (Move m : orderedMoves) {

        board new_state = state;
        if (new_state.makeMove(m)) {
            S8 score = minimax(new_state, max_depth-1, -INF, INF, false, nodes);

            if (score > best_score) {
                best_score = score;
                best_move = m;
            }

        }

    }
        return {best_score, best_move, nodes};
}

int mateCount(board state, int count, int depth) {
    if (depth == 0) {
        return max_depth;
    }
        count++;
        vector<Move> moves;
        moves.reserve(50);
        getMovesForPosition(state, state.Board.Player, moves);

    if (checkForMate(state)) {
        return count;
    }

        for (Move m : moves) {
            board newState = state;
            if (newState.makeMove(m)) {
                return mateCount(newState, count, depth-1);
            }
        }
        return INF;
}


Move getFastestMate(vector<Move> tryMates, board state) {
    int bestScore = INF;
    Move bestMove;
    for (Move mate : tryMates) {
        board newState = state;
        newState.makeMove(mate);
        int score = mateCount(newState, 0, max_depth-1);
        if (score < bestScore) {
            bestScore = score;
            bestMove = mate;
        }
        if (bestScore == 1) {
            return bestMove;
        }
    }
    return bestMove;
}

move_nodes find_best_move(board state, int depth, vector<string> statesVisited) {

    statesPreviouslyVisited = statesVisited;

    evalFor = state.Board.Player;

    max_depth = depth;

    if (state.Board.Move < 10) {
        Move bookMove = openingBook.getBookMove(state);
        if (bookMove.positions != 0) {
            return {bookMove, 0};
        }
    }

    vector<Move> moves;
    moves.reserve(50);
    getMovesForPosition(state, state.Board.Player, moves);

    cout << "Total moves: " <<  moves.size() << endl;

    vector<vector<Move>> movesForThread;

    int splitLength = moves.size() / numberOfThreads;

    for (int i = 0; i < numberOfThreads; i++) {
        int start = i * splitLength;
        int end = start + splitLength;
        if (i != numberOfThreads - 1) {
            vector<Move> splitVec(moves.begin() + start, moves.begin() + end);
            movesForThread.push_back(splitVec);
        } else {
            vector<Move> splitVec(moves.begin() + start, moves.end());
            movesForThread.push_back(splitVec);
        }
    }


    vector<thread> threads(numberOfThreads);
    vector<future<move_score_nodes>> futures(numberOfThreads);

    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    for (U8 i = 0; i < numberOfThreads; i++) {
        promise<move_score_nodes> p;
        futures[i] = p.get_future();
        threads[i] = thread([i, state, movesForThread, p = std::move(p)]() mutable {
            // execute your function here
            move_score_nodes result = score_moves(state, movesForThread[i]);
            p.set_value(result);
        });
    }



    vector<move_score_nodes> results(numberOfThreads);
    for (U8 i = 0; i < numberOfThreads; i++) {
        threads[i].join();
        results[i] = futures[i].get();
    }

    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Elapsed time: " << duration.count() << " microseconds" << std::endl;


    Move bestMove;
    int bestScore = -INF;
    int total_nodes = 0;

    vector<Move> matingMoves;

    for (move_score_nodes result: results) {
        if (bestScore == INF) {
            if (result.score == INF) {
                matingMoves.push_back(result.move);
            }
        }
        if (result.score > bestScore) {
            bestScore = result.score;
            bestMove = result.move;
            if (bestScore == INF) {
                matingMoves.push_back(bestMove);
            }
        }
        total_nodes += result.nodes;
    }

    if (!matingMoves.empty()) {
        return {getFastestMate(matingMoves, state), 0};
    }

    cout << "Pruned: " << total_nodes << " nodes \n";

    if (bestScore == -INF) {
        for (Move m : moves) {
            board testState = state;
            if (testState.makeMove(m)) {
                return {m, total_nodes};
            }
        }
    }

    return {bestMove, total_nodes};
}


void getMovesForPosition(board state, COLOR color, vector<Move> &locationForMoves) {
    if (color == COLOR::WHITE) {
        if (state.Board.WhiteKingside) {
            locationForMoves.push_back({0, PIECE::KING, COLOR::WHITE, SIDES::KINGSIDE});
        }
        if (state.Board.WhiteQueenside) {
            locationForMoves.push_back({0, PIECE::KING, COLOR::WHITE, SIDES::QUEENSIDE});
        }
        for (U8 p = 0; p < 6; p++) {
            U64 pieceLocations;
            PIECE pieceType;
            switch (p) {
                case 0:
                    pieceType = PIECE::PAWN;
                    pieceLocations = state.Board.WhitePawns;
                    break;
                case 1:
                    pieceType = PIECE::KNIGHT;
                    pieceLocations = state.Board.WhiteKnights;
                    break;
                case 2:
                    pieceType = PIECE::ROOK;
                    pieceLocations = state.Board.WhiteRooks;
                    break;
                case 3:
                    pieceType = PIECE::BISHOP;
                    pieceLocations = state.Board.WhiteBishops;
                    break;
                case 4:
                    pieceType = PIECE::QUEEN;
                    pieceLocations = state.Board.WhiteQueens;
                    break;
                case 5:
                    pieceType = PIECE::KING;
                    pieceLocations = state.Board.WhiteKing;
                    break;
            }
            if (pieceType == PIECE::PAWN) {
                while (pieceLocations != 0) {
                    U64 lowest_piece = getLowestBit64(pieceLocations);
                    U64 PieceMoves = state.getPieceMoves(pieceType, lowest_piece, color);
                    while (PieceMoves != 0) {
                        U64 lowest_move = getLowestBit64(PieceMoves);
                        // look for promotions
                        if ((lowest_move & 0xff000000000000ffULL) != 0) {
                            locationForMoves.push_back(
                                    {(lowest_piece | lowest_move), pieceType, color, SIDES::NONE, PIECE::QUEEN});
                            locationForMoves.push_back(
                                    {(lowest_piece | lowest_move), pieceType, color, SIDES::NONE, PIECE::KNIGHT});
                            locationForMoves.push_back({(lowest_piece | lowest_move), pieceType, color, SIDES::NONE, PIECE::ROOK});
                            locationForMoves.push_back(
                                    {(lowest_piece | lowest_move), pieceType, color, SIDES::NONE, PIECE::BISHOP});
                        } else {
                            locationForMoves.push_back({(lowest_piece | lowest_move), pieceType, color});
                        }
                        PieceMoves ^= lowest_move;
                    }
                    pieceLocations ^= lowest_piece;
                }
            } else {
                while (pieceLocations != 0) {
                    U64 lowest_piece = getLowestBit64(pieceLocations);
                    U64 PieceMoves = state.getPieceMoves(pieceType, lowest_piece, color);
                    while (PieceMoves != 0) {
                        U64 lowest_move = getLowestBit64(PieceMoves);
                        locationForMoves.push_back({(lowest_piece | lowest_move), pieceType, color});
                        PieceMoves ^= lowest_move;
                    }
                    pieceLocations ^= lowest_piece;
                }
            }
        }
    } else {
        if (state.Board.BlackKingside) {
            locationForMoves.push_back({0, PIECE::KING, COLOR::BLACK, SIDES::KINGSIDE});
        }
        if (state.Board.BlackQueenside) {
            locationForMoves.push_back({0, PIECE::KING, COLOR::BLACK, SIDES::QUEENSIDE});
        }
        for (U8 p = 0; p < 6; p++) {
            U64 pieceLocations;
            PIECE pieceType;
            switch (p) {
                case 0:
                    pieceType = PIECE::PAWN;
                    pieceLocations = state.Board.BlackPawns;
                    break;
                case 1:
                    pieceType = PIECE::KNIGHT;
                    pieceLocations = state.Board.BlackKnights;
                    break;
                case 2:
                    pieceType = PIECE::ROOK;
                    pieceLocations = state.Board.BlackRooks;
                    break;
                case 3:
                    pieceType = PIECE::BISHOP;
                    pieceLocations = state.Board.BlackBishops;
                    break;
                case 4:
                    pieceType = PIECE::QUEEN;
                    pieceLocations = state.Board.BlackQueens;
                    break;
                case 5:
                    pieceType = PIECE::KING;
                    pieceLocations = state.Board.BlackKing;
                    break;
            }
            if (pieceType == PIECE::PAWN) {
                while (pieceLocations != 0) {
                    U64 lowest_piece = getLowestBit64(pieceLocations);
                    U64 PieceMoves = state.getPieceMoves(pieceType, lowest_piece, color);
                    while (PieceMoves != 0) {
                        U64 lowest_move = getLowestBit64(PieceMoves);
                        // look for promotions
                        if ((lowest_move & 0xff000000000000ffULL) != 0) {
                            locationForMoves.push_back(
                                    {(lowest_piece | lowest_move), pieceType, color, SIDES::NONE, PIECE::QUEEN});
                            locationForMoves.push_back(
                                    {(lowest_piece | lowest_move), pieceType, color, SIDES::NONE, PIECE::KNIGHT});
                            locationForMoves.push_back({(lowest_piece | lowest_move), pieceType, color, SIDES::NONE, PIECE::ROOK});
                            locationForMoves.push_back(
                                    {(lowest_piece | lowest_move), pieceType, color, SIDES::NONE, PIECE::BISHOP});
                        } else {
                            locationForMoves.push_back({(lowest_piece | lowest_move), pieceType, color});
                        }
                        PieceMoves ^= lowest_move;
                    }
                    pieceLocations ^= lowest_piece;
                }
            } else {
                while (pieceLocations != 0) {
                    U64 lowest_piece = getLowestBit64(pieceLocations);
                    U64 PieceMoves = state.getPieceMoves(pieceType, lowest_piece, color);
                    while (PieceMoves != 0) {
                        U64 lowest_move = getLowestBit64(PieceMoves);
                        locationForMoves.push_back({(lowest_piece | lowest_move), pieceType, color});
                        PieceMoves ^= lowest_move;
                    }
                    pieceLocations ^= lowest_piece;
                }
            }
        }
    }
}


void setDepth(int depth) {
    cout << "Depth: " << depth << endl;
    max_depth = depth;
}

int getDepth() {
    return max_depth;
}

bool checkForMate(board Game) {
    vector<Move> moves;
    moves.reserve(50);
    getMovesForPosition(Game, Game.Board.Player, moves);
    bool validMoves = false;
    for (Move m : moves) {
        if (tryMove(m, Game)) {
            validMoves = true;
            break;
        }
    }
    return !validMoves;
}

bool tryMove(Move move, board Game) {
    if (Game.makeMove(move)) {
        return true;
    } else {
        return false;
    }
}

string number_to_chess_coords(int num) {
    int n1 = num / 100;
    int n2 = num % 100;
    string coords = int_to_location_string[n1] + int_to_location_string[n2];
    return coords;
}

bool staleMate(board Game) {
    if (Game.Board.Player == COLOR::BLACK) {
        if ((Game.generateAttackMap(COLOR::WHITE) & Game.Board.BlackKing) != 0) {
            return false;
        } else {
            return true;
        }
    } else {
        if ((Game.generateAttackMap(COLOR::BLACK) & Game.Board.WhiteKing) != 0) {
            return false;
        } else {
            return true;
        }
    }
}

S8 getScorePrediction(board state, Move move) {
    S8 pieceValue;
    S8 score = 0;

    switch(move.movingPiece) {
        case PAWN:
            pieceValue = 1;
            break;
        case KNIGHT:
            pieceValue = 3;
            break;
        case ROOK:
            pieceValue = 5;
            break;
        case BISHOP:
            pieceValue = 3;
            break;
        case QUEEN:
            pieceValue = 9;
            break;
        case KING:
            pieceValue = 15;
            break;
    }

    if (move.color == WHITE) {
        if ((move.positions & state.Board.BlackPieces) != 0) {
            if ((state.Board.BlackPawns & move.positions) != 0) {
                return score + (1 - pieceValue);
            } else if ((state.Board.BlackKnights & move.positions) != 0 || (state.Board.BlackBishops & move.positions) != 0) {
                return score + (3 - pieceValue);
            } else if ((state.Board.BlackRooks & move.positions) != 0) {
                return score + (5 - pieceValue);
            } else if ((state.Board.BlackQueens & move.positions) != 0) {
                return score + (9 - pieceValue);
            }
        }
    } else {
        if ((move.positions & state.Board.WhitePieces) != 0) {
            if ((state.Board.WhitePawns & move.positions) != 0) {
                return score + (1 - pieceValue);
            } else if ((state.Board.WhiteKnights & move.positions) != 0 || (state.Board.WhiteBishops & move.positions) != 0) {
                return score + (3 - pieceValue);
            } else if ((state.Board.WhiteRooks & move.positions) != 0) {
                return score + (5 - pieceValue);
            } else if ((state.Board.WhiteQueens & move.positions) != 0) {
                return score + (9 - pieceValue);
            }
        }
    }
    return score;
}

bool checkForRepetition(board newState) {
    string fen = newState.getFEN(false);
    auto it = find(statesPreviouslyVisited.begin(), statesPreviouslyVisited.end(), fen);

    if (it != statesPreviouslyVisited.end()) {
        if (count(statesPreviouslyVisited.begin(), statesPreviouslyVisited.end(), fen) == 2) {
            return true;
        }
    }
    return false;
}

void initBook() {
    openingBook.initOpenings();
}
