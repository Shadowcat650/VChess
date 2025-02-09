//
// Created by ShadowCat650 on 4/3/23.
//

#include "gui.h"

PIECE selectedPiece;
COLOR selectedPieceColor;
U64 selectedPieceSquare;
PIECE promoteTo = PIECE::QUEEN;

int SEARCH_DEPTH = 5;

bool computerSearching = false;

COLOR player = COLOR::WHITE;

enum winConditions {
    white,
    black,
    draw,
    none
};

struct fenMove {
    string fen;
    Move move;
};

winConditions winner = none;

vector<string> statesVisited;

U64 highlightedSquares = 0;
U64 lastMovePositions = 0;

board Game;

vector<string> lastPosition;

vector<string> movesMade;

vector<fenMove> openingInstructions;

bool openingMode = false;

void loop(std::string fen) {

    // Create Window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Velocity Chess");
    window.setFramerateLimit(10);

    // Create the black and white tiles for the chess board
    sf::RectangleShape whiteTile(sf::Vector2f(100, 100));
    whiteTile.setFillColor(sf::Color (238,203,162,255));
    sf::RectangleShape blackTile(sf::Vector2f(100, 100));
    blackTile.setFillColor(sf::Color (198,112,60,255));

    // Create select tile
    sf::RectangleShape selectTile(sf::Vector2f(100, 100));
    selectTile.setFillColor(sf::Color (220, 235, 12, 100));

    // Create the movedTile
    sf::RectangleShape movedTile(sf::Vector2f(100, 100));
    movedTile.setFillColor(sf::Color (247, 51, 37, 70));

    // load text font
    sf::Font font;
    if (!font.loadFromFile("/Library/Fonts/Arial Unicode.ttf")) {
        cout << "Error loading text font" << endl;
    }

    // Create header
    sf::RectangleShape header(sf::Vector2f(400, 100));
    header.setFillColor(sf::Color (110, 112, 112, 255));
    header.setPosition(800, 0);

    sf::Text headerText("Velocity Chess Engine v.0", font, 30);
    headerText.setFillColor(sf::Color::Black);
    headerText.setStyle(sf::Text::Bold);
    sf::FloatRect textBounds = headerText.getLocalBounds();
    headerText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                         textBounds.top + textBounds.height / 2.0f);
    headerText.setPosition(header.getPosition() + header.getSize() / 2.0f);

    // Create Restart Button
    sf::RectangleShape restart(sf::Vector2f(400, 100));
    restart.setFillColor(sf::Color (90, 92, 92, 255));
    restart.setPosition(800, 100);

    sf::Text restartText("Restart", font, 30);
    restartText.setFillColor(sf::Color::Black);
    restartText.setStyle(sf::Text::Bold);
    textBounds = restartText.getLocalBounds();
    restartText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                         textBounds.top + textBounds.height / 2.0f);
    restartText.setPosition(restart.getPosition() + restart.getSize() / 2.0f);

    // Create loadLastFen Button
    sf::RectangleShape loadLast(sf::Vector2f(400, 100));
    loadLast.setFillColor(sf::Color (110, 112, 112, 255));
    loadLast.setPosition(800, 200);

    sf::Text loadLastText("Undo Move", font, 30);
    loadLastText.setFillColor(sf::Color::Black);
    loadLastText.setStyle(sf::Text::Bold);
    textBounds = loadLastText.getLocalBounds();
    loadLastText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                          textBounds.top + textBounds.height / 2.0f);
    loadLastText.setPosition(loadLast.getPosition() + loadLast.getSize() / 2.0f);

    // Create game over pop ups
    sf::RectangleShape gameOver(sf::Vector2f(250, 100));
    gameOver.setFillColor(sf::Color (90, 92, 92, 255));
    gameOver.setPosition(275, 350);

    sf::Text gameOverTextWhite("White wins!", font, 30);
    gameOverTextWhite.setFillColor(sf::Color::Black);
    gameOverTextWhite.setStyle(sf::Text::Bold);
    textBounds = gameOverTextWhite.getLocalBounds();
    gameOverTextWhite.setOrigin(textBounds.left + textBounds.width / 2.0f,
                          textBounds.top + textBounds.height / 2.0f);
    gameOverTextWhite.setPosition(gameOver.getPosition() + gameOver.getSize() / 2.0f);

    sf::Text gameOverTextBlack("Black wins!", font, 30);
    gameOverTextBlack.setFillColor(sf::Color::Black);
    gameOverTextBlack.setStyle(sf::Text::Bold);
    textBounds = gameOverTextBlack.getLocalBounds();
    gameOverTextBlack.setOrigin(textBounds.left + textBounds.width / 2.0f,
                           textBounds.top + textBounds.height / 2.0f);
    gameOverTextBlack.setPosition(gameOver.getPosition() + gameOver.getSize() / 2.0f);

    sf::Text gameOverTextDraw("It's a draw!", font, 30);
    gameOverTextDraw.setFillColor(sf::Color::Black);
    gameOverTextDraw.setStyle(sf::Text::Bold);
    textBounds = gameOverTextDraw.getLocalBounds();
    gameOverTextDraw.setOrigin(textBounds.left + textBounds.width / 2.0f,
                           textBounds.top + textBounds.height / 2.0f);
    gameOverTextDraw.setPosition(gameOver.getPosition() + gameOver.getSize() / 2.0f);



    // Create pieces
    sf::Texture whitePawnTexture;
    sf::Texture blackPawnTexture;
    sf::Texture whiteKnightTexture;
    sf::Texture blackKnightTexture;
    sf::Texture whiteRookTexture;
    sf::Texture blackRookTexture;
    sf::Texture whiteBishopTexture;
    sf::Texture blackBishopTexture;
    sf::Texture whiteQueenTexture;
    sf::Texture blackQueenTexture;
    sf::Texture whiteKingTexture;
    sf::Texture blackKingTexture;


    whitePawnTexture.loadFromFile("src/gui/assets/white_pawn.png");
    blackPawnTexture.loadFromFile("src/gui/assets/black_pawn.png");
    whiteKnightTexture.loadFromFile("src/gui/assets/white_knight.png");
    blackKnightTexture.loadFromFile("src/gui/assets/black_knight.png");
    whiteRookTexture.loadFromFile("src/gui/assets/white_rook.png");
    blackRookTexture.loadFromFile("src/gui/assets/black_rook.png");
    whiteBishopTexture.loadFromFile("src/gui/assets/white_bishop.png");
    blackBishopTexture.loadFromFile("src/gui/assets/black_bishop.png");
    whiteQueenTexture.loadFromFile("src/gui/assets/white_queen.png");
    blackQueenTexture.loadFromFile("src/gui/assets/black_queen.png");
    whiteKingTexture.loadFromFile("src/gui/assets/white_king.png");
    blackKingTexture.loadFromFile("src/gui/assets/black_king.png");


    sf::Sprite whitePawn(whitePawnTexture);
    sf::Sprite blackPawn(blackPawnTexture);
    sf::Sprite whiteKnight(whiteKnightTexture);
    sf::Sprite blackKnight(blackKnightTexture);
    sf::Sprite whiteRook(whiteRookTexture);
    sf::Sprite blackRook(blackRookTexture);
    sf::Sprite whiteBishop(whiteBishopTexture);
    sf::Sprite blackBishop(blackBishopTexture);
    sf::Sprite whiteQueen(whiteQueenTexture);
    sf::Sprite blackQueen(blackQueenTexture);
    sf::Sprite whiteKing(whiteKingTexture);
    sf::Sprite blackKing(blackKingTexture);


    whitePawn.setTextureRect(sf::IntRect(0, 0, 13, 16));
    blackPawn.setTextureRect(sf::IntRect(0, 0, 13, 16));
    whiteKnight.setTextureRect(sf::IntRect(0, 0, 16, 18));
    blackKnight.setTextureRect(sf::IntRect(0, 0, 16, 18));
    whiteRook.setTextureRect(sf::IntRect(0, 0, 14, 18));
    blackRook.setTextureRect(sf::IntRect(0, 0, 14, 18));
    whiteBishop.setTextureRect(sf::IntRect(0, 0, 18, 19));
    blackBishop.setTextureRect(sf::IntRect(0, 0, 18, 19));
    whiteQueen.setTextureRect(sf::IntRect(0, 0, 18, 18));
    blackQueen.setTextureRect(sf::IntRect(0, 0, 18, 18));
    whiteKing.setTextureRect(sf::IntRect(0, 0, 20, 20));
    blackKing.setTextureRect(sf::IntRect(0, 0, 20, 20));


    whitePawn.setScale(4.5f, 4.5f);
    blackPawn.setScale(4.5f, 4.5f);
    whiteKnight.setScale(4.5f, 4.5f);
    blackKnight.setScale(4.5f, 4.5f);
    whiteRook.setScale(4.5f, 4.5f);
    blackRook.setScale(4.5f, 4.5f);
    whiteBishop.setScale(4.5f, 4.5f);
    blackBishop.setScale(4.5f, 4.5f);
    whiteQueen.setScale(4.5f, 4.5f);
    blackQueen.setScale(4.5f, 4.5f);
    whiteKing.setScale(4.5f, 4.5f);
    blackKing.setScale(4.5f, 4.5f);

    if (fen != "startpos") {
        Game.loadPosition(fen);
    } else {
        Game.toStart();
    }

    lastPosition.push_back(Game.getFEN(true));

    bool firstPass = true;

    screen objectTracker;

    objectTracker.createObject(64, {800, 100}, 400, 100);
    objectTracker.createObject(65, {800, 200}, 400, 100);

    // Loop
    while (window.isOpen()) {
//        if (window.getSize().x != 800 || window.getSize().y) {
//            window.setSize({800, 800});
//        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    promoteTo = PIECE::QUEEN;
                } else if (event.key.code == sf::Keyboard::R) {
                    promoteTo = PIECE::ROOK;
                } else if (event.key.code == sf::Keyboard::K || event.key.code == sf::Keyboard::N) {
                    promoteTo = PIECE::KNIGHT;
                } else if (event.key.code == sf::Keyboard::B) {
                    promoteTo = PIECE::BISHOP;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
                    U8 objectClicked = objectTracker.getObjectClicked({clickPosition.x, clickPosition.y});
                    if (objectClicked != 255) {
                        if (objectClicked < 64) {
                            if (player == Game.Board.Player) {
                                U8 squareClicked = getSquareFromCoordinates(clickPosition.x, clickPosition.y);
                                if (((highlightedSquares & (LOCATION::ZERO >> squareClicked))) != 0) {
                                    U64 positions = (LOCATION::ZERO >> selectedPieceSquare) | (highlightedSquares & (LOCATION::ZERO >> squareClicked));
                                    if (selectedPiece == PIECE::KING) {
                                        if (positions == 0xa00000000000000ULL | positions == 0xaULL) {
                                            makeMove({positions, selectedPiece, selectedPieceColor, SIDES::KINGSIDE});
                                            lastMovePositions = positions;
                                        } else if (positions == 0x2800000000000000ULL | positions == 0x28ULL) {
                                            makeMove({positions, selectedPiece, selectedPieceColor, SIDES::QUEENSIDE});
                                            lastMovePositions = positions;
                                        } else {
                                            makeMove({positions, selectedPiece, selectedPieceColor});
                                            lastMovePositions = positions;
                                        }
                                    } else if (selectedPiece == PIECE::PAWN) {
                                        if ((positions & 0xff000000000000ff) != 0) {
                                            makeMove({positions, selectedPiece, selectedPieceColor, SIDES::NONE, promoteTo});
                                            lastMovePositions = positions;
                                        } else {
                                            makeMove({positions, selectedPiece, selectedPieceColor});
                                            lastMovePositions = positions;
                                        }
                                    } else {
                                        makeMove({positions, selectedPiece, selectedPieceColor});
                                        lastMovePositions = positions;
                                    }
                                } else if ((Game.Board.WhitePawns & (LOCATION::ZERO >> squareClicked)) != 0) {
                                    highlightedSquares = Game.getPieceMoves(PIECE::PAWN, LOCATION::ZERO >> squareClicked, COLOR::WHITE);
                                    selectedPiece = PIECE::PAWN;
                                    selectedPieceColor = COLOR::WHITE;
                                    selectedPieceSquare = squareClicked;
                                } else if ((Game.Board.BlackPawns & (LOCATION::ZERO >> squareClicked)) != 0) {
                                    highlightedSquares = Game.getPieceMoves(PIECE::PAWN, LOCATION::ZERO >> squareClicked, COLOR::BLACK);
                                    selectedPiece = PIECE::PAWN;
                                    selectedPieceColor = COLOR::BLACK;
                                    selectedPieceSquare = squareClicked;
                                } else if ((Game.Board.WhiteKnights & (LOCATION::ZERO >> squareClicked)) != 0) {
                                    highlightedSquares = Game.getPieceMoves(PIECE::KNIGHT, LOCATION::ZERO >> squareClicked, COLOR::WHITE);
                                    selectedPiece = PIECE::KNIGHT;
                                    selectedPieceColor = COLOR::WHITE;
                                    selectedPieceSquare = squareClicked;
                                }
                                else if ((Game.Board.BlackKnights & (LOCATION::ZERO >> squareClicked)) != 0) {
                                    highlightedSquares = Game.getPieceMoves(PIECE::KNIGHT, LOCATION::ZERO >> squareClicked, COLOR::BLACK);
                                    selectedPiece = PIECE::KNIGHT;
                                    selectedPieceColor = COLOR::BLACK;
                                    selectedPieceSquare = squareClicked;
                                } else if ((Game.Board.WhiteRooks & (LOCATION::ZERO >> squareClicked)) != 0) {
                                    highlightedSquares = Game.getPieceMoves(PIECE::ROOK, LOCATION::ZERO >> squareClicked, COLOR::WHITE);
                                    selectedPiece = PIECE::ROOK;
                                    selectedPieceColor = COLOR::WHITE;
                                    selectedPieceSquare = squareClicked;
                                }
                                else if ((Game.Board.BlackRooks & (LOCATION::ZERO >> squareClicked)) != 0) {
                                    highlightedSquares = Game.getPieceMoves(PIECE::ROOK, LOCATION::ZERO >> squareClicked, COLOR::BLACK);
                                    selectedPiece = PIECE::ROOK;
                                    selectedPieceColor = COLOR::BLACK;
                                    selectedPieceSquare = squareClicked;
                                }
                                else if ((Game.Board.WhiteBishops & (LOCATION::ZERO >> squareClicked)) != 0) {
                                    highlightedSquares = Game.getPieceMoves(PIECE::BISHOP, LOCATION::ZERO >> squareClicked, COLOR::WHITE);
                                    selectedPiece = PIECE::BISHOP;
                                    selectedPieceColor = COLOR::WHITE;
                                    selectedPieceSquare = squareClicked;
                                }
                                else if ((Game.Board.BlackBishops & (LOCATION::ZERO >> squareClicked)) != 0) {
                                    highlightedSquares = Game.getPieceMoves(PIECE::BISHOP, LOCATION::ZERO >> squareClicked, COLOR::BLACK);
                                    selectedPiece = PIECE::BISHOP;
                                    selectedPieceColor = COLOR::BLACK;
                                    selectedPieceSquare = squareClicked;
                                }
                                else if ((Game.Board.WhiteQueens & (LOCATION::ZERO >> squareClicked)) != 0) {
                                    highlightedSquares = Game.getPieceMoves(PIECE::QUEEN, LOCATION::ZERO >> squareClicked, COLOR::WHITE);
                                    selectedPiece = PIECE::QUEEN;
                                    selectedPieceColor = COLOR::WHITE;
                                    selectedPieceSquare = squareClicked;
                                }
                                else if ((Game.Board.BlackQueens & (LOCATION::ZERO >> squareClicked)) != 0) {
                                    highlightedSquares = Game.getPieceMoves(PIECE::QUEEN, LOCATION::ZERO >> squareClicked, COLOR::BLACK);
                                    selectedPiece = PIECE::QUEEN;
                                    selectedPieceColor = COLOR::BLACK;
                                    selectedPieceSquare = squareClicked;
                                }
                                else if ((Game.Board.WhiteKing & (LOCATION::ZERO >> squareClicked)) != 0) {
                                    highlightedSquares = Game.getPieceMoves(PIECE::KING, LOCATION::ZERO >> squareClicked, COLOR::WHITE);
                                    if (Game.Board.WhiteKingside) {
                                        highlightedSquares |= LOCATION::ZERO >> 6;
                                    }
                                    if (Game.Board.WhiteQueenside) {
                                        highlightedSquares |= LOCATION::ZERO >> 2;
                                    }
                                    selectedPiece = PIECE::KING;
                                    selectedPieceColor = COLOR::WHITE;
                                    selectedPieceSquare = squareClicked;
                                }
                                else if ((Game.Board.BlackKing & (LOCATION::ZERO >> squareClicked)) != 0) {
                                    highlightedSquares = Game.getPieceMoves(PIECE::KING, LOCATION::ZERO >> squareClicked, COLOR::BLACK);
                                    if (Game.Board.BlackKingside) {
                                        highlightedSquares |= LOCATION::ZERO >> 62;
                                    }
                                    if (Game.Board.BlackQueenside) {
                                        highlightedSquares |= LOCATION::ZERO >> 58;
                                    }
                                    selectedPiece = PIECE::KING;
                                    selectedPieceColor = COLOR::BLACK;
                                    selectedPieceSquare = squareClicked;
                                }  else {
                                    highlightedSquares = 0;
                                }
                                if (!computerSearching && player != Game.Board.Player) {
                                    computerSearching = true;
                                    move_nodes data = find_best_move(Game, SEARCH_DEPTH, statesVisited);
                                    Move computerMove = data.move;
                                    Game.makeMove(computerMove);
                                    lastMovePositions = computerMove.positions;
                                    movesMade.push_back(getStringForMove(computerMove, Game));
                                    if (checkForDraw(Game)) {
                                        winner = draw;
                                    }
                                    statesVisited.push_back(Game.getFEN(false));
                                    if (checkForMate(Game)) {
                                        handleMate(Game);
                                    }
                                    computerSearching = false;
                                }
                            } else {

                            }
                        } else if (objectClicked == 64){
                            Game.toStart();
                            winner = none;
                            player = player;
                            statesVisited = {};
                            lastMovePositions = 0;
                            if (player == COLOR::BLACK) {
                                computerSearching = true;
                                move_nodes data = find_best_move(Game, SEARCH_DEPTH, statesVisited);
                                Move computerMove = data.move;
                                Game.makeMove(computerMove);
                                lastMovePositions = computerMove.positions;
                                movesMade.push_back(getStringForMove(computerMove, Game));
                                if (checkForDraw(Game)) {
                                    winner = draw;
                                }
                                statesVisited.push_back(Game.getFEN(false));
                                if (checkForMate(Game)) {
                                    handleMate(Game);
                                }
                                computerSearching = false;
                            }
                        } else if (objectClicked == 65) {
                            if (!lastPosition.empty()) {
                                auto it = std::find(statesVisited.begin(), statesVisited.end(), Game.getFEN(false));
                                if (it != statesVisited.end()) {
                                    statesVisited.erase(it);
                                }
                                auto lastPos = lastPosition.back();
                                Game.loadPosition(lastPos);
                                lastPosition.pop_back();
                            }
                        }
                    }
                }
                if (selectedPieceColor != Game.Board.Player) {
                    highlightedSquares = 0;
                } else {
                    highlightedSquares = pruneIllegal(highlightedSquares, Game);
                }
            }
        }

        window.clear({51, 44, 59, 100});
        // Render Objects
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                // Render Squares
                if (squareIsWhite((j +(i * 8)))) {
                    whiteTile.setPosition(j * 100, (7 - i) * 100);
                    window.draw(whiteTile);
                } else {
                    blackTile.setPosition(j * 100, (7 - i) * 100);
                    window.draw(blackTile);
                }

                if (firstPass) {
                    objectTracker.createObject((8 * i) + j, {j * 100, (7 - i) * 100}, 100, 100);
                }

                // Render Pieces
                if ((Game.Board.WhitePawns & (LOCATION::ZERO >> (j +(i * 8)))) != 0) {
                    whitePawn.setPosition((j * 100) + 20.75, ((7 - i) * 100) + 14);
                    window.draw(whitePawn);
                } else if ((Game.Board.BlackPawns & (LOCATION::ZERO >> (j + (i * 8)))) != 0) {
                    blackPawn.setPosition((j * 100) + 20.75, ((7 - i) * 100) + 14);
                    window.draw(blackPawn);
                } else if ((Game.Board.WhiteKnights & (LOCATION::ZERO >> (j + (i * 8)))) != 0) {
                    whiteKnight.setPosition((j * 100) + 14, ((7 - i) * 100) + 9.5);
                    window.draw(whiteKnight);
                }
                else if ((Game.Board.BlackKnights & (LOCATION::ZERO >> (j + (i * 8)))) != 0) {
                    blackKnight.setPosition((j * 100) + 14, ((7 - i) * 100) + 9.5);
                    window.draw(blackKnight);
                } else if ((Game.Board.WhiteRooks & (LOCATION::ZERO >> (j + (i * 8)))) != 0) {
                    whiteRook.setPosition((j * 100) + 18.5, ((7 - i) * 100) + 9.5);
                    window.draw(whiteRook);
                }
                else if ((Game.Board.BlackRooks & (LOCATION::ZERO >> (j + (i * 8)))) != 0) {
                    blackRook.setPosition((j * 100) + 18.5, ((7 - i) * 100) + 9.5);
                    window.draw(blackRook);
                }
                else if ((Game.Board.WhiteBishops & (LOCATION::ZERO >> (j + (i * 8)))) != 0) {
                    whiteBishop.setPosition((j * 100) + 9.5, ((7 - i) * 100) + 7.25);
                    window.draw(whiteBishop);
                }
                else if ((Game.Board.BlackBishops & (LOCATION::ZERO >> (j + (i * 8)))) != 0) {
                    blackBishop.setPosition((j * 100) + 9.5, ((7 - i) * 100) + 7.25);
                    window.draw(blackBishop);
                }
                else if ((Game.Board.WhiteQueens & (LOCATION::ZERO >> (j + (i * 8)))) != 0) {
                    whiteQueen.setPosition((j * 100) + 9.5, ((7 - i) * 100) + 9.5);
                    window.draw(whiteQueen);
                 }
                else if ((Game.Board.BlackQueens & (LOCATION::ZERO >> (j + (i * 8)))) != 0) {
                    blackQueen.setPosition((j * 100) + 9.5, ((7 - i) * 100) + 9.5);
                    window.draw(blackQueen);
                }
                else if ((Game.Board.WhiteKing & (LOCATION::ZERO >> (j + (i * 8)))) != 0) {
                    whiteKing.setPosition((j * 100) + 5, ((7 - i) * 100) + 5);
                    window.draw(whiteKing);
                }
                else if ((Game.Board.BlackKing & (LOCATION::ZERO >> (j + (i * 8)))) != 0) {
                    blackKing.setPosition((j * 100) + 5, ((7 - i) * 100) + 5);
                    window.draw(blackKing);
                }

                // Render Highlights

                if (((LOCATION::ZERO >> (j +(i * 8))) & lastMovePositions) != 0) {
                    movedTile.setPosition(j * 100, (7 - i) * 100);
                    window.draw(movedTile);
                }
                if (((LOCATION::ZERO >> (j +(i * 8))) & highlightedSquares) != 0) {
                    selectTile.setPosition(j * 100, (7 - i) * 100);
                    window.draw(selectTile);
                }
            }
        }
        // Render controls
        window.draw(header);
        window.draw(headerText);
        window.draw(restart);
        window.draw(restartText);
        window.draw(loadLast);
        window.draw(loadLastText);

        if (winner != none) {
            window.draw(gameOver);
            switch (winner) {
                case white:
                    window.draw(gameOverTextWhite);
                    break;
                case black:
                    window.draw(gameOverTextBlack);
                    break;
                case draw:
                    window.draw(gameOverTextDraw);
                    break;
            }
        }

        switch (promoteTo) {
            case QUEEN:
                whiteQueen.setPosition(814, 709.5);
                window.draw(whiteQueen);
                break;
            case KNIGHT:
                whiteKnight.setPosition(814, 709.5);
                window.draw(whiteKnight);
                break;
            case BISHOP:
                whiteBishop.setPosition(809.5, 707.25);
                window.draw(whiteBishop);
                break;
            case ROOK:
                whiteRook.setPosition(818.5, 709.5);
                window.draw(whiteRook);
                break;
            default:
                break;
        }

        if (firstPass) {
            firstPass = false;
        }
        window.display();
    }
    exit(0);
}

bool squareIsWhite(U64 square) {
    return ((LOCATION::ZERO >> square) & 0x55aa55aa55aa55aaULL) != 0;
}

U8 getSquareFromCoordinates(int x, int y) {
    return (x / 100) + (8 * ((7 - (y / 100))));
}

bool testMove(U64 moveFrom, board Game) {
    U64 positions = (LOCATION::ZERO >> selectedPieceSquare) | moveFrom;
    if (selectedPiece == PIECE::KING) {
        if (positions == 0xa00000000000000ULL | positions == 0xaULL) {
            if (Game.makeMove({positions, selectedPiece, selectedPieceColor, SIDES::KINGSIDE})) {
                return true;
            } else {
                return false;
            }
        } else if (positions == 0x2800000000000000ULL | positions == 0x28ULL) {
            if (Game.makeMove({positions, selectedPiece, selectedPieceColor, SIDES::QUEENSIDE})) {
                return true;
            } else {
                return false;
            }
        } else {
            if (Game.makeMove({positions, selectedPiece, selectedPieceColor})) {
                return true;
            } else {
                return false;
            }
        }
    } else if (selectedPiece == PIECE::PAWN) {
        if ((positions & 0xff000000000000ff) != 0) {
            if (Game.makeMove({positions, selectedPiece, selectedPieceColor, SIDES::NONE, promoteTo})) {
                return true;
            } else {
                return false;
            }
        } else {
            if (Game.makeMove({positions, selectedPiece, selectedPieceColor})) {
                return true;
            } else {
                return false;
            }
        }
    } else if (Game.makeMove({positions, selectedPiece, selectedPieceColor})) {
        return true;
    } else {
        return false;
    }
}

void makeMove(Move move) {
    string position = Game.getFEN(true);
    if (Game.makeMove(move)) {
        if (openingMode) {
            openingInstructions.push_back({position, move});
        }
        lastPosition.push_back(position);
        movesMade.push_back(getStringForMove(move, Game));
        if (checkForDraw(Game)) {
            winner = draw;
        }
        statesVisited.push_back(Game.getFEN(false));
        highlightedSquares = 0;
        if (checkForMate(Game)) {
            handleMate(Game);
        }
    }
}


U64 pruneIllegal(U64 movesToPrune, board Game) {
    U64 newMoves = movesToPrune;
    while (movesToPrune != 0) {
        U64 lowest = getLowestBit64(movesToPrune);
        if (!testMove(lowest, Game)) {
            newMoves ^= lowest;
        }
        movesToPrune ^= lowest;
    }
    return newMoves;
}

void handleMate(board Game) {
    if (Game.Board.Player == COLOR::BLACK) {
        if (!staleMate(Game)) {
            winner = white;
        } else {
            winner = draw;
        }
    } else {
        if (!staleMate(Game)) {
            winner = black;
        } else {
            winner = draw;
        }
    }
}

bool checkForDraw(board state) {
    if (state.Board.HalfMoveClock == 50) {
        return true;
    }

    string fen = state.getFEN(false);
    auto it = find(statesVisited.begin(), statesVisited.end(), fen);

    if (it != statesVisited.end()) {
        if (count(statesVisited.begin(), statesVisited.end(), fen) == 2) {
            return true;
        }
    }
    return false;
}

void printOpeningInstructions(COLOR forColor) {
    vector<string> usedFEN;
    for (fenMove instruction : openingInstructions) {
        auto it = find(usedFEN.begin(), usedFEN.end(), instruction.fen);
        if (it == usedFEN.end()) {
            usedFEN.push_back(instruction.fen);
            if (instruction.move.color == COLOR::WHITE && forColor == WHITE) {
                switch(instruction.move.movingPiece) {
                    case PAWN:
                        if (instruction.move.queen != PIECE::PAWN) {
                            switch (instruction.move.queen) {
                                case QUEEN:
                                    cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, PAWN, WHITE, NONE, QUEEN}});" << endl;
                                    break;
                                case KNIGHT:
                                    cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, PAWN, WHITE, NONE, KNIGHT}});" << endl;
                                    break;
                                case BISHOP:
                                    cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, PAWN, WHITE, NONE, BISHOP}});" << endl;
                                    break;
                                case ROOK:
                                    cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, PAWN, WHITE, NONE, ROOK}});" << endl;
                                    break;
                            }
                        } else {
                            cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, PAWN, WHITE}});" << endl;
                        }
                        break;
                    case KNIGHT:
                        cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, KNIGHT, WHITE}});" << endl;
                        break;
                    case ROOK:
                        cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, ROOK, WHITE}});" << endl;
                        break;
                    case BISHOP:
                        cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, BISHOP, WHITE}});" << endl;
                        break;
                    case QUEEN:
                        cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, QUEEN, WHITE}});" << endl;
                        break;
                    case KING:
                        if (instruction.move.castle != SIDES::NONE) {
                            if (instruction.move.castle == SIDES::KINGSIDE) {
                                cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, KING, WHITE, KINGSIDE}});" << endl;
                            } else {
                                cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, KING, WHITE, QUEENSIDE}});" << endl;
                            }
                        } else {
                            cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, KING, WHITE}});" << endl;
                        }
                        break;
                }
            } else if (instruction.move.color == COLOR::BLACK && forColor == BLACK) {
                switch(instruction.move.movingPiece) {
                    case PAWN:
                        if (instruction.move.queen != PIECE::PAWN) {
                            switch (instruction.move.queen) {
                                case QUEEN:
                                    cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, PAWN, BLACK, NONE, QUEEN}});" << endl;
                                    break;
                                case KNIGHT:
                                    cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, PAWN, BLACK, NONE, KNIGHT}});" << endl;
                                    break;
                                case BISHOP:
                                    cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, PAWN, BLACK, NONE, BISHOP}});" << endl;
                                    break;
                                case ROOK:
                                    cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, PAWN, BLACK, NONE, ROOK}});" << endl;
                                    break;
                            }
                        } else {
                            cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, PAWN, BLACK}});" << endl;
                        }
                        break;
                    case KNIGHT:
                        cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, KNIGHT, BLACK}});" << endl;
                        break;
                    case ROOK:
                        cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, ROOK, BLACK}});" << endl;
                        break;
                    case BISHOP:
                        cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, BISHOP, BLACK}});" << endl;
                        break;
                    case QUEEN:
                        cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, QUEEN, BLACK}});" << endl;
                        break;
                    case KING:
                        if (instruction.move.castle != SIDES::NONE) {
                            if (instruction.move.castle == SIDES::KINGSIDE) {
                                cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, KING, BLACK, KINGSIDE}});" << endl;
                            } else {
                                cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, KING, BLACK, QUEENSIDE}});" << endl;
                            }
                        } else {
                            cout << "openingPositions.push_back({'" << instruction.fen << "', {0x" <<  hex << instruction.move.positions << "ULL, KING, BLACK}});" << endl;
                        }
                        break;
                }
            }
        }
    }
}
