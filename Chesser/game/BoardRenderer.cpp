#include "BoardRenderer.h"

void BoardRenderer::Init(GameState* state, MoveMaker* _maker, Board* _board) {
  maker = _maker;
  board = _board;
  _STATE = state;

  Object::createObject("board", "assets/board.png", Rect(0, 0, 512, 512));
  mBoard = Object::objs["board"];
  mBoard->scale(glm::vec2(_STATE->win_width / mBoard->getTex().x,
                          _STATE->win_height / mBoard->getTex().y));
}

void BoardRenderer::Render(Board* board, int win_h, int win_w) {
  mBoard->scale(glm::vec2(_STATE->win_width / mBoard->getTex().x,
                          _STATE->win_height / mBoard->getTex().y));
}
