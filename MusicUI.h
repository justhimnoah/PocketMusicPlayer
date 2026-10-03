#pragma once

#include <Arduino.h>
#include "DisplayManager.h"
#include "TouchManager.h"
#include "BluetoothManager.h"

enum class UIAction {
  NONE,
  PREVIOUS,
  PLAY_PAUSE,
  NEXT
};

class MusicUI {
 public:
  MusicUI();
  void begin(DisplayManager& display);
  void renderWaitingForDevice();
  void renderConnected();
  void renderDisconnected();
  void renderNowPlaying(const BluetoothManager& bt,
                        uint16_t backgroundColor,
                        uint8_t hour,
                        uint8_t minute);

  UIAction evaluateTouch(int x, int y) const;
  uint16_t resolveBackgroundColor(const BluetoothManager& bt) const;

 private:
  DisplayManager* display_;
  static uint16_t colorFromString(const String& text);
};
