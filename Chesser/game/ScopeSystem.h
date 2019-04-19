//#ifndef SCOPESYS_H
//#define SCOPESYS_H
//#pragma once
//#include "Board.h"
//#include "ResourceManager.h"
//#include "chsr_api.h"
//
// struct Scope {
//    Scope() {}
//    Scope(int _x, int _y, sf::Vector2i _ray) {
//        x = _x;
//        y = _y;
//        ray = _ray;
//    }
//    int x, y;
//    sf::Vector2i ray;
//};
//
// class ScopeSystem {
//   public:
//    void Init(Board* b) { mBoard = b; }  // Scope
//    vector<Scope> getPieceScope(Piece* pce);
//    bool isScopeIntersect(Scope scope, Loc point);
//
//   private:
//    // Scope
//    vector<Scope> getKingScope(Piece* pce);
//    vector<Scope> getQueenScope(Piece* pce);
//    vector<Scope> getRookScope(Piece* pce);
//    vector<Scope> getBishopScope(Piece* pce);
//    vector<Scope> getKnightScope(Piece* pce);
//    vector<Scope> getPawnScope(Piece* pce);
//    Board* mBoard = nullptr;
//};
//
//#endif