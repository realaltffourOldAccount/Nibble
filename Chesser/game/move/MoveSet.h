//#ifndef MOVESET_H
//#define MOVESET_H
//#pragma once
//
//#include "../utils.h"
//#include "Cords.h"
//#include "Move.h"
//#include "univ_includes.h"
//
// class MoveSet {
//   public:
//    void Insert(Move* move, int begin);
//    void InsertRange(vector<Move*> moves, int begin);
//    void Delete(int begin);
//    void DeleteRange(int begin, int end);
//    void push_back(Move* move);
//    void push_front(Move* move);
//
//    Move* pop_back();
//    Move* pop_front();
//
//    void clear();
//
//    Move* operator[](const int x) { return mSet[x]; }
//
//    auto begin() { return mSet.begin(); }
//    auto end() { return mSet.end(); }
//
//   private:
//    deque<Move*> mSet;
//};
//
//#endif