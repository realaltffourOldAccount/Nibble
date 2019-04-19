#ifndef KING_H
#define KING_H
#pragma once

#include "Piece.h"

class King : public Piece {
   public:
    King(bool iswhite) : Piece(PieceTypes::_King, iswhite) {}
};

#endif