//
// Created by ShadowCat650 on 3/22/23.
//

#include <sstream>
#include "uci.h"

board currentBoard;
int target_depth = 4;

void uci() {
    string input;
    id();
    while (getline(cin, input)) {
        if (input == "uci") {
            id();
        } else if (input == "isready") {
            isReady();
        } else if (input == "ucinewgame") {
            newGame();
        } else if (input.substr(0, 8) == "position") {
            position(input);
        } else if (input.substr(0, 2) == "go") {
            go();
        } else if (input == "stop") {
            setDepth(0);
        } else if (input == "quit") {
            setDepth(0);
            break;
        } else if (input.substr(0, 9) == "setoption") {
            setOption(input);
        }
    }
}

void id() {
    // identify with id
    // send option command
    // uciok
    cout << "id name VelocityChess\n";
    cout << "id author ShadowCat650\n";
    cout << "uciok\n";
}

void isReady() {
    cout << "readyok\n";
}

void go() {
    move_nodes moveFound = find_best_move(currentBoard, target_depth, {});
    cout << "info nodes " << moveFound.nodes << "\n";
    cout << "info depth " << getDepth() << "\n";
    cout << "bestmove " << getStringForMove(moveFound.move, currentBoard) << "\n";
}

void position(string input) {
    if (input.substr(9, 8) == "startpos") {
        currentBoard.toStart();
    } else {
        size_t fenPos = input.find("fen");
        size_t movesPos = input.find("moves");
        size_t startPos = (fenPos != string::npos) ? fenPos : movesPos;
        if (startPos != string::npos) {
            size_t spacePos = input.find(' ', startPos + 1);
            string fen = input.substr(spacePos + 1, (movesPos != string::npos) ? movesPos - spacePos - 1 : input.length() - spacePos - 1);
            currentBoard.loadPosition(fen);
        }
    }
    std::vector<std::string> moves;
    std::size_t pos = input.find("moves");
    if (pos != std::string::npos && pos + 6 < input.length()) {
        std::string movesString = input.substr(pos + 6); // "moves " has 6 characters
        std::istringstream iss(movesString);
        std::string token;
        while (iss >> token) {
            moves.push_back(token);
        }
    }
    for (string move : moves) {
        if (move.length() == 4) {
            U64 firstLocation = LOCATION::ZERO >> Precomputed.locationStringToInt[move.substr(0, 2)];
            U64 secondLocation = LOCATION::ZERO >> Precomputed.locationStringToInt[move.substr(2, 2)];
            PIECE moving  = findPieceMoving(firstLocation);
            if (moving == PIECE::KING) {
                if (((firstLocation | secondLocation) & 0xa00000000000000ULL) != 0) {
                    currentBoard.makeMove({(firstLocation | secondLocation), moving, currentBoard.Board.Player, SIDES::KINGSIDE});
                } else if (((firstLocation | secondLocation) & 0x2800000000000000ULL) != 0) {
                    currentBoard.makeMove({(firstLocation | secondLocation), moving, currentBoard.Board.Player, SIDES::QUEENSIDE});
                } else if (((firstLocation | secondLocation) & 0xaULL) != 0) {
                    currentBoard.makeMove({(firstLocation | secondLocation), moving, currentBoard.Board.Player, SIDES::KINGSIDE});
                } else if (((firstLocation | secondLocation) & 0x28ULL) != 0) {
                    currentBoard.makeMove({(firstLocation | secondLocation), moving, currentBoard.Board.Player, SIDES::QUEENSIDE});
                } else {
                    currentBoard.makeMove({(firstLocation | secondLocation), moving, currentBoard.Board.Player});
                }
            } else {
                currentBoard.makeMove({(firstLocation | secondLocation), moving, currentBoard.Board.Player});
            }
        } else {
            U64 firstLocation = LOCATION::ZERO >> Precomputed.locationStringToInt[move.substr(0, 2)];
            U64 secondLocation = LOCATION::ZERO >> Precomputed.locationStringToInt[move.substr(2, 2)];
            PIECE moving  = findPieceMoving(firstLocation);
            char promotion = move[4];
            switch (promotion) {
                case 'q':
                    currentBoard.makeMove({(firstLocation | secondLocation), moving, currentBoard.Board.Player, SIDES::NONE, PIECE::QUEEN});
                    break;
                case 'n':
                    currentBoard.makeMove({(firstLocation | secondLocation), moving, currentBoard.Board.Player, SIDES::NONE, PIECE::KNIGHT});
                    break;
                case 'r':
                    currentBoard.makeMove({(firstLocation | secondLocation), moving, currentBoard.Board.Player, SIDES::NONE, PIECE::ROOK});
                    break;
                case 'b':
                    currentBoard.makeMove({(firstLocation | secondLocation), moving, currentBoard.Board.Player, SIDES::NONE, PIECE::BISHOP});
                    break;
            }
        }
    }
}

void newGame() {
currentBoard.toStart();
}

PIECE findPieceMoving(U64 position) {
        if (((currentBoard.Board.WhitePawns | currentBoard.Board.BlackPawns) & position) != 0) {
            return PIECE::PAWN;
        }
        if (((currentBoard.Board.WhiteRooks | currentBoard.Board.BlackRooks) & position) != 0) {
            return PIECE::ROOK;
        }
        if (((currentBoard.Board.WhiteBishops | currentBoard.Board.BlackBishops) & position) != 0) {
            return PIECE::BISHOP;
        }
        if (((currentBoard.Board.WhiteKnights | currentBoard.Board.BlackKnights) & position) != 0) {
            return PIECE::KNIGHT;
        }
        if (((currentBoard.Board.WhiteQueens | currentBoard.Board.BlackQueens) & position) != 0) {
            return PIECE::QUEEN;
        }
        if (((currentBoard.Board.WhiteKing | currentBoard.Board.BlackKing) & position) != 0) {
            return PIECE::KING;
        }
    return PAWN;
}

string getStringForMove(Move move, board Board) {
    U64 originLocation;
    U8 originSquare;
    U8 endSquare;
    switch (move.movingPiece) {
        case PAWN:
            originLocation = (Board.Board.WhitePawns | Board.Board.BlackPawns) & move.positions;
            endSquare = 63 - __builtin_ctzll(originLocation);
            originSquare = 63 - __builtin_ctzll(originLocation ^ move.positions);
            if (move.queen != PIECE::PAWN) {
                switch (move.queen) {
                    case QUEEN:
                        return int_to_location_string[originSquare] + int_to_location_string[endSquare] + "q";
                    case KNIGHT:
                        return int_to_location_string[originSquare] + int_to_location_string[endSquare] + "q";
                    case ROOK:
                        return int_to_location_string[originSquare] + int_to_location_string[endSquare] + "q";
                    case BISHOP:
                        return int_to_location_string[originSquare] + int_to_location_string[endSquare] + "q";
                }
            } else {
                return int_to_location_string[originSquare] + int_to_location_string[endSquare];
            }
        case KNIGHT:
            originLocation = (Board.Board.WhiteKnights | Board.Board.BlackKnights) & move.positions;
            originSquare = 63 - __builtin_ctzll(originLocation);
            endSquare = 63 - __builtin_ctzll(originLocation ^ move.positions);
            return int_to_location_string[originSquare] + int_to_location_string[endSquare];
        case ROOK:
            originLocation = (Board.Board.WhiteRooks | Board.Board.BlackRooks) & move.positions;
            originSquare = 63 - __builtin_ctzll(originLocation);
            endSquare = 63 - __builtin_ctzll(originLocation ^ move.positions);
            return int_to_location_string[originSquare] + int_to_location_string[endSquare];
        case BISHOP:
            originLocation = (Board.Board.WhiteBishops | Board.Board.BlackBishops) & move.positions;
            originSquare = 63 - __builtin_ctzll(originLocation);
            endSquare = 63 - __builtin_ctzll(originLocation ^ move.positions);
            return int_to_location_string[originSquare] + int_to_location_string[endSquare];
        case QUEEN:
            originLocation = (Board.Board.WhiteQueens | Board.Board.BlackQueens) & move.positions;
            originSquare = 63 - __builtin_ctzll(originLocation);
            endSquare = 63 - __builtin_ctzll(originLocation ^ move.positions);
            return int_to_location_string[originSquare] + int_to_location_string[endSquare];
        case KING:
            originLocation = (Board.Board.WhiteKing | Board.Board.BlackKing) & move.positions;
            originSquare = 63 - __builtin_ctzll(originLocation);
            endSquare = 63 - __builtin_ctzll(originLocation ^ move.positions);
            return int_to_location_string[originSquare] + int_to_location_string[endSquare];
    }
}

void setOption(string input) {
    size_t idPos = input.find("name ") + 5;
    size_t idEndPos = input.find(" ", idPos);
    string optionId = input.substr(idPos, idEndPos - idPos);

    // Extract the option value (if present)
    size_t valuePos = input.find("value ");
    string optionValueStr;
    if (valuePos != string::npos) {
        size_t valueStartPos = valuePos + 6;
        optionValueStr = input.substr(valueStartPos);
    }


    // Handle the depth option
    if (optionId == "depth") {
        if (!optionValueStr.empty()) {
            target_depth = (stoi(input.substr(valuePos + 6)));
        }
    }
}
