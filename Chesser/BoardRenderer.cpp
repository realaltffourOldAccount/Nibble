//#include "BoardRenderer.h"

// void BoardRenderer::Init(ResourceManager* res, MoveMaker* _maker,
//                         Board* _board) {
//    maker = _maker;
//    board = _board;
//    mBoard = new sf::Sprite();
//    board_tex = new sf::Texture();
//    board_tex->loadFromFile("assets/board.png", sf::IntRect(0, 0, 512, 512));
//
//    pieces_tex = new sf::Texture();
//    pieces_tex->loadFromFile("assets/pieces.png", sf::IntRect(0, 0, 1280,
//    427));
//
//    mBoard->setTexture(*board_tex);
//    mBoard->setScale(sf::Vector2f(700.0f / (float)board_tex->getSize().x,
//                                  700.0f / (float)board_tex->getSize().y));
//
//    // White pieces
//
//    mWhiteKing = new sf::Sprite();
//    mWhiteKing->setTexture(*pieces_tex);
//    mWhiteKing->setTextureRect(sf::IntRect(0, 0, pieces_tex->getSize().x / 6,
//                                           pieces_tex->getSize().y / 2));
//    mWhiteKing->setOrigin(mWhiteKing->getLocalBounds().width / 2,
//                          mWhiteKing->getLocalBounds().height / 2);
//    mWhiteKing->setScale(CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                         CELL_H / float(pieces_tex->getSize().y / 2.0f));
//
//    mWhiteQueen = new sf::Sprite();
//    mWhiteQueen->setTexture(*pieces_tex);
//    mWhiteQueen->setTextureRect(sf::IntRect(pieces_tex->getSize().x / 6, 0,
//                                            pieces_tex->getSize().x / 6,
//                                            pieces_tex->getSize().y / 2));
//    mWhiteQueen->setOrigin(mWhiteQueen->getLocalBounds().width / 2,
//                           mWhiteQueen->getLocalBounds().height / 2);
//    mWhiteQueen->setScale(CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                          CELL_H / float(pieces_tex->getSize().y / 2.0f));
//
//    mWhiteRook = new sf::Sprite();
//    mWhiteRook->setTexture(*pieces_tex);
//    mWhiteRook->setTextureRect(sf::IntRect(4 * (pieces_tex->getSize().x / 6),
//    0,
//                                           pieces_tex->getSize().x / 6,
//                                           pieces_tex->getSize().y / 2));
//    mWhiteRook->setOrigin(mWhiteRook->getLocalBounds().width / 2,
//                          mWhiteRook->getLocalBounds().height / 2);
//    mWhiteRook->setScale(CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                         CELL_H / float(pieces_tex->getSize().y / 2.0f));
//
//    mWhiteBishop = new sf::Sprite();
//    mWhiteBishop->setTexture(*pieces_tex);
//    mWhiteBishop->setTextureRect(sf::IntRect(2 * (pieces_tex->getSize().x /
//    6),
//                                             0, pieces_tex->getSize().x / 6,
//                                             pieces_tex->getSize().y / 2));
//    mWhiteBishop->setOrigin(mWhiteBishop->getLocalBounds().width / 2,
//                            mWhiteBishop->getLocalBounds().height / 2);
//    mWhiteBishop->setScale(CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                           CELL_H / float(pieces_tex->getSize().y / 2.0f));
//
//    mWhiteKnight = new sf::Sprite();
//    mWhiteKnight->setTexture(*pieces_tex);
//    mWhiteKnight->setTextureRect(sf::IntRect(3 * (pieces_tex->getSize().x /
//    6),
//                                             0, pieces_tex->getSize().x / 6,
//                                             pieces_tex->getSize().y / 2));
//    mWhiteKnight->setOrigin(mWhiteKnight->getLocalBounds().width / 2,
//                            mWhiteKnight->getLocalBounds().height / 2);
//    mWhiteKnight->setScale(CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                           CELL_H / float(pieces_tex->getSize().y / 2.0f));
//
//    mWhitePawn = new sf::Sprite();
//    mWhitePawn->setTexture(*pieces_tex);
//    mWhitePawn->setTextureRect(sf::IntRect(5 * (pieces_tex->getSize().x / 6),
//    0,
//                                           pieces_tex->getSize().x / 6,
//                                           pieces_tex->getSize().y / 2));
//    mWhitePawn->setOrigin(mWhitePawn->getLocalBounds().width / 2,
//                          mWhitePawn->getLocalBounds().height / 2);
//    mWhitePawn->setScale(CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                         CELL_H / float(pieces_tex->getSize().y / 2.0f));
//
//    // Black pieces
//
//    mBlackKing = new sf::Sprite();
//    mBlackKing->setTexture(*pieces_tex);
//    mBlackKing->setTextureRect(sf::IntRect(0, pieces_tex->getSize().y / 2,
//                                           pieces_tex->getSize().x / 6,
//                                           pieces_tex->getSize().y / 2));
//    mBlackKing->setOrigin(mBlackKing->getLocalBounds().width / 2,
//                          mBlackKing->getLocalBounds().height / 2);
//    mBlackKing->setScale(CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                         CELL_H / float(pieces_tex->getSize().y / 2.0f));
//
//    mBlackQueen = new sf::Sprite();
//    mBlackQueen->setTexture(*pieces_tex);
//    mBlackQueen->setTextureRect(
//        sf::IntRect(pieces_tex->getSize().x / 6, pieces_tex->getSize().y / 2,
//                    pieces_tex->getSize().x / 6, pieces_tex->getSize().y /
//                    2));
//    mBlackQueen->setOrigin(mBlackQueen->getLocalBounds().width / 2,
//                           mBlackQueen->getLocalBounds().height / 2);
//    mBlackQueen->setScale(CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                          CELL_H / float(pieces_tex->getSize().y / 2.0f));
//
//    mBlackRook = new sf::Sprite();
//    mBlackRook->setTexture(*pieces_tex);
//    mBlackRook->setTextureRect(sf::IntRect(
//        4 * (pieces_tex->getSize().x / 6), pieces_tex->getSize().y / 2,
//        pieces_tex->getSize().x / 6, pieces_tex->getSize().y / 2));
//    mBlackRook->setOrigin(mBlackRook->getLocalBounds().width / 2,
//                          mBlackRook->getLocalBounds().height / 2);
//    mBlackRook->setScale(CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                         CELL_H / float(pieces_tex->getSize().y / 2.0f));
//
//    mBlackBishop = new sf::Sprite();
//    mBlackBishop->setTexture(*pieces_tex);
//    mBlackBishop->setTextureRect(sf::IntRect(
//        2 * (pieces_tex->getSize().x / 6), pieces_tex->getSize().y / 2,
//        pieces_tex->getSize().x / 6, pieces_tex->getSize().y / 2));
//    mBlackBishop->setOrigin(mBlackBishop->getLocalBounds().width / 2,
//                            mBlackBishop->getLocalBounds().height / 2);
//    mBlackBishop->setScale(CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                           CELL_H / float(pieces_tex->getSize().y / 2.0f));
//
//    mBlackKnight = new sf::Sprite();
//    mBlackKnight->setTexture(*pieces_tex);
//    mBlackKnight->setTextureRect(sf::IntRect(
//        3 * (pieces_tex->getSize().x / 6), pieces_tex->getSize().y / 2,
//        pieces_tex->getSize().x / 6, pieces_tex->getSize().y / 2));
//    mBlackKnight->setOrigin(mBlackKnight->getLocalBounds().width / 2,
//                            mBlackKnight->getLocalBounds().height / 2);
//    mBlackKnight->setScale(CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                           CELL_H / float(pieces_tex->getSize().y / 2.0f));
//
//    mBlackPawn = new sf::Sprite();
//    mBlackPawn->setTexture(*pieces_tex);
//    mBlackPawn->setTextureRect(sf::IntRect(
//        5 * (pieces_tex->getSize().x / 6), pieces_tex->getSize().y / 2,
//        pieces_tex->getSize().x / 6, pieces_tex->getSize().y / 2));
//    mBlackPawn->setOrigin(mBlackPawn->getLocalBounds().width / 2,
//                          mBlackPawn->getLocalBounds().height / 2);
//    mBlackPawn->setScale(CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                         CELL_H / float(pieces_tex->getSize().y / 2.0f));
//
//    res->addSprite(mWhiteKing);
//    res->addSprite(mWhiteQueen);
//    res->addSprite(mWhiteRook);
//    res->addSprite(mWhiteBishop);
//    res->addSprite(mWhiteKnight);
//    res->addSprite(mWhitePawn);
//
//    res->addSprite(mBlackKing);
//    res->addSprite(mBlackQueen);
//    res->addSprite(mBlackRook);
//    res->addSprite(mBlackBishop);
//    res->addSprite(mBlackKnight);
//    res->addSprite(mBlackPawn);
//}
// void BoardRenderer::Render(Board* board, sf::RenderWindow* win) {
//    win->draw(*mBoard);
//    Board given_board = *board;
//
//    for (int i = 0; i < board->size(); i++) {
//        auto rank = board->get()[i];
//        for (int j = 0; j < rank.size(); j++) {
//            auto file = rank[j];
//
//            if (file == nullptr) continue;
//            sf::Sprite* placing = nullptr;
//            if (file->isWhite) {
//                switch (file->type) {
//                    case PieceTypes::_King: {
//                        placing = mWhiteKing;
//                        break;
//                    }
//                    case PieceTypes::_Queen: {
//                        placing = mWhiteQueen;
//                        break;
//                    }
//                    case PieceTypes::_Rook: {
//                        placing = mWhiteRook;
//                        break;
//                    }
//                    case PieceTypes::_Bishop: {
//                        placing = mWhiteBishop;
//                        break;
//                    }
//                    case PieceTypes::_Knight: {
//                        placing = mWhiteKnight;
//                        break;
//                    }
//                    case PieceTypes::_Pawn: {
//                        placing = mWhitePawn;
//                        break;
//                    }
//                    default:
//                        break;
//                }
//            } else {
//                switch (file->type) {
//                    case PieceTypes::_King: {
//                        placing = mBlackKing;
//                        break;
//                    }
//                    case PieceTypes::_Queen: {
//                        placing = mBlackQueen;
//                        break;
//                    }
//                    case PieceTypes::_Rook: {
//                        placing = mBlackRook;
//                        break;
//                    }
//                    case PieceTypes::_Bishop: {
//                        placing = mBlackBishop;
//                        break;
//                    }
//                    case PieceTypes::_Knight: {
//                        placing = mBlackKnight;
//                        break;
//                    }
//                    case PieceTypes::_Pawn: {
//                        placing = mBlackPawn;
//                        break;
//                    }
//                    default:
//                        break;
//                }
//            }
//
//            placing->setPosition((CELL_W * (j)) + (CELL_W / 2),
//                                 (CELL_H * (i)) + (CELL_H / 2));
//            if (board->get()[i][j]->isChoosen)
//                placing->scale(SELECT_SCALE, SELECT_SCALE);
//            else
//                placing->setScale(
//                    CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                    CELL_H / float(pieces_tex->getSize().y / 2.0f));
//            win->draw(*placing);
//            if (board->get()[i][j]->isChoosen)
//                placing->setScale(
//                    CELL_W / float(pieces_tex->getSize().x / 6.0f),
//                    CELL_H / float(pieces_tex->getSize().y / 2.0f));
//        }
//    }
//
//    // Render Selected Piece Moves
//    if (maker->isChoose()) {
//        // Something is Choosen
//        auto selected_info = maker->getChoosen();
//        selectedInfo = &selected_info;
//        auto cords =
//            maker->getLegalMoves(selected_info.pce, selected_info.orig);
//        for (int i = 0; i < cords.size(); i++) {
//            auto cord = cords[i];
//            sf::CircleShape circle;
//            circle.setRadius(15);
//            circle.setFillColor(sf::Color(5, 45, 41, 150));
//            circle.setOrigin(circle.getLocalBounds().width / 2,
//                             circle.getLocalBounds().height / 2);
//            circle.setPosition((cord.file * CELL_W) + (CELL_W / 2),
//                               (cord.rank * CELL_W) + (CELL_H / 2));
//            win->draw(circle);
//        }
//    }
//}
//