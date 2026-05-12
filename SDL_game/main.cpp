#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Game.hpp"

Game* g = 0;

int main(int argv, char** argc) {
  g = new Game();
  if (g->init("TEST WINDOW", 640, 480, SDL_WINDOW_RESIZABLE)) {
    g->startGame();
  } else {
    return 1;
  }

  while (g->isRunning()) {
    g->handleEvents();
    g->update();
    g->render();
  }
  g->clean();
  return 0;
}