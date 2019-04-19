//#include "ScopeSystem.h"
//
// vector<Scope> ScopeSystem::getPieceScope(Piece* pce) {
//    if (pce == nullptr) return {};
//
//    if (pce->type == PieceTypes::_King)
//        return getKingScope(pce);
//    else if (pce->type == PieceTypes::_Queen)
//        return getQueenScope(pce);
//    else if (pce->type == PieceTypes::_Rook)
//        return getRookScope(pce);
//    else if (pce->type == PieceTypes::_Bishop)
//        return getBishopScope(pce);
//    else if (pce->type == PieceTypes::_Knight)
//        return getKnightScope(pce);
//    else if (pce->type == PieceTypes::_Pawn)
//        return getPawnScope(pce);
//}
//
// vector<Scope> ScopeSystem::getKingScope(Piece* pce) {
//    vector<Scope> res;
//    //
//    //  |1|2|3|
//    //  |8|K|4|
//    //  |7|6|5|
//    //
//
//    return res;
//}
// vector<Scope> ScopeSystem::getQueenScope(Piece* pce) {}
// vector<Scope> ScopeSystem::getRookScope(Piece* pce) {}
// vector<Scope> ScopeSystem::getBishopScope(Piece* pce) {}
// vector<Scope> ScopeSystem::getKnightScope(Piece* pce) {}
// vector<Scope> ScopeSystem::getPawnScope(Piece* pce) {}
//
// bool ScopeSystem::isScopeIntersect(Scope scope, Loc point) {}
//