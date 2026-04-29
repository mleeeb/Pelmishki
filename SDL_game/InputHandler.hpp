#pragma once

#include <SDL3/SDL.h>

#include <Vector2D.hpp>
#include <iostream>
#include <vector>

enum mouse_buttons {
  LEFT = SDL_BUTTON_LEFT - 1,
  MIDDLE = SDL_BUTTON_MIDDLE - 1,
  RIGHT = SDL_BUTTON_RIGHT - 1,
  BACK = SDL_BUTTON_X1 - 1,
  FORW = SDL_BUTTON_X2 - 1
};

class InputHandler {
 public:
  static InputHandler* Instance() {
    if (instance_ == 0) {
      instance_ = new InputHandler();
    }
    return instance_;
  }

  void handle(SDL_Event event);
  // void clean();
  Vector2D* getMousePosition();
  bool getMouseButtonState(int buttonNumber);
  bool isKeyDown(SDL_Scancode key);

 private:
  InputHandler();
  ~InputHandler();
  static InputHandler* instance_;

  void onMouseButtonDown(SDL_Event event);
  void onMouseButtonUp(SDL_Event event);
  void onMouseMotion(SDL_Event event);
  void onKeyDown(SDL_Event event);

  std::vector<bool> mouseStates_;
  Vector2D* mousePosition_;
  const bool* keystates_;
};