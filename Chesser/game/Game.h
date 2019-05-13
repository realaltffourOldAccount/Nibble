#ifndef GAME_H
#define GAME_H
#pragma once

#include "chsr_api.h"
#include "engine/GEngine.h"

class Game : public GEngine::Window {
  public:
    Game(void);
    ~Game(void);

  public: // GLFW Events
    void OnKey(int key, int scancode, int action, int mods);
    void OnMouseButton(int button, int action, int mods);

  private: // Functions
    void tick(void);
    void render(void);
};

#endif