#pragma once
#include <SDL3/SDL.h>

#include <iostream>

class GameObject {
 protected:
  std::string texture_tag_;
  int currentFrame_;
  int currentRow_;
  float x_, y_;
  float w_, h_;

 public:
  void load(std::string tag, float x, float y, float w, float h);
  void draw(SDL_Renderer* renderer);
  void update();
  void clean();
};
