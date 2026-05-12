#include "GameObject.hpp"

#include "TextureManager.hpp"

void GameObject::load(std::string tag, float x, float y, float w, float h) {
  x_ = x;
  y_ = y;
  w_ = w;
  h_ = h;
  texture_tag_ = tag;
  currentRow_ = 1;
  currentFrame_ = 1;
}

void GameObject::draw(SDL_Renderer* renderer) {
  TextureManager::Instance().drawFrame(texture_tag_, x_, y_, w_, h_,
                                       currentRow_, currentFrame_, renderer);
}

void GameObject::update() {
  // x_ += 0.1;
  currentFrame_ = int(((SDL_GetTicks() / 1000) % 6));
}

void GameObject::clean() { std::cout << "Clean game object" << std::endl; }
