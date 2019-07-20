#ifndef PIECE_H
#define PIECE_H
#pragma once

enum PieceTypes {
    _King = 0,
    _Queen = 1,
    _Rook = 2,
    _Bishop = 3,
    _Knight = 4,
    _Pawn = 5
};

class Piece {
    public:
        Piece() {}
        Piece(PieceTypes _type, bool _iswhite) {
            type = _type;
            isWhite = _iswhite;
        }

        bool operator==(Piece* pce) {
            return (pce->type == type && pce->isWhite == isWhite);
        }

        void operator=(Piece* pce) {
            type = pce->type;
            isWhite = pce->isWhite;
        }

        int type = -1;
        bool isWhite = true;
        bool isChoosen = false;
};

#endif
