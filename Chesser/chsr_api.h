#ifndef CHSR_API
#define CHSR_API
#include "univ_includes.h"
#include "macros.h"
#include "defs.h"

/*
        OS Specific Includes
*/

#if (__OS__ == __OS_WIN32__) || (__OS__ == __OS_WIN64__)
#include <Windows.h>
#elif (__OS__ == __OS_LINUX__)
#include <unistd.h>
#endif

/*
    Api Includes
*/
#include "Log.h"

#include "Board.h"
#include "pieces/Bishop.h"
#include "pieces/King.h"
#include "pieces/Knight.h"
#include "pieces/Pawn.h"
#include "pieces/Piece.h"
#include "pieces/Queen.h"
#include "pieces/Rook.h"
/*
    Api Defines
*/
#define PCE_NUMPR 8
#define BOARD_W 700
#define BOARD_H 700
#define CELL_W float(float(BOARD_W) / float(PCE_NUMPR))
#define CELL_H float(float(BOARD_H) / float(PCE_NUMPR))
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700
#define FPS_WINDOW_LIMIT 60
#define SELECT_SCALE 1.1f

#define WHITE_CHECKS_BLACK 1
#define BLACK_CHECKS_WHITE 2
#define WHITE_CHECKMATES_BLACK 3
#define BLACK_CHECKMATES_WHITE 4
#define NO_CHECKS 5

/*
    Api Functions
*/
#include "move/Move.h"
static Loc xy2loc(int x, int y) {
    Loc res;
    res.file = x;
    res.rank = y;
    return res;
}
// static Loc vec2Loc(sf::Vector2i xy) {
//    Loc res;
//    res.file = xy.x;
//    res.rank = xy.y;
//    return res;
//}
// static sf::Vector2i loc2xy(Loc loc) {
//    sf::Vector2i res;
//    res.x = loc.file;
//    res.y = loc.rank;
//    return res;
//}

// static Loc getLocOfWhiteKing(Board* mBoard) {
//    for (int i = 0; i < mBoard->get().size(); i++) {
//        for (int j = 0; j < mBoard->get()[i].size(); j++) {
//            if (mBoard->get()[i][j] != nullptr)
//                if (mBoard->get()[i][j]->isWhite)
//                    if (mBoard->get()[i][j]->type == PieceTypes::_King)
//                        return xy2loc(i, j);
//        }
//    }
//}
// static Loc getLocOfBlackKing(Board* mBoard) {
//    for (int i = 0; i < mBoard->get().size(); i++) {
//        for (int j = 0; j < mBoard->get()[i].size(); j++) {
//            if (mBoard->get()[i][j] != nullptr)
//                if (!mBoard->get()[i][j]->isWhite)
//                    if (mBoard->get()[i][j]->type == PieceTypes::_King)
//                        return xy2loc(i, j);
//        }
//    }
//}
#endif