#ifndef MOVEMAKER_H
#define MOVEMAKER_H
#pragma once
//#include "BoardRenderer.h"
#include "Board.h"
#include "ResourceManager.h"
#include "chsr_api.h"

// struct ChoosenPiece {
//    Piece* pce;
//    sf::Sprite* sprite;
//    Loc orig;
//    Loc dest;
//};
//
// struct PieceInfo {
//    PieceInfo() {}
//    PieceInfo(Piece* _pce, Loc _loc) {
//        pce = _pce;
//        loc = _loc;
//    }
//    Piece* pce;
//    Loc loc;
//};
//
class MoveMaker {
//   public:
//    void Init();
//    void SetBoard(Board* board);
//    void SetWindow(sf::RenderWindow* _win);
//    void SetResManager(ResourceManager* res);
//    void StartAsWhite(bool istrue = true) { isWhiteTurn = istrue; }
//
//    void Update(sf::Event evt);
//    void Render();
//
//    bool isChoose() { return isChoosen; }
//    auto getChoosen() { return choosen; }
//
//    vector<PieceInfo*> getWhitePieces();
//    vector<PieceInfo*> getBlackPieces();
//
//    vector<Loc> getLegalMoves(Piece* pce, Loc orig);
//
//    /*
//        Returns one of the defines:
//            WHITE_CHECKS_BLACK
//            BLACK_CHECKS_WHITE
//            WHITE_CHECKMATES_BLACK
//            BLACK_CHECKMATES_WHITE
//    */
//    int isCheck();
//
//   private:
//    // Returns one of the defines:
//    // WHITE_CHECKS_BLACK
//    // WHITE_CHECKMATES_BLACK
//    // NO_CHECKS
//    int isWhiteChecking();
//    // Returns one of the defines:
//    // BLACK_CHECKS_WHITE
//    // BLACK_CHECKMATES_WHITE
//    // NO_CHECKS
//    int isBlackChecking();
//
//    vector<Loc> getLegalKingMoves(Loc orig);
//    vector<Loc> getLegalQueenMoves(Loc orig);
//    vector<Loc> getLegalRookMoves(Loc orig);
//    vector<Loc> getLegalBishopMoves(Loc orig);
//    vector<Loc> getLegalKnightMoves(Loc orig);
//    vector<Loc> getLegalPawnMoves(Loc orig);
//
//    Board* mBoard;
//    ResourceManager* res = nullptr;
//    sf::RenderWindow* win;
//
//    bool isChoosen = false;
//    bool isWhiteTurn = true;
//    MoveSet* mMoves = nullptr;
//    Cords* mWhiteMove = nullptr;
//    Cords* mBlackMove = nullptr;
//    ChoosenPiece choosen;
//
//    bool HandleMove(ChoosenPiece info);
//    bool UnHandleMove(ChoosenPiece info);
//
//    sf::Sprite* getPieceSprite(Piece* pce) {
//        if (pce == nullptr) return nullptr;
//        if (pce->isWhite) {
//            switch (pce->type) {
//                case PieceTypes::_King:
//                    return (*res)[0];
//                    break;
//                case PieceTypes::_Queen:
//                    return (*res)[1];
//                    break;
//                case PieceTypes::_Rook:
//                    return (*res)[2];
//                    break;
//                case PieceTypes::_Bishop:
//                    return (*res)[3];
//                    break;
//                case PieceTypes::_Knight:
//                    return (*res)[4];
//                    break;
//                case PieceTypes::_Pawn:
//                    return (*res)[5];
//                    break;
//                default:
//                    break;
//            }
//        } else {
//            switch (pce->type) {
//                case PieceTypes::_King:
//                    return (*res)[6];
//                    break;
//                case PieceTypes::_Queen:
//                    return (*res)[7];
//                    break;
//                case PieceTypes::_Rook:
//                    return (*res)[8];
//                    break;
//                case PieceTypes::_Bishop:
//                    return (*res)[9];
//                    break;
//                case PieceTypes::_Knight:
//                    return (*res)[10];
//                    break;
//                case PieceTypes::_Pawn:
//                    return (*res)[11];
//                    break;
//                default:
//                    break;
//            }
//        }
//    }
//
//    bool HandleKingMoveWhite(Piece* pce_dest, sf::Vector2i orig,
//                             sf::Vector2i dest);
//    bool HandleKingMoveBlack(Piece* pce_dest, sf::Vector2i orig,
//                             sf::Vector2i dest);
//    bool HandleQueenMove(Piece* pce_dest, sf::Vector2i orig, sf::Vector2i
//    dest); bool HandleRookMove(Piece* pce_dest, sf::Vector2i orig,
//    sf::Vector2i dest); bool HandleBishopMove(Piece* pce_dest, sf::Vector2i
//    orig,
//                          sf::Vector2i dest);
//    bool HandleKnightMove(Piece* pce_dest, sf::Vector2i orig,
//                          sf::Vector2i dest);
//    bool HandlePawnMoveWhite(Piece* pce_dest, sf::Vector2i orig,
//                             sf::Vector2i dest);
//    bool HandlePawnMoveBlack(Piece* pce_dest, sf::Vector2i orig,
//                             sf::Vector2i dest);
};

#endif