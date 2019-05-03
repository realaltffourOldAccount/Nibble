#ifndef BOARD_RENDERER_H
#define BOARD_RENDERER_H
#pragma once

#include "Board.h"
#include "MoveMaker.h"
#include "chsr_api.h"
#include "move/Cords.h"

class BoardRenderer {
 public:
  void Init(GameState *state, MoveMaker *maker, Board *_board);
  void Render(Board *board, int win_h, int win_w);

 private:
  GameState *_STATE;
  MoveMaker *maker = nullptr;
  Board *board = nullptr;
  ChoosenPiece *selectedInfo = nullptr;

  Textures::Texture *pieces_tex = nullptr;

  Object::Obj *mBoard = nullptr;

  Object::Obj *mWhiteKing = nullptr;
  Object::Obj *mWhiteQueen = nullptr;
  Object::Obj *mWhiteRook = nullptr;
  Object::Obj *mWhiteBishop = nullptr;
  Object::Obj *mWhiteKnight = nullptr;
  Object::Obj *mWhitePawn = nullptr;

  Object::Obj *mBlackKing = nullptr;
  Object::Obj *mBlackQueen = nullptr;
  Object::Obj *mBlackRook = nullptr;
  Object::Obj *mBlackBishop = nullptr;
  Object::Obj *mBlackKnight = nullptr;
  Object::Obj *mBlackPawn = nullptr;
};
#endif