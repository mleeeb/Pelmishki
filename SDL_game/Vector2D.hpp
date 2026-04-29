#pragma once

#include <cmath>

class Vector2D {
 private:
  float x_;
  float y_;

 public:
  Vector2D(float x, float y) : x_(x), y_(y) {}
  float get_x() { return x_; }
  float get_y() { return y_; }
  void set_x(float new_x) { x_ = new_x; }
  void set_y(float new_y) { y_ = new_y; }
  float length() { return sqrt(x_ * x_ + y_ + y_); }
};