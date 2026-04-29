#include "TextureManager.hpp"

#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>

bool TextureManager::load(std::string fileName, std::string tag,
                          SDL_Renderer* renderer) {
  SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());
  if (tmpSurface == 0) {
    return false;
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
  SDL_DestroySurface(tmpSurface);
  if (texture != 0) {
    textureMap_[tag] = texture;
    return true;
  }
  return false;
}

void TextureManager::draw(std::string tag, float x, float y, float width,
                          float height, SDL_Renderer* renderer,
                          SDL_FlipMode flip) {
  SDL_FRect srcRect;
  SDL_FRect dstRect;

  srcRect.x = srcRect.y = 0;
  srcRect.w = dstRect.w = width;
  srcRect.h = dstRect.h = height;
  dstRect.x = x;
  dstRect.y = y;
  SDL_RenderTextureRotated(renderer, textureMap_[tag], &srcRect, &dstRect, 0,
                           NULL, flip);
}

void TextureManager::drawFrame(std::string tag, float x, float y, float width,
                               float height, int currentRow, int currentFrame,
                               SDL_Renderer* renderer, SDL_FlipMode flip) {
  SDL_FRect srcRect;
  SDL_FRect dstRect;

  srcRect.x = width * currentFrame;
  srcRect.y = height * (currentRow - 1);
  srcRect.w = dstRect.w = width;
  srcRect.h = dstRect.h = height;
  dstRect.x = x;
  dstRect.y = y;
  SDL_RenderTextureRotated(renderer, textureMap_[tag], &srcRect, &dstRect, 0,
                           NULL, flip);
}
