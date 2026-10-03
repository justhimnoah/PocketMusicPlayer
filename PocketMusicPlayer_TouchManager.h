#pragma once

#include <Arduino.h>
#include "Config.h"

struct TouchPoint {
  bool valid;
  int x;
  int y;
  int pressure;
};

class TouchManager {
 public:
  TouchManager();
  void begin();
  bool isTouched() const;
  TouchPoint getTouch();

  int mapTouchX(int rawX) const;
  int mapTouchY(int rawY) const;

 private:
  bool initialized_;
  bool swapXY_;
  bool invertX_;
  bool invertY_;
};
