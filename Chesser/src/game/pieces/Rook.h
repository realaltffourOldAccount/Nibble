#ifndef ROOK_H
#define ROOK_H
#pragma once

#include "Piece.h"

class Rook : public Piece {
    public:
        Rook(bool iswhite) : Piece(PieceTypes::_Rook, iswhite) {}
};

#endif
