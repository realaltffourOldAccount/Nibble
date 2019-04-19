#ifndef MOVE_H
#define MOVE_H
#pragma once

#include "../../utils.h"
#include "Cords.h"

class Move {
   public:
    Move(Cords play1, Cords play2) {
        mWhites = play1;
        mBlacks = play2;
    }

    Cords mWhites;
    Cords mBlacks;
};

#endif