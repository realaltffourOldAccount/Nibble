#ifndef CORDS_H
#define CORDS_H

#include <math.h>
#include <algorithm>
#include "../pieces/Piece.h"

using namespace std;

struct Loc {
    int file;
    int rank;
    bool operator==(const Loc& loc) {
        return file == loc.file && rank == loc.rank;
    }
    bool CheckInRange() {
        if (file >= 1 && file <= 8)
            if (rank >= 1 && rank <= 8) return true;
        return false;
    };

    int dist(Loc loc) {
        int x, y, x2, y2;
        x = rank;
        y = file;
        x2 = loc.rank;
        y2 = loc.file;

        return sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
    }

    string to_str() {
        string res;
        res.push_back(('a') + file);
        res.append(to_string(8 - rank));
        return res;
    }
};

class Cords {
   public:
    Cords() {}
    Cords(Loc orig) { mOrig = orig; }
    Cords(bool iswhite, int type, Loc dest, Loc orig, bool capt, Loc captloc,
          bool king_castle, bool queen_castle, bool check, bool checkmate) {
        isWhite = iswhite;
        mType = type;
        mDest = dest;
        mOrig = orig;
        mCapture = capt;
        mCaptLoc = captloc;
        mKingside_castle = king_castle;
        mQueenside_castle = queen_castle;
        mCheck = check;
        mCheckmate = checkmate;
    }

    bool CheckMove() {
        if (mDest == mOrig) return false;

        if (!mDest.CheckInRange()) return false;
        if (!mOrig.CheckInRange()) return false;

        if (mKingside_castle && mQueenside_castle) return false;

        if (mCaptLoc == mDest) return false;
        if (mCaptLoc == mOrig) return false;
    };

    string to_str() {
        string res;
        res.push_back(getCharFromType(mType));
        res.append(mOrig.to_str());
        if (mCapture) res.append("x");
        res.append(mDest.to_str());

        if (mCheckmate) {
            res.append("#");
            return res;
        }
        if (mCheck) res.append("!");
        return res;
    }

    bool isWhite = true;
    int mType = -1;
    Loc mDest = {' ', -1};
    Loc mOrig = {' ', -1};
    bool mCapture = false;
    Loc mCaptLoc = {' ', -1};
    bool mKingside_castle = false;
    bool mQueenside_castle = false;
    bool mCheck = false;
    bool mCheckmate = false;
};

#endif