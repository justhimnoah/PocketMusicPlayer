#include "TouchManager.h"

TouchManager::TouchManager()
  : initialized_(false),
    swapXY_(TOUCH_SWAP_XY),
    invertX_(TOUCH_INVERT_X),
    invertY_(TOUCH_INVERT_Y) {
}

void TouchManager::begin() {
  Serial.println("[TOUCH] Initializing...");

  // The target hardware may use a different controller than XPT2046.
  // This project isolates the exact controller selection in Config.h.
  // Keep the public API stable so the rest of the app does not care which
  // low-level device is behind the touch system.
  //
  // If your real hardware uses XPT2046, this is the place to initialize it.
  // If it uses another controller, substitute the correct library and pins.
  //
  // NOTE: This is intentionally simple and hardware-doc driven.

  initialized_ = true;
  Serial.println("[TOUCH] Ready");
}

bool TouchManager::isTouched() const {
  // A real touch implementation should poll the controller here.
  // This scaffold leaves the controller-specific code isolated to this class.
  return false;
}

TouchPoint TouchManager::getTouch() {
  TouchPoint p;
  p.valid = false;
  p.x = 0;
  p.y = 0;
  p.pressure = 0;

  // Real hardware integration should replace this stub with the actual
  // touch controller's API and calibration logic.
  return p;
}

int TouchManager::mapTouchX(int rawX) const {
  int x = rawX;
  if (invertX_) x = 4095 - x;
  if (swapXY_) x = rawX;  // kept simple for the generic mapper
  x = constrain(x, TOUCH_CAL_X_MIN, TOUCH_CAL_X_MAX);
  return map(x, TOUCH_CAL_X_MIN, TOUCH_CAL_X_MAX, 0, DISPLAY_WIDTH);
}

int TouchManager::mapTouchY(int rawY) const {
  int y = rawY;
  if (invertY_) y = 4095 - y;
  if (swapXY_) y = rawY;
  y = constrain(y, TOUCH_CAL_Y_MIN, TOUCH_CAL_Y_MAX);
  return map(y, TOUCH_CAL_Y_MIN, TOUCH_CAL_Y_MAX, 0, DISPLAY_HEIGHT);
}
