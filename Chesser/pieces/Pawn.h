#ifndef PAWN_H
#define PAWN_H
#pragma once

#include "Piece.h"

class Pawn : public Piece {
   public:
    Pawn(bool iswhite) : Piece(PieceTypes::_Pawn, iswhite) {}
};

#endif