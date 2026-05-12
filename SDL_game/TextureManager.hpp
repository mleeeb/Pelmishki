#pragma once

#include <SDL3/SDL.h>

#include <map>
#include <string>

class TextureManager {
 private:
  TextureManager() = default;
  TextureManager(const TextureManager&) = delete;
  TextureManager& operator=(const TextureManager&) = delete;
  TextureManager(TextureManager&&) = delete;
  TextureManager& operator=(TextureManager&&) = delete;

  std::map<std::string, SDL_Texture*> textureMap_;

 public:
  bool load(std::string fileName, std::string tag, SDL_Renderer* renderer);
  void draw(std::string tag, float x, float y, float width, float height,
            SDL_Renderer* renderer, SDL_FlipMode flip = SDL_FLIP_NONE);
  void drawFrame(std::string tag, float x, float y, float width, float height,
                 int currentRow, int currentFrame, SDL_Renderer* renderer,
                 SDL_FlipMode flip = SDL_FLIP_NONE);
  static TextureManager& Instance() {
    static TextureManager Instance_;
    return Instance_;
  }
};