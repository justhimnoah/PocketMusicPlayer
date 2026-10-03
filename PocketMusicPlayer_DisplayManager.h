#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "Config.h"

class DisplayManager {
 public:
  DisplayManager();
  void begin();
  void clear(uint16_t color = UI_BG_DARK);
  void showStartupScreen();
  void showBluetoothWaiting(bool connected);
  void showDisconnected();
  void showConnected();
  void showNoArtPlaceholder();
  void drawClock(uint8_t hour, uint8_t minute);
  void drawSource(const char* sourceText);
  void drawNowPlaying(const char* title,
                      const char* artist,
                      const char* album,
                      const char* sourceName,
                      bool showNoArt,
                      float progress,
                      uint32_t positionMs,
                      uint32_t durationMs,
                      bool playing,
                      uint16_t bgColor);
  void drawProgressBar(float progress, uint32_t positionMs, uint32_t durationMs);
  void drawControlButton(int x, int y, int w, int h, const char* label, bool active);
  void drawMediaButtons(bool previousActive, bool playPauseActive, bool nextActive);
  void drawSimpleText(const char* text, int x, int y, uint16_t color, uint8_t size = 2);
  void drawLargeText(const char* text, int x, int y, uint16_t color, uint8_t size = 2);
  void fillBackground(uint16_t color);

  Adafruit_ILI9341& getTft() { return tft_; }

 private:
  Adafruit_ILI9341 tft_;
  uint16_t currentBgColor_;
  void drawButtonBase(int x, int y, int w, int h, uint16_t fill, uint16_t outline);
  void drawTextBlock(const char* text, int x, int y, int maxWidth, uint16_t color, uint8_t size, bool allowScroll);
};
