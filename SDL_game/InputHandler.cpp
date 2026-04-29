#include "InputHandler.hpp"

InputHandler* InputHandler::instance_ = 0;

InputHandler::InputHandler() {
  for (int i = 0; i < 5; i++) {
    mouseStates_.push_back(false);
  }
  mousePosition_ = new Vector2D(0, 0);
}

InputHandler::~InputHandler() {}

bool InputHandler::getMouseButtonState(int buttonNumber) {
  return mouseStates_[buttonNumber];
}

void InputHandler::onMouseButtonDown(SDL_Event event) {
  if (event.button.button == SDL_BUTTON_LEFT) {
    mouseStates_[LEFT] = true;
    std::cout << "left" << std::endl;
  }
  if (event.button.button == SDL_BUTTON_MIDDLE) {
    mouseStates_[MIDDLE] = true;
    std::cout << "mid" << std::endl;
  }
  if (event.button.button == SDL_BUTTON_RIGHT) {
    mouseStates_[RIGHT] = true;
    std::cout << "right" << std::endl;
  }
  if (event.button.button == SDL_BUTTON_X1) {
    mouseStates_[BACK] = true;
    std::cout << "back" << std::endl;
  }
  if (event.button.button == SDL_BUTTON_X2) {
    mouseStates_[FORW] = true;
    std::cout << "forw" << std::endl;
  }
}

void InputHandler::onMouseButtonUp(SDL_Event event) {
  if (event.button.button == SDL_BUTTON_LEFT) {
    mouseStates_[LEFT] = false;
  }
  if (event.button.button == SDL_BUTTON_MIDDLE) {
    mouseStates_[MIDDLE] = false;
  }
  if (event.button.button == SDL_BUTTON_RIGHT) {
    mouseStates_[RIGHT] = false;
  }
  if (event.button.button == SDL_BUTTON_X1) {
    mouseStates_[BACK] = false;
  }
  if (event.button.button == SDL_BUTTON_X2) {
    mouseStates_[FORW] = false;
  }
}

Vector2D* InputHandler::getMousePosition() { return mousePosition_; }

void InputHandler::onMouseMotion(SDL_Event event) {
  mousePosition_->set_x(event.motion.x);
  mousePosition_->set_y(event.motion.y);
}
void InputHandler::onKeyDown(SDL_Event event) {
  keystates_ = SDL_GetKeyboardState(0);
  if (isKeyDown(SDL_SCANCODE_DOWN)) {
    std::cout << "down" << std::endl;
  }
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
  if (keystates_ != 0) {
    if (keystates_[key] == true) {
      return true;
    }
    return false;
  }
  return false;
}

void InputHandler::handle(SDL_Event event) {
  switch (event.type) {
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      onMouseButtonDown(event);
      break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
      onMouseButtonUp(event);
      break;
    case SDL_EVENT_MOUSE_MOTION:
      onMouseMotion(event);
      break;
    case SDL_EVENT_KEY_DOWN:
      onKeyDown(event);
      break;

    default:
      break;
  }
}