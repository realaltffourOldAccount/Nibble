#ifndef BISHOP_H
#define BISHOP_H
#pragma once

#include "Piece.h"

class Bishop : public Piece {
    public:
        Bishop(bool iswhite) : Piece(PieceTypes::_Bishop, iswhite) {}
};

#endif
