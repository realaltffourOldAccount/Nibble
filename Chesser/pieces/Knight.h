#ifndef KNIGHT_H
#define KNIGHT_H
#pragma once

#include "Piece.h"

class Knight : public Piece {
   public:
    Knight(bool iswhite) : Piece(PieceTypes::_Knight, iswhite){};
};

#endif