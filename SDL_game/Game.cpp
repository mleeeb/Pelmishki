#include "Game.hpp"

#include <iostream>

#include "InputHandler.hpp"
#include "TextureManager.hpp"

bool Game::init(std::string title, int w, int h, int flags) {
  window_ = SDL_CreateWindow(title.c_str(), w, h, flags);
  if (window_ != 0) {
    std::cout << "window created" << std::endl;
    renderer_ = SDL_CreateRenderer(window_, NULL);
    if (renderer_ != 0) {
      std::cout << "renderer created" << std::endl;
      if (TextureManager::Instance().load("assets/main.bmp", "main_char",
                                          renderer_) != 0) {
        std::cout << "main texture created" << std::endl;
      } else {
        std::cerr << "main texture error" << std::endl;
        return false;
      }
      if (TextureManager::Instance().load("assets/go.bmp", "go", renderer_) !=
          0) {
        std::cout << "go texture created" << std::endl;
      } else {
        std::cerr << "go texture error" << std::endl;
        return false;
      }
      go.load("go", 100, 300, 200, 200);
      main_char.load("main_char", 100, 100, 200, 200);

    } else {
      std::cerr << "renderer error" << std::endl;
      return false;
    }
  } else {
    std::cerr << "window error" << std::endl;
    return false;
  }
  return true;
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
  SDL_RenderClear(renderer_);

  go.draw(renderer_);
  main_char.draw(renderer_);

  SDL_RenderPresent(renderer_);
}

void Game::update() {
  go.update();
  main_char.update();
}

void Game::handleEvents() {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        stopGame();
        break;
      case SDL_EVENT_WINDOW_RESIZED:
        std::cout << "resize" << std::endl;
        break;
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
      case SDL_EVENT_MOUSE_BUTTON_UP:
      case SDL_EVENT_MOUSE_MOTION:
      case SDL_EVENT_KEY_DOWN:
        InputHandler::Instance()->handle(event);
        break;
      default:
        break;
    }
  }
}

void Game::clean() {
  std::cout << "exit" << std::endl;
  go.clean();
  main_char.clean();
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}