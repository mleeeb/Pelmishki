#pragma once

#include "GameObject.hpp"

class Player : public GameObject {
 public:
  void load(std::string tag, float x, float y, float w, float h);
  void draw(SDL_Renderer* renderer);
  void update();
  void clean();
};