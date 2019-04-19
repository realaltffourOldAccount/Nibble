//#include "MoveMaker.h"
//
//void MoveMaker::Init() { mMoves = new MoveSet(); }
//
//void MoveMaker::SetBoard(Board* board) { mBoard = board; }
//void MoveMaker::SetWindow(sf::RenderWindow* _win) { win = _win; }
//void MoveMaker::SetResManager(ResourceManager* _res) { res = _res; }
//
//void MoveMaker::Update(sf::Event evt) {
//    if (mWhiteMove != nullptr && mBlackMove != nullptr) {
//        mMoves->push_back(new Move(*mWhiteMove, *mBlackMove));
//        cout << mWhiteMove->to_str() << " " << mBlackMove->to_str() << endl;
//        mWhiteMove = nullptr;
//        mBlackMove = nullptr;
//        isWhiteTurn = true;
//    }
//    if (evt.type == sf::Event::MouseButtonPressed) {
//        if (isChoosen) {
//            // Place piece
//            int rank, file;
//            file = sf::Mouse::getPosition(*win).x / CELL_W;
//            rank = sf::Mouse::getPosition(*win).y / CELL_H;
//
//            if (1 < file < 8 && 1 < rank < 8) {
//                choosen.dest = xy2loc(file, rank);
//                if (choosen.orig == choosen.dest) {
//                    // UnPick
//                    isChoosen = false;
//                    choosen.pce = nullptr;
//                    choosen.sprite = nullptr;
//                    mBoard->GetBoard()[0][rank][file]->isChoosen = false;
//                } else {
//                    vector<Loc> legal_moves =
//                        getLegalMoves(choosen.pce, choosen.orig);
//                    for (int i = 0; i < legal_moves.size(); i++) {
//                        if ((legal_moves[i] == choosen.dest)) {
//                            // Place Piece
//                            // Check First
//                            if (HandleMove(choosen)) {
//                                isChoosen = false;
//                                choosen.pce = nullptr;
//                                choosen.sprite = nullptr;
//                                mBoard->GetBoard()[0][rank][file]->isChoosen =
//                                    false;
//                                // Check for Checks, mates
//                                // TODO: REMOVE THIS
//                                cout << isCheck() << endl;
//                                return;
//                            } else {
//                                // UnPick
//                                isChoosen = false;
//                                choosen.pce = nullptr;
//                                choosen.sprite = nullptr;
//                                mBoard->GetBoard()[0][rank][file]->isChoosen =
//                                    false;
//                                return;
//                            }
//                        }
//                    }
//                    // Check if user is selecting other piece
//                    if (mBoard->get()[choosen.dest.rank][choosen.dest.file] &&
//                        mBoard->get()[choosen.dest.rank][choosen.dest.file]
//                                ->isWhite == isWhiteTurn) {
//                        mBoard
//                            ->GetBoard()[0][choosen.orig.rank]
//                                        [choosen.orig.file]
//                            ->isChoosen = false;
//                        goto pce_pick;
//                    }
//                    isChoosen = false;
//                    choosen.pce = nullptr;
//                    choosen.sprite = nullptr;
//                }
//            }
//
//        } else {  // Pick Piece
//        pce_pick:
//            int rank, file;
//            file = sf::Mouse::getPosition(*win).x / CELL_W;
//            rank = sf::Mouse::getPosition(*win).y / CELL_H;
//
//            if (1 < file < 8 && 1 < rank < 8) {
//                if (mBoard->get()[rank][file] == nullptr) return;
//                if (mBoard->get()[rank][file]->isWhite != isWhiteTurn) return;
//                choosen.pce = mBoard->get()[rank][file];
//                mBoard->GetBoard()[0][rank][file]->isChoosen = true;
//                if (choosen.pce == nullptr) return;
//                choosen.sprite = getPieceSprite(choosen.pce);
//                choosen.orig = xy2loc(file, rank);
//                isChoosen = true;
//            }
//        }
//    }
//}
//
//void MoveMaker::Render() {
//    // if (isChoosen) {
//    //    choosen.sprite->setPosition(sf::Mouse::getPosition(*win).x,
//    //                                sf::Mouse::getPosition(*win).y);
//    //    win->draw(*choosen.sprite);
//    //}
//}
//
//bool MoveMaker::HandleMove(ChoosenPiece info) {
//    sf::Vector2i orig = loc2xy(info.orig);
//    sf::Vector2i dest = loc2xy(info.dest);
//    Piece* pce = info.pce;
//    if (info.pce == nullptr) return false;
//    bool white = info.pce->isWhite;
//    Piece* pce_at_dest = mBoard->get()[dest.y][dest.x];
//    if (pce_at_dest == pce) return false;  // stop headaches later
//
//    if (white) {
//        if (pce->type == PieceTypes::_King)
//            return HandleKingMoveWhite(pce_at_dest, orig, dest);
//        if (pce->type == PieceTypes::_Queen)
//            return HandleQueenMove(pce_at_dest, orig, dest);
//        if (pce->type == PieceTypes::_Rook)
//            return HandleRookMove(pce_at_dest, orig, dest);
//        if (pce->type == PieceTypes::_Bishop)
//            return HandleBishopMove(pce_at_dest, orig, dest);
//        if (pce->type == PieceTypes::_Knight)
//            return HandleKnightMove(pce_at_dest, orig, dest);
//        if (pce->type == PieceTypes::_Pawn)
//            return HandlePawnMoveWhite(pce_at_dest, orig, dest);
//
//    } else {
//        if (pce->type == PieceTypes::_King)
//            return HandleKingMoveBlack(pce_at_dest, orig, dest);
//        if (pce->type == PieceTypes::_Queen)
//            return HandleQueenMove(pce_at_dest, orig, dest);
//        if (pce->type == PieceTypes::_Rook)
//            return HandleRookMove(pce_at_dest, orig, dest);
//        if (pce->type == PieceTypes::_Bishop)
//            return HandleBishopMove(pce_at_dest, orig, dest);
//        if (pce->type == PieceTypes::_Knight)
//            return HandleKnightMove(pce_at_dest, orig, dest);
//        if (pce->type == PieceTypes::_Pawn)
//            return HandlePawnMoveBlack(pce_at_dest, orig, dest);
//    }
//    return false;
//}
//
//bool MoveMaker::HandleKingMoveWhite(Piece* pce_at_dest, sf::Vector2i orig,
//                                    sf::Vector2i dest) {
//    // Check if move destance is more than one
//    if (choosen.orig.dist(choosen.dest) != 1) return false;
//
//    // check if dest is near black's king
//    Loc blackking = getLocOfBlackKing(mBoard);
//    if (blackking.dist(choosen.dest) == 0) return false;
//    // Check if destination is null
//    if (mBoard->get()[dest.y][dest.x] != nullptr)
//        // Check if capture with white pieces
//        if (mBoard->get()[dest.y][dest.x]->isWhite) return false;
//
//    // Place Piece
//    mBoard->GetBoard()[0][dest.y][dest.x] = new King(true);
//    mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//
//    // Make Notation
//    Cords* cords = (pce_at_dest == nullptr) ?
//                                            // no capt
//                       new Cords(true, 0, vec2Loc(dest), vec2Loc(orig), false,
//                                 Loc(), false, false, false, false)
//                                            :
//                                            // capt
//                       new Cords(true, 0, vec2Loc(dest), vec2Loc(orig), true,
//                                 vec2Loc(dest), false, false, false, false);
//    (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//    isWhiteTurn = !isWhiteTurn;
//    return false;
//}
//bool MoveMaker::HandleQueenMove(
//    Piece* pce_at_dest, sf::Vector2i orig,
//    sf::Vector2i dest) {  // Check if destination is null
//    if (mBoard->get()[dest.y][dest.x] != nullptr)
//        // Check if capture with white pieces
//        if (mBoard->get()[dest.y][dest.x]->isWhite == choosen.pce->isWhite)
//            return false;
//
//    // Check if other pieces are there
//    vector<Piece*> path;
//    if (orig.x == dest.x) {
//        // changing is on y axis
//        int higher_y = (orig.y > dest.y) ? orig.y : dest.y;
//        int lower_y = (orig.y > dest.y) ? dest.y : orig.y;
//        for (int i = lower_y; i < higher_y; i++)
//            path.push_back(mBoard->get()[i][orig.x]);
//    }
//    if (orig.y == dest.y) {
//        // changing is on x axis
//        int higher_x = (orig.x > dest.x) ? orig.x : dest.x;
//        int lower_x = (orig.x > dest.x) ? dest.x : orig.x;
//        for (int i = lower_x; i < higher_x; i++)
//            path.push_back(mBoard->get()[orig.y][i]);
//    }
//    if (abs(dest.x - orig.x) == abs(dest.y - orig.y)) {
//        // changing on both axis
//        int higher_x = (orig.x > dest.x) ? orig.x : dest.x;
//        int lower_x = (orig.x > dest.x) ? dest.x : orig.x;
//        int higher_y = (orig.y > dest.y) ? orig.y : dest.y;
//        int lower_y = (orig.y > dest.y) ? dest.y : orig.y;
//
//        for (int y = higher_y, x = higher_x; x < lower_x; x--, y--)
//            path.push_back(mBoard->get()[y][x]);
//    }
//    for (int i = 1; i < path.size(); i++)
//        if (pce_at_dest != path[i])
//            if (path[i] != nullptr) return false;
//
//    // Check if move is correct
//    if (orig.x == dest.x) {  // Place Piece
//        mBoard->GetBoard()[0][dest.y][dest.x] = new Queen(choosen.pce->isWhite);
//        mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//    }
//    if (orig.y == dest.y) {  // Place Piece
//        mBoard->GetBoard()[0][dest.y][dest.x] = new Queen(choosen.pce->isWhite);
//        mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//    }
//    if (abs(dest.x - orig.x) == abs(dest.y - orig.y)) {  // Place Piece
//        mBoard->GetBoard()[0][dest.y][dest.x] = new Queen(choosen.pce->isWhite);
//        mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//    }
//    // Make Notation
//    Cords* cords =
//        (pce_at_dest == nullptr)
//            ? new Cords(choosen.pce->isWhite, PieceTypes::_Queen,
//                        xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y), false,
//                        Loc(), false, false, false, false)
//            : new Cords(choosen.pce->isWhite, PieceTypes::_Queen,
//                        xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y), true,
//                        xy2loc(dest.x, dest.y), false, false, false, false);
//    (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//    isWhiteTurn = !isWhiteTurn;
//    return true;
//}
//bool MoveMaker::HandleRookMove(Piece* pce_at_dest, sf::Vector2i orig,
//                               sf::Vector2i dest) {
//    // Check if destination is null
//    if (mBoard->get()[dest.y][dest.x] != nullptr)
//        // Check if capture with same team pieces
//        if (mBoard->get()[dest.y][dest.x]->isWhite == choosen.pce->isWhite)
//            return false;
//
//    // Check if other pieces are there
//    vector<Piece*> path;
//    if (orig.x == dest.x) {
//        // changing is on y axis
//        int higher_y = (orig.y > dest.y) ? orig.y : dest.y;
//        int lower_y = (orig.y > dest.y) ? dest.y : orig.y;
//        for (int i = lower_y; i < higher_y; i++)
//            path.push_back(mBoard->get()[i][orig.x]);
//    }
//    if (orig.y == orig.y) {
//        // changing is on x axis
//        int higher_x = (orig.x > dest.x) ? orig.x : dest.x;
//        int lower_x = (orig.x > dest.x) ? dest.x : orig.x;
//        for (int i = lower_x; i < higher_x; i++)
//            path.push_back(mBoard->get()[orig.y][i]);
//    }
//    for (int i = 0; i < path.size(); i++)
//        if (i != 0)
//            if (path[i] != nullptr) return false;
//    // Check if move is correct
//    if (orig.x == dest.x) {
//        // Place Piece
//        mBoard->GetBoard()[0][dest.y][dest.x] = new Rook(choosen.pce->isWhite);
//        mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//        // Make Notation
//        Cords* cords =
//            (pce_at_dest == nullptr)
//                ? new Cords(choosen.pce->isWhite, PieceTypes::_Rook,
//                            xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y),
//                            false, Loc(), false, false, false, false)
//                : new Cords(choosen.pce->isWhite, PieceTypes::_Rook,
//                            xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y),
//                            true, xy2loc(dest.x, dest.y), false, false, false,
//                            false);
//        (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//        isWhiteTurn = !isWhiteTurn;
//        return true;
//    }
//    if (orig.y == dest.y) {
//        // Place Piece
//        mBoard->GetBoard()[0][dest.y][dest.x] = new Rook(choosen.pce->isWhite);
//        mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//        // Make Notation
//        Cords* cords =
//            (pce_at_dest == nullptr)
//                ? new Cords(choosen.pce->isWhite, PieceTypes::_Rook,
//                            xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y),
//                            false, Loc(), false, false, false, false)
//                : new Cords(choosen.pce->isWhite, PieceTypes::_Rook,
//                            xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y),
//                            true, xy2loc(dest.x, dest.y), false, false, false,
//                            false);
//        (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//        isWhiteTurn = !isWhiteTurn;
//        return true;
//    }
//    if (abs(dest.x - orig.x) == abs(dest.y - orig.y)) return false;
//    // Place Piece
//    mBoard->GetBoard()[0][dest.y][dest.x] = new Rook(choosen.pce->isWhite);
//    mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//    // Make Notation
//    Cords* cords =
//        (pce_at_dest == nullptr)
//            ? new Cords(choosen.pce->isWhite, PieceTypes::_Rook,
//                        xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y), false,
//                        Loc(), false, false, false, false)
//            : new Cords(choosen.pce->isWhite, PieceTypes::_Rook,
//                        xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y), true,
//                        xy2loc(dest.x, dest.y), false, false, false, false);
//    (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//    isWhiteTurn = !isWhiteTurn;
//    return true;
//}
//bool MoveMaker::HandleBishopMove(
//    Piece* pce_at_dest, sf::Vector2i orig,
//    sf::Vector2i dest) {  // Check if destination is null
//    if (mBoard->get()[dest.y][dest.x] != nullptr)
//        // Check if capture with white pieces
//        if (mBoard->get()[dest.y][dest.x]->isWhite == choosen.pce->isWhite)
//            return false;
//
//    // Check if other pieces are there
//    vector<Piece*> path;
//    if (abs(dest.x - orig.x) == abs(dest.y - orig.y)) {
//        // changing on both axis
//        int higher_x = (orig.x > dest.x) ? orig.x : dest.x;
//        int lower_x = (orig.x > dest.x) ? dest.x : orig.x;
//        int higher_y = (orig.y > dest.y) ? orig.y : dest.y;
//        int lower_y = (orig.y > dest.y) ? dest.y : orig.y;
//        for (int y = higher_y, x = higher_x; x < lower_x; x--, y--)
//            path.push_back(mBoard->get()[y][x]);
//
//        for (int i = 1; i < path.size(); i++)
//            if (pce_at_dest != path[i])
//                if (path[i] != nullptr) return false;
//        // Check if move is correct
//        if (orig.x == dest.x) return false;
//        if (orig.y == dest.y) return false;
//        if (abs(dest.x - orig.x) != abs(dest.y - orig.y)) return false;
//
//        // Place Piece
//        mBoard->GetBoard()[0][dest.y][dest.x] =
//            new Bishop(choosen.pce->isWhite);
//        mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//        // Make Notation
//        Cords* cords =
//            (pce_at_dest == nullptr)
//                ? new Cords(choosen.pce->isWhite, PieceTypes::_Bishop,
//                            xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y),
//                            false, Loc(), false, false, false, false)
//                : new Cords(choosen.pce->isWhite, PieceTypes::_Bishop,
//                            xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y),
//                            true, xy2loc(dest.x, dest.y), false, false, false,
//                            false);
//        (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//        isWhiteTurn = !isWhiteTurn;
//        return true;
//    }
//    return false;
//}
//bool MoveMaker::HandleKnightMove(
//    Piece* pce_at_dest, sf::Vector2i orig,
//    sf::Vector2i dest) {  // Check if destination is null
//    if (mBoard->get()[dest.y][dest.x] != nullptr)
//        // Check if capture with white pieces
//        if (mBoard->get()[dest.y][dest.x]->isWhite) return false;
//
//    // Check if path is correct
//    int x_diff = abs(orig.x - dest.x);
//    int y_diff = abs(orig.y - dest.y);
//
//    if (x_diff == 2 && y_diff == 1) {
//        // Place Piece
//        mBoard->GetBoard()[0][dest.y][dest.x] =
//            new Knight(choosen.pce->isWhite);
//        mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//        // Make Notation
//        Cords* cords =
//            (pce_at_dest == nullptr)
//                ? new Cords(choosen.pce->isWhite, PieceTypes::_Knight,
//                            xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y),
//                            false, Loc(), false, false, false, false)
//                : new Cords(choosen.pce->isWhite, PieceTypes::_Knight,
//                            xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y),
//                            true, xy2loc(dest.x, dest.y), false, false, false,
//                            false);
//        (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//        isWhiteTurn = !isWhiteTurn;
//        return true;
//    }
//    if (x_diff == 1 && y_diff == 2) {
//        // Place Piece
//        mBoard->GetBoard()[0][dest.y][dest.x] =
//            new Knight(choosen.pce->isWhite);
//        mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//        // Make Notation
//        Cords* cords =
//            (pce_at_dest == nullptr)
//                ? new Cords(choosen.pce->isWhite, PieceTypes::_Knight,
//                            xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y),
//                            false, Loc(), false, false, false, false)
//                : new Cords(choosen.pce->isWhite, PieceTypes::_Knight,
//                            xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y),
//                            true, xy2loc(dest.x, dest.y), false, false, false,
//                            false);
//        (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//        isWhiteTurn = !isWhiteTurn;
//        return true;
//    }
//    return false;
//}
//bool MoveMaker::HandlePawnMoveWhite(
//    Piece* pce_at_dest, sf::Vector2i orig,
//    sf::Vector2i dest) {  // Check if destination is null
//    if (mBoard->get()[dest.y][dest.x] != nullptr)
//        // Check if capture with white pieces
//        if (mBoard->get()[dest.y][dest.x]->isWhite) return false;
//
//    if (orig.y <= dest.y) return false;  // cant move back
//
//    // check en passent
//    if (dest.y == 2) {
//        Piece* sidePce = mBoard->GetBoard()[0][orig.y][dest.x];
//        if (sidePce != nullptr) {
//            if (sidePce->type == 5) {
//                mBoard->GetBoard()[0][orig.y][dest.x] = nullptr;
//                // Place Piece
//                mBoard->GetBoard()[0][dest.y][dest.x] = new Pawn(true);
//                mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//                // Make Notation
//                Cords* cords =
//                    (pce_at_dest == nullptr)
//                        ? new Cords(true, PieceTypes::_Pawn,
//                                    xy2loc(dest.x, dest.y),
//                                    xy2loc(orig.x, orig.y), false, Loc(), false,
//                                    false, false, false)
//                        : new Cords(true, PieceTypes::_Pawn,
//                                    xy2loc(dest.x, dest.y),
//                                    xy2loc(orig.x, orig.y), true,
//                                    xy2loc(dest.x, dest.y), false, false, false,
//                                    false);
//                (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//                isWhiteTurn = !isWhiteTurn;
//                return true;
//            } else
//                return false;
//        }
//    }
//
//    int x_diff = abs(orig.x - dest.x);
//    int y_diff = abs(orig.y - dest.y);
//
//    if (y_diff == 1 && x_diff == 1) {
//        // check for capture
//        if (mBoard->get()[dest.y][dest.x] != nullptr) {
//            if (!mBoard->get()[dest.y][dest.x]->isChoosen) {
//                // Place Piece
//                mBoard->GetBoard()[0][dest.y][dest.x] = new Pawn(true);
//                mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//                // Make Notation
//                Cords* cords =
//                    (pce_at_dest == nullptr)
//                        ? new Cords(true, PieceTypes::_Pawn,
//                                    xy2loc(dest.x, dest.y),
//                                    xy2loc(orig.x, orig.y), false, Loc(), false,
//                                    false, false, false)
//                        : new Cords(true, PieceTypes::_Pawn,
//                                    xy2loc(dest.x, dest.y),
//                                    xy2loc(orig.x, orig.y), true,
//                                    xy2loc(dest.x, dest.y), false, false, false,
//                                    false);
//                (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//                isWhiteTurn = !isWhiteTurn;
//                return true;
//            }
//        }
//        return false;
//    }
//
//    // check if normal move
//    if (y_diff == 1) {
//        // return true only if the one step is clear
//        if (pce_at_dest != nullptr) return false;
//        // Place Piece
//        mBoard->GetBoard()[0][dest.y][dest.x] = new Pawn(true);
//        mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//        // Make Notation
//        Cords* cords =
//            (pce_at_dest == nullptr)
//                ? new Cords(true, PieceTypes::_Pawn, xy2loc(dest.x, dest.y),
//                            xy2loc(orig.x, orig.y), false, Loc(), false, false,
//                            false, false)
//                : new Cords(true, PieceTypes::_Pawn, xy2loc(dest.x, dest.y),
//                            xy2loc(orig.x, orig.y), true,
//                            xy2loc(dest.x, dest.y), false, false, false, false);
//        (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//        isWhiteTurn = !isWhiteTurn;
//        return true;
//    }
//
//    // check for begining move, double step
//    if (orig.y == 6) {
//        // return true only if the one step is clear
//        if (pce_at_dest != nullptr) return false;
//        if (y_diff == 2) {
//            // Check if there is a piece in between
//            if (mBoard->GetBoard()[0][orig.y - 1][orig.x] != nullptr)
//                return false;
//            // Place Piece
//            mBoard->GetBoard()[0][dest.y][dest.x] = new Pawn(true);
//            mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//            // Make Notation
//            Cords* cords =
//                (pce_at_dest == nullptr)
//                    ? new Cords(true, PieceTypes::_Pawn, xy2loc(dest.x, dest.y),
//                                xy2loc(orig.x, orig.y), false, Loc(), false,
//                                false, false, false)
//                    : new Cords(true, PieceTypes::_Pawn, xy2loc(dest.x, dest.y),
//                                xy2loc(orig.x, orig.y), true,
//                                xy2loc(dest.x, dest.y), false, false, false,
//                                false);
//            (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//            isWhiteTurn = !isWhiteTurn;
//            return true;
//        }
//    }
//
//    return false;
//}
//
//bool MoveMaker::HandleKingMoveBlack(Piece* pce_at_dest, sf::Vector2i orig,
//                                    sf::Vector2i dest) {
//    // Check if move destance is more than one
//    if (choosen.orig.dist(choosen.dest) != 1) return false;
//
//    // check if dest is near white's king
//    Loc whiteking = getLocOfWhiteKing(mBoard);
//    if (whiteking.dist(choosen.dest) == 0) return false;
//    // Check if destination is null
//    if (mBoard->get()[dest.y][dest.x] != nullptr)
//        // Check if capture with black pieces
//        if (!mBoard->get()[dest.y][dest.x]->isWhite) return false;
//
//    // Place Piece
//    mBoard->GetBoard()[0][dest.y][dest.x] = new King(false);
//    mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//
//    // Make Notation
//    Cords* cords = (pce_at_dest == nullptr) ?
//                                            // no capt
//                       new Cords(false, 0, vec2Loc(dest), vec2Loc(orig), false,
//                                 Loc(), false, false, false, false)
//                                            :
//                                            // capt
//                       new Cords(false, 0, vec2Loc(dest), vec2Loc(orig), true,
//                                 vec2Loc(dest), false, false, false, false);
//    (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//    isWhiteTurn = !isWhiteTurn;
//    return false;
//}
//bool MoveMaker::HandlePawnMoveBlack(
//    Piece* pce_at_dest, sf::Vector2i orig,
//    sf::Vector2i dest) {  // Check if destination is null
//    if (mBoard->get()[dest.y][dest.x] != nullptr)
//        // Check if capture with black pieces
//        if (!mBoard->get()[dest.y][dest.x]->isWhite) return false;
//
//    // check en passent
//    if (dest.y == 5) {
//        Piece* sidePce = mBoard->GetBoard()[0][orig.y][dest.x];
//        if (sidePce != nullptr) {
//            if (sidePce->type == 5) {
//                mBoard->GetBoard()[0][orig.y][dest.x] = nullptr;
//                // Place Piece
//                mBoard->GetBoard()[0][dest.y][dest.x] = new Pawn(false);
//                mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//                // Make Notation
//                Cords* cords =
//                    (pce_at_dest == nullptr)
//                        ? new Cords(false, PieceTypes::_Pawn,
//                                    xy2loc(dest.x, dest.y),
//                                    xy2loc(orig.x, orig.y), false, Loc(), false,
//                                    false, false, false)
//                        : new Cords(false, PieceTypes::_Pawn,
//                                    xy2loc(dest.x, dest.y),
//                                    xy2loc(orig.x, orig.y), true,
//                                    xy2loc(dest.x, dest.y), false, false, false,
//                                    false);
//                (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//                isWhiteTurn = !isWhiteTurn;
//                return true;
//            } else
//                return false;
//        }
//    }
//
//    if (orig.y >= dest.y) return false;  // cant move back
//
//    int x_diff = abs(orig.x - dest.x);
//    int y_diff = abs(orig.y - dest.y);
//
//    if (y_diff == 1 && x_diff == 1) {
//        // check for capture
//        if (mBoard->get()[dest.y][dest.x] != nullptr) {
//            if (!mBoard->get()[dest.y][dest.x]->isChoosen) {
//                // Place Piece
//                mBoard->GetBoard()[0][dest.y][dest.x] = new Pawn(false);
//                mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//                // Make Notation
//                Cords* cords =
//                    (pce_at_dest == nullptr)
//                        ? new Cords(false, PieceTypes::_Pawn,
//                                    xy2loc(dest.x, dest.y),
//                                    xy2loc(orig.x, orig.y), false, Loc(), false,
//                                    false, false, false)
//                        : new Cords(false, PieceTypes::_Pawn,
//                                    xy2loc(dest.x, dest.y),
//                                    xy2loc(orig.x, orig.y), true,
//                                    xy2loc(dest.x, dest.y), false, false, false,
//                                    false);
//                (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//                isWhiteTurn = !isWhiteTurn;
//                return true;
//            }
//        }
//        return false;
//    }
//
//    // check if normal move
//    if (y_diff == 1) {
//        // return true only if the one step is clear
//        if (pce_at_dest != nullptr) return false;
//        // Place Piece
//        mBoard->GetBoard()[0][dest.y][dest.x] = new Pawn(false);
//        mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//        // Make Notation
//        Cords* cords =
//            (pce_at_dest == nullptr)
//                ? new Cords(false, PieceTypes::_Pawn, xy2loc(dest.x, dest.y),
//                            xy2loc(orig.x, orig.y), false, Loc(), false, false,
//                            false, false)
//                : new Cords(false, PieceTypes::_Pawn, xy2loc(dest.x, dest.y),
//                            xy2loc(orig.x, orig.y), true,
//                            xy2loc(dest.x, dest.y), false, false, false, false);
//        (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//        isWhiteTurn = !isWhiteTurn;
//        return true;
//    }
//
//    // check for begining move, double step
//    if (orig.y == 1) {
//        // return true only if the one step is clear
//        if (pce_at_dest != nullptr) return false;
//        if (y_diff == 2) {
//            // Check if there is a piece in between
//            if (mBoard->GetBoard()[0][orig.y + 1][orig.x] != nullptr)
//                return false;
//            // Place Piece
//            mBoard->GetBoard()[0][dest.y][dest.x] = new Pawn(false);
//            mBoard->GetBoard()[0][orig.y][orig.x] = nullptr;
//            // Make Notation
//            Cords* cords =
//                (pce_at_dest == nullptr)
//                    ? new Cords(false, PieceTypes::_Pawn,
//                                xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y),
//                                false, Loc(), false, false, false, false)
//                    : new Cords(false, PieceTypes::_Pawn,
//                                xy2loc(dest.x, dest.y), xy2loc(orig.x, orig.y),
//                                true, xy2loc(dest.x, dest.y), false, false,
//                                false, false);
//            (isWhiteTurn) ? mWhiteMove = cords : mBlackMove = cords;
//            isWhiteTurn = !isWhiteTurn;
//            return true;
//        }
//    }
//
//    return false;
//}
//
//vector<Loc> MoveMaker::getLegalMoves(Piece* pce, Loc orig) {
//    if (pce == nullptr) return {};
//    if (pce->type == PieceTypes::_King) return getLegalKingMoves(orig);
//    if (pce->type == PieceTypes::_Queen) return getLegalQueenMoves(orig);
//    if (pce->type == PieceTypes::_Rook) return getLegalRookMoves(orig);
//    if (pce->type == PieceTypes::_Bishop) return getLegalBishopMoves(orig);
//    if (pce->type == PieceTypes::_Knight) return getLegalKnightMoves(orig);
//    if (pce->type == PieceTypes::_Pawn) return getLegalPawnMoves(orig);
//}
//
//vector<Loc> MoveMaker::getLegalKingMoves(Loc orig) {
//    //
//    //  |1|2|3|
//    //  |8|K|4|
//    //  |7|6|5|
//    //
//    vector<Loc> possible_dests;
//    if (orig.rank - 1 > 0) {
//        if (orig.file - 1 > 0)
//            possible_dests.push_back(
//                xy2loc(orig.file - 1, orig.rank - 1));  // 1
//        if (orig.file > 0)
//            possible_dests.push_back(xy2loc(orig.file, orig.rank - 1));  // 2
//        if (orig.file + 1 < 8)
//            possible_dests.push_back(
//                xy2loc(orig.file + 1, orig.rank - 1));  // 3
//    }
//    if (orig.rank > 0 && orig.rank < 8) {
//        if (orig.file - 1 > 0)
//            possible_dests.push_back(xy2loc(orig.file - 1, orig.rank));  // 8
//        if (orig.file + 1 > 0)
//            possible_dests.push_back(xy2loc(orig.file + 1, orig.rank));  // 4
//    }
//    if (orig.rank + 1 < 8) {
//        if (orig.file - 1 > 0)
//            possible_dests.push_back(
//                xy2loc(orig.file - 1, orig.rank + 1));  // 7
//        if (orig.file > 0)
//            possible_dests.push_back(xy2loc(orig.file, orig.rank + 1));  // 6
//        if (orig.file + 1 < 8)
//            possible_dests.push_back(
//                xy2loc(orig.file + 1, orig.rank + 1));  // 5
//    }
//
//    vector<Loc> res;
//    Piece* thispce = mBoard->get()[orig.rank][orig.file];
//    if (thispce == nullptr) return {};  // Something is bad
//    Loc oKing = (thispce->isWhite) ? getLocOfBlackKing(mBoard)
//                                   : getLocOfWhiteKing(mBoard);
//    for (int i = 0; i < possible_dests.size(); i++) {
//        Piece* pce =
//            mBoard->get()[possible_dests[i].rank][possible_dests[i].file];
//        if (orig.dist(oKing) == 0)
//            // kings must be one cell apart
//            continue;
//        // Check if same color captures
//        if (pce != nullptr)
//            if (pce->isWhite == thispce->isWhite)  // same color
//                continue;
//        res.push_back(possible_dests[i]);
//    }
//    return res;
//}
//vector<Loc> MoveMaker::getLegalQueenMoves(Loc orig) {
//    vector<Loc> possible_dests_horiz;
//    vector<Loc> possible_dests_vert;
//
//    for (int x = orig.file + 1; x < 8; x++) {
//        if (x > 7) break;
//        if (mBoard->get()[orig.rank][x] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[orig.rank][x]->isWhite)
//                possible_dests_horiz.push_back(xy2loc(x, orig.rank));
//            break;
//        }
//        possible_dests_horiz.push_back(xy2loc(x, orig.rank));
//    }
//    for (int x = orig.file - 1; x >= 0; x--) {
//        if (x < 0) break;
//        if (mBoard->get()[orig.rank][x] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[orig.rank][x]->isWhite)
//                possible_dests_horiz.push_back(xy2loc(x, orig.rank));
//            break;
//        }
//        possible_dests_horiz.push_back(xy2loc(x, orig.rank));
//    }
//    for (int y = orig.rank + 1; y < 8; y++) {
//        if (y > 7) break;
//        if (mBoard->get()[y][orig.file] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[y][orig.file]->isWhite)
//                possible_dests_horiz.push_back(xy2loc(orig.file, y));
//            break;
//        }
//        possible_dests_horiz.push_back(xy2loc(orig.file, y));
//    }
//    for (int y = orig.rank - 1; y >= 0; y--) {
//        if (y < 0) break;
//        if (mBoard->get()[y][orig.file] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[y][orig.file]->isWhite)
//                possible_dests_horiz.push_back(xy2loc(orig.file, y));
//            break;
//        }
//        possible_dests_horiz.push_back(xy2loc(orig.file, y));
//    }
//
//    vector<Loc> possible_dests_pos_diag;
//    vector<Loc> possible_dests_neg_diag;
//
//    for (int x = orig.file + 1, y = orig.rank + 1; x < 8, y < 8; x++, y++) {
//        if (x < 0 || x > 7 || y < 0 || y > 7) break;
//        if (mBoard->get()[y][x] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[y][x]->isWhite)
//                possible_dests_neg_diag.push_back(xy2loc(x, y));
//            break;
//        }
//        possible_dests_neg_diag.push_back(xy2loc(x, y));
//    }
//    for (int x = orig.file - 1, y = orig.rank + 1; x != 0, y < 8; x--, y++) {
//        if (x < 0 || x > 7 || y < 0 || y > 7) break;
//        if (mBoard->get()[y][x] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[y][x]->isWhite)
//                possible_dests_neg_diag.push_back(xy2loc(x, y));
//            break;
//        }
//        possible_dests_neg_diag.push_back(xy2loc(x, y));
//    }
//
//    for (int x = orig.file + 1, y = orig.rank - 1; x < 8, y >= 0; x++, y--) {
//        if (x < 0 || x > 7 || y < 0 || y > 7) break;
//        if (mBoard->get()[y][x] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[y][x]->isWhite)
//                possible_dests_neg_diag.push_back(xy2loc(x, y));
//            break;
//        }
//        possible_dests_neg_diag.push_back(xy2loc(x, y));
//    }
//    for (int x = orig.file - 1, y = orig.rank - 1; x >= 0, y >= 0; x--, y--) {
//        if (x < 0 || x > 7 || y < 0 || y > 7) break;
//        if (mBoard->get()[y][x] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[y][x]->isWhite)
//                possible_dests_neg_diag.push_back(xy2loc(x, y));
//            break;
//        }
//        possible_dests_neg_diag.push_back(xy2loc(x, y));
//    }
//
//    vector<Loc> res;
//    for (int i = 0; i < possible_dests_horiz.size(); i++)
//        res.push_back(possible_dests_horiz[i]);
//    for (int i = 0; i < possible_dests_vert.size(); i++)
//        res.push_back(possible_dests_vert[i]);
//    for (int i = 0; i < possible_dests_pos_diag.size(); i++)
//        res.push_back(possible_dests_pos_diag[i]);
//    for (int i = 0; i < possible_dests_neg_diag.size(); i++)
//        res.push_back(possible_dests_neg_diag[i]);
//
//    return res;
//}
//vector<Loc> MoveMaker::getLegalRookMoves(Loc orig) {
//    vector<Loc> possible_dests_horiz;
//    vector<Loc> possible_dests_vert;
//
//    for (int x = orig.file + 1; x < 8; x++) {
//        if (mBoard->get()[orig.rank][x] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[orig.rank][x]->isWhite)
//                possible_dests_horiz.push_back(xy2loc(x, orig.rank));
//            break;
//        }
//        possible_dests_horiz.push_back(xy2loc(x, orig.rank));
//    }
//    for (int x = orig.file - 1; x >= 0; x--) {
//        if (mBoard->get()[orig.rank][x] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[orig.rank][x]->isWhite)
//                isWhiteTurn == false;
//            possible_dests_horiz.push_back(xy2loc(x, orig.rank));
//            break;
//        }
//        possible_dests_horiz.push_back(xy2loc(x, orig.rank));
//    }
//    for (int y = orig.rank + 1; y < 8; y++) {
//        if (mBoard->get()[y][orig.file] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[y][orig.file]->isWhite)
//                possible_dests_horiz.push_back(xy2loc(orig.file, y));
//            break;
//        }
//        possible_dests_horiz.push_back(xy2loc(orig.file, y));
//    }
//    for (int y = orig.rank - 1; y >= 0; y--) {
//        if (mBoard->get()[y][orig.file] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[y][orig.file]->isWhite)
//                possible_dests_horiz.push_back(xy2loc(orig.file, y));
//            break;
//        }
//        possible_dests_horiz.push_back(xy2loc(orig.file, y));
//    }
//    vector<Loc> res;
//    for (int i = 0; i < possible_dests_horiz.size(); i++)
//        res.push_back(possible_dests_horiz[i]);
//    for (int i = 0; i < possible_dests_vert.size(); i++)
//        res.push_back(possible_dests_vert[i]);
//    return res;
//}
//vector<Loc> MoveMaker::getLegalBishopMoves(Loc orig) {
//    vector<Loc> possible_dests_pos_diag;
//    vector<Loc> possible_dests_neg_diag;
//
//    for (int x = orig.file + 1, y = orig.rank + 1; x < 8, y < 8; x++, y++) {
//        if (x < 0 || y < 0 || x > 7 || y > 7) break;
//        if (mBoard->get()[y][x] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[y][x]->isWhite)
//                possible_dests_neg_diag.push_back(xy2loc(x, y));
//            break;
//        }
//        possible_dests_neg_diag.push_back(xy2loc(x, y));
//    }
//    for (int x = orig.file - 1, y = orig.rank + 1; x >= 0, y < 8; x--, y++) {
//        if (x < 0 || y < 0 || x > 7 || y > 7) break;
//        if (mBoard->get()[y][x] != nullptr) {
//            auto pce = mBoard->get()[orig.rank][orig.file];
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[y][x]->isWhite)
//                possible_dests_neg_diag.push_back(xy2loc(x, y));
//            break;
//        }
//        possible_dests_neg_diag.push_back(xy2loc(x, y));
//    }
//
//    for (int x = orig.file + 1, y = orig.rank - 1; x < 8, y >= 0; x++, y--) {
//        if (x < 0 || y < 0 || x > 7 || y > 7) break;
//        if (mBoard->get()[y][x] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[y][x]->isWhite)
//                possible_dests_neg_diag.push_back(xy2loc(x, y));
//            break;
//        }
//        possible_dests_neg_diag.push_back(xy2loc(x, y));
//    }
//    for (int x = orig.file - 1, y = orig.rank - 1; x >= 0, y >= 0; x--, y--) {
//        if (x < 0 || y < 0 || x > 7 || y > 7) break;
//        if (mBoard->get()[y][x] != nullptr) {
//            if (mBoard->get()[orig.rank][orig.file]->isWhite !=
//                mBoard->get()[y][x]->isWhite)
//                possible_dests_neg_diag.push_back(xy2loc(x, y));
//            break;
//        }
//        possible_dests_neg_diag.push_back(xy2loc(x, y));
//    }
//
//    vector<Loc> res;
//    for (int i = 0; i < possible_dests_pos_diag.size(); i++)
//        res.push_back(possible_dests_pos_diag[i]);
//    for (int i = 0; i < possible_dests_neg_diag.size(); i++)
//        res.push_back(possible_dests_neg_diag[i]);
//
//    return res;
//}
//vector<Loc> MoveMaker::getLegalKnightMoves(Loc orig) {
//    vector<Loc> cords;
//    if (orig.rank - 2 >= 0) {
//        if (orig.file - 1 >= 0)
//            cords.push_back(xy2loc(orig.file - 1, orig.rank - 2));
//        if (orig.file + 1 < 8)
//            cords.push_back(xy2loc(orig.file + 1, orig.rank - 2));
//    }
//    if (orig.rank + 2 < 8) {
//        if (orig.file - 1 >= 0)
//            cords.push_back(xy2loc(orig.file - 1, orig.rank + 2));
//        if (orig.file + 1 < 8)
//            cords.push_back(xy2loc(orig.file + 1, orig.rank + 2));
//    }
//    if (orig.file - 2 >= 0) {
//        if (orig.rank - 1 >= 0)
//            cords.push_back(xy2loc(orig.file - 2, orig.rank - 1));
//        if (orig.rank + 1 < 8)
//            cords.push_back(xy2loc(orig.file - 2, orig.rank + 1));
//    }
//    if (orig.file + 2 < 8) {
//        if (orig.rank - 1 >= 0)
//            cords.push_back(xy2loc(orig.file + 2, orig.rank - 1));
//        if (orig.rank + 1 < 8)
//            cords.push_back(xy2loc(orig.file + 2, orig.rank + 1));
//    }
//
//    vector<Loc> res;
//    for (int i = 0; i < cords.size(); i++) {
//        if (mBoard->get()[cords[i].rank][cords[i].file] != nullptr) {
//            if (mBoard->get()[cords[i].rank][cords[i].file]->isWhite ==
//                mBoard->get()[orig.rank][orig.file]->isWhite)
//                continue;
//        }
//        res.push_back(cords[i]);
//    }
//    return res;
//}
//vector<Loc> MoveMaker::getLegalPawnMoves(Loc orig) {
//    vector<Loc> res;
//    Piece* pce = mBoard->get()[orig.rank][orig.file];
//    if (pce == nullptr) return res;
//    if (pce->isWhite) {
//        // Check En passent
//        if (orig.rank == 3) {
//            Piece* lsidePce = mBoard->get()[orig.rank][orig.file - 1];
//            Piece* rsidePce = mBoard->get()[orig.rank][orig.file + 1];
//
//            if (lsidePce != nullptr) {
//                if (!lsidePce->isWhite) {
//                    if (lsidePce->type == PieceTypes::_Pawn) {
//                        // TODO: Check for discovered checks
//                        res.push_back(xy2loc(orig.file - 1, orig.rank - 1));
//                    }
//                }
//            }
//            if (rsidePce != nullptr) {
//                if (!rsidePce->isWhite) {
//                    if (rsidePce->type == PieceTypes::_Pawn) {
//                        // TODO: Check for discovered checks
//                        res.push_back(xy2loc(orig.file + 1, orig.rank - 1));
//                    }
//                }
//            }
//        }
//        // Check Cpatures
//        if (!(orig.rank - 1 < 0 || orig.file - 1 < 0 || orig.rank + 1 > 7 ||
//              orig.file + 1 > 7)) {
//            Piece* pce_left = mBoard->get()[orig.rank - 1][orig.file - 1];
//            Piece* pce_right = mBoard->get()[orig.rank - 1][orig.file + 1];
//
//            if (pce_left != nullptr) {
//                if (pce_left->isWhite !=
//                    mBoard->get()[orig.rank][orig.file]->isWhite)
//                    res.push_back(xy2loc(orig.file - 1, orig.rank - 1));
//            }
//            if (pce_right != nullptr) {
//                if (pce_right->isWhite !=
//                    mBoard->get()[orig.rank][orig.file]->isWhite)
//                    res.push_back(xy2loc(orig.file + 1, orig.rank - 1));
//            }
//        }
//        if (orig.rank == 6) {
//            if (mBoard->get()[orig.rank - 1][orig.file] == nullptr)
//                res.push_back(xy2loc(orig.file, orig.rank - 1));
//            res.push_back(xy2loc(orig.file, orig.rank - 2));
//        } else {
//            if (mBoard->get()[orig.rank - 1][orig.file] == nullptr)
//                res.push_back(xy2loc(orig.file, orig.rank - 1));
//        }
//
//    } else {
//        // Check En passent
//        if (orig.rank == 4) {
//            Piece* lsidePce = mBoard->get()[orig.rank][orig.file - 1];
//            Piece* rsidePce = mBoard->get()[orig.rank][orig.file + 1];
//
//            if (lsidePce != nullptr) {
//                if (lsidePce->isWhite) {
//                    if (lsidePce->type == PieceTypes::_Pawn) {
//                        // TODO: Check for discovered checks
//                        res.push_back(xy2loc(orig.file - 1, orig.rank + 1));
//                    }
//                }
//            }
//            if (rsidePce != nullptr) {
//                if (rsidePce->isWhite) {
//                    if (rsidePce->type == PieceTypes::_Pawn) {
//                        // TODO: Check for discovered checks
//                        res.push_back(xy2loc(orig.file + 1, orig.rank + 1));
//                    }
//                }
//            }
//        }
//        // Check for captures
//        if (!(orig.rank - 1 < 0 || orig.file - 1 < 0 || orig.rank + 1 > 7 ||
//              orig.file + 1 > 7)) {
//            Piece* pce_left = mBoard->get()[orig.rank + 1][orig.file - 1];
//            Piece* pce_right = mBoard->get()[orig.rank + 1][orig.file + 1];
//
//            if (pce_left != nullptr) {
//                if (pce_left->isWhite !=
//                    mBoard->get()[orig.rank][orig.file]->isWhite)
//                    res.push_back(xy2loc(orig.file - 1, orig.rank + 1));
//            }
//            if (pce_right != nullptr) {
//                if (pce_right->isWhite !=
//                    mBoard->get()[orig.rank][orig.file]->isWhite)
//                    res.push_back(xy2loc(orig.file + 1, orig.rank + 1));
//            }
//        }
//        if (orig.rank == 1) {
//            if (mBoard->get()[orig.rank + 1][orig.file] == nullptr)
//                res.push_back(xy2loc(orig.file, orig.rank + 1));
//            res.push_back(xy2loc(orig.file, orig.rank + 2));
//        } else {
//            if (mBoard->get()[orig.rank + 1][orig.file] == nullptr)
//                res.push_back(xy2loc(orig.file, orig.rank + 1));
//        }
//    }
//    return res;
//}
//
//int MoveMaker::isCheck() {
//    int res1 = isWhiteChecking();
//    int res2 = isBlackChecking();
//    if (res1 == WHITE_CHECKS_BLACK)
//        return res1;
//    else if (res1 == WHITE_CHECKMATES_BLACK)
//        return res1;
//    else if (res2 == BLACK_CHECKS_WHITE)
//        return res2;
//    else if (res2 == BLACK_CHECKMATES_WHITE)
//        return res2;
//    else
//        return NO_CHECKS;
//}
//
//int MoveMaker::isWhiteChecking() {
//    // Get White pieces
//    auto pces = getWhitePieces();
//    vector<vector<Loc> > moves;
//    for (auto* pce : pces) moves.push_back(getLegalMoves(pce->pce, pce->loc));
//
//    // Search for the king being in one of the moves
//    for (int i = 0; i < moves.size(); i++) {
//        for (int j = 0; j < moves[i].size(); j++) {
//            Piece* pce = mBoard->get()[moves[i][j].rank][moves[i][j].file];
//            if (pce == nullptr) continue;
//            if (pce->isWhite) continue;
//            if (pce->type == PieceTypes::_King) {
//                // Found 'em
//
//                // Check for checkmate
//                PieceInfo bKing;
//                bKing.loc = getLocOfBlackKing(mBoard);
//                bKing.pce = pce;
//
//                std::vector<Loc> bKingMoves = getLegalKingMoves(bKing.loc);
//
//                if (bKingMoves.size() == 0)
//                    // CheckMate
//                    return WHITE_CHECKMATES_BLACK;
//                else
//                    return WHITE_CHECKS_BLACK;
//            }
//        }
//    }
//    return NO_CHECKS;
//}
//int MoveMaker::isBlackChecking() {
//    // Get Black Pieces
//    auto pces = getBlackPieces();
//    vector<vector<Loc> > moves;
//    for (auto* pce : pces) moves.push_back(getLegalMoves(pce->pce, pce->loc));
//
//    // Search for the king being in one of the moves
//    for (int i = 0; i < moves.size(); i++) {
//        for (int j = 0; j < moves[i].size(); j++) {
//            Piece* pce = mBoard->get()[moves[i][j].rank][moves[i][j].file];
//            if (pce == nullptr) continue;
//            if (!pce->isWhite) continue;
//            if (pce->type == PieceTypes::_King) {
//                // Found 'em
//
//                // Check For Checkmate
//                PieceInfo wKing;
//                wKing.loc = getLocOfWhiteKing(mBoard);
//                wKing.pce = pce;
//
//                auto wKingMoves = getLegalKingMoves(wKing.loc);
//                if (wKingMoves.size() == 0)
//                    // CheckMate
//                    return BLACK_CHECKMATES_WHITE;
//                else
//                    return BLACK_CHECKS_WHITE;
//            }
//        }
//    }
//    return NO_CHECKS;
//}
//
//vector<PieceInfo*> MoveMaker::getWhitePieces() {
//    vector<PieceInfo*> res;
//    for (int i = 0; i < mBoard->get().size(); i++) {
//        for (int j = 0; j < mBoard->get()[i].size(); j++) {
//            Piece* pce = mBoard->get()[i][j];
//            if (pce != nullptr)
//                if (pce->isWhite)
//                    res.push_back(new PieceInfo(pce, xy2loc(j, i)));
//        }
//    }
//    return res;
//}
//vector<PieceInfo*> MoveMaker::getBlackPieces() {
//    vector<PieceInfo*> res;
//    for (int i = 0; i < mBoard->get().size(); i++) {
//        for (int j = 0; j < mBoard->get()[i].size(); j++) {
//            Piece* pce = mBoard->get()[i][j];
//            if (pce != nullptr)
//                if (!pce->isWhite)
//                    res.push_back(new PieceInfo(pce, xy2loc(j, i)));
//        }
//    }
//    return res;
//}
//