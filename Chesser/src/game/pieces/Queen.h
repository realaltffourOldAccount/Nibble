#ifndef QUEEN_H
#define QUEEN_H
#pragma once

#include "Piece.h"

class Queen : public Piece {
    public:
        Queen(bool iswhite) : Piece(_Queen, iswhite) {}
};

#endif
