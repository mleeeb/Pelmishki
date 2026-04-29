#pragma once

#include <SDL3/SDL.h>

#include <string>

#include "GameObject.hpp"
#include "Player.hpp"

class Game {
 public:
  Game() {}
  ~Game() {}
  bool init(std::string, int, int, int);
  void render();
  void update();
  void handleEvents();
  void clean();
  void startGame() { running_ = true; }
  void stopGame() { running_ = false; }
  bool isRunning() { return running_; }
  GameObject go;
  Player main_char;

 private:
  bool running_ = false;
  SDL_Window* window_;
  SDL_Renderer* renderer_;
};