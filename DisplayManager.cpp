#include "DisplayManager.h"

DisplayManager::DisplayManager()
  : tft_(TFT_CS, TFT_DC, TFT_RST) {
  currentBgColor_ = UI_BG_DARK;
}

void DisplayManager::begin() {
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);

  Serial.println("[DISPLAY] Initializing...");
  tft_.begin();
  tft_.setRotation(DISPLAY_ROTATION);
  tft_.invertDisplay(false);

  Serial.println("[DISPLAY] Ready");
  clear();
}

void DisplayManager::clear(uint16_t color) {
  tft_.fillScreen(color);
  currentBgColor_ = color;
}

void DisplayManager::fillBackground(uint16_t color) {
  currentBgColor_ = color;
  tft_.fillScreen(color);
}

void DisplayManager::showStartupScreen() {
  clear(UI_BG_DARK);
  tft_.setTextColor(UI_TEXT, UI_BG_DARK);
  tft_.setTextSize(2);
  tft_.setCursor(28, 70);
  tft_.println("POCKET MUSIC PLAYER");
  tft_.setCursor(90, 110);
  tft_.println("DISPLAY OK");

  delay(800);
}

void DisplayManager::showBluetoothWaiting(bool connected) {
  clear(UI_BG_DARK);
  tft_.setTextColor(UI_TEXT, UI_BG_DARK);
  tft_.setTextSize(2);

  tft_.setCursor(26, 70);
  tft_.println("POCKET MUSIC PLAYER");

  if (connected) {
    tft_.setCursor(70, 110);
    tft_.println("Bluetooth Connected");
  } else {
    tft_.setCursor(58, 110);
    tft_.println("Bluetooth");
    tft_.setCursor(42, 135);
    tft_.println("Waiting for device...");
  }
}

void DisplayManager::showDisconnected() {
  showBluetoothWaiting(false);
}

void DisplayManager::showConnected() {
  showBluetoothWaiting(true);
}

void DisplayManager::showNoArtPlaceholder() {
  int x = ALBUM_ART_X;
  int y = ALBUM_ART_Y;
  int s = ALBUM_ART_SIZE;

  tft_.fillRoundRect(x, y, s, s, 8, UI_PANEL);
  tft_.drawRoundRect(x, y, s, s, 8, UI_TEXT_MUTED);

  tft_.setTextColor(UI_TEXT_MUTED, UI_PANEL);
  tft_.setTextSize(2);
  int16_t textW = 5 * 12;  // rough estimate
  tft_.setCursor(x + (s - textW) / 2, y + s / 2 - 10);
  tft_.print("NO ART");
}

void DisplayManager::drawClock(uint8_t hour, uint8_t minute) {
  char clockBuf[16];
  snprintf(clockBuf, sizeof(clockBuf), "%02d:%02d", hour, minute);

  tft_.setTextColor(UI_TEXT, currentBgColor_);
  tft_.setTextSize(1);
  tft_.setCursor(250, 10);
  tft_.print(clockBuf);
}

void DisplayManager::drawSource(const char* sourceText) {
  tft_.setTextColor(UI_TEXT_MUTED, currentBgColor_);
  tft_.setTextSize(1);
  tft_.setCursor(SOURCE_LABEL_X, SOURCE_LABEL_Y);
  tft_.print(sourceText);
}

void DisplayManager::drawTextBlock(const char* text,
                                   int x,
                                   int y,
                                   int maxWidth,
                                   uint16_t color,
                                   uint8_t size,
                                   bool allowScroll) {
  (void)allowScroll;
  tft_.setTextColor(color, currentBgColor_);
  tft_.setTextSize(size);
  tft_.setCursor(x, y);

  int textLen = strlen(text);
  if (textLen == 0) {
    tft_.print(" ");
    return;
  }

  int maxChars = maxWidth / (size * 6);
  if (maxChars < 1) maxChars = 1;

  if (textLen > maxChars) {
    char shortText[64];
    strncpy(shortText, text, sizeof(shortText) - 1);
    shortText[sizeof(shortText) - 1] = '\0';
    if (strlen(shortText) > maxChars) {
      shortText[maxChars - 1] = '.';
      shortText[maxChars] = '.';
      shortText[maxChars + 1] = '.';
      shortText[maxChars + 2] = '\0';
    }
    tft_.print(shortText);
  } else {
    tft_.print(text);
  }
}

void DisplayManager::drawNowPlaying(const char* title,
                                   const char* artist,
                                   const char* album,
                                   const char* sourceName,
                                   bool showNoArt,
                                   float progress,
                                   uint32_t positionMs,
                                   uint32_t durationMs,
                                   bool playing,
                                   uint16_t bgColor) {
  fillBackground(bgColor);

  drawSource(sourceName);

  // Title label area
  tft_.setTextColor(UI_TEXT_MUTED, bgColor);
  tft_.setTextSize(1);
  tft_.setCursor(16, 24);
  tft_.println("NOW PLAYING");

  int titleX = 16;
  int titleY = 44;
  int titleMaxW = 150;
  drawTextBlock(title, titleX, titleY, titleMaxW, UI_TEXT, 2, true);

  int artistY = 92;
  drawTextBlock(artist, 16, artistY, 150, UI_TEXT_MUTED, 2, true);

  int albumY = 118;
  drawTextBlock(album, 16, albumY, 150, UI_TEXT_MUTED, 2, true);

  // Album-art placeholder or area
  int ax = ALBUM_ART_X;
  int ay = ALBUM_ART_Y;
  int s = ALBUM_ART_SIZE;

  tft_.fillRoundRect(ax, ay, s, s, 8, UI_PANEL);
  tft_.drawRoundRect(ax, ay, s, s, 8, UI_TEXT_MUTED);

  if (showNoArt) {
    tft_.setTextColor(UI_TEXT_MUTED, UI_PANEL);
    tft_.setTextSize(2);
    int16_t textW = 5 * 12;
    tft_.setCursor(ax + (s - textW) / 2, ay + s / 2 - 10);
    tft_.print("NO ART");
  } else {
    tft_.setTextColor(UI_TEXT, UI_PANEL);
    tft_.setTextSize(2);
    tft_.setCursor(ax + 18, ay + s / 2 - 10);
    tft_.print("ART");
  }

  drawProgressBar(progress, positionMs, durationMs);

  int buttonY = 212;
  int buttonH = 20;
  int buttonW = 70;
  int leftX = 16;
  int midX = 124;
  int rightX = 230;

  drawControlButton(leftX, buttonY, buttonW, buttonH, "<<", true);
  drawControlButton(midX, buttonY, 90, buttonH, playing ? "||" : ">", true);
  drawControlButton(rightX, buttonY, buttonW, buttonH, ">>", true);
}

void DisplayManager::drawControlButton(int x, int y, int w, int h, const char* label, bool active) {
  uint16_t fill = active ? UI_ACCENT : UI_PANEL;
  uint16_t outline = active ? UI_ACCENT2 : UI_TEXT_MUTED;

  drawButtonBase(x, y, w, h, fill, outline);
  tft_.setTextColor(UI_TEXT, fill);
  tft_.setTextSize(2);
  int labelW = strlen(label) * 12;
  tft_.setCursor(x + (w - labelW) / 2, y + 3);
  tft_.print(label);
}

void DisplayManager::drawButtonBase(int x, int y, int w, int h, uint16_t fill, uint16_t outline) {
  tft_.fillRoundRect(x, y, w, h, 8, fill);
  tft_.drawRoundRect(x, y, w, h, 8, outline);
}

void DisplayManager::drawMediaButtons(bool previousActive, bool playPauseActive, bool nextActive) {
  int buttonY = 210;
  int buttonH = 20;
  int leftW = 72;
  int centerW = 90;
  int rightW = 72;

  drawControlButton(16, buttonY, leftW, buttonH, "<<", previousActive);
  drawControlButton(118, buttonY, centerW, buttonH, ">", playPauseActive);
  drawControlButton(228, buttonY, rightW, buttonH, ">>", nextActive);
}

void DisplayManager::drawProgressBar(float progress, uint32_t positionMs, uint32_t durationMs) {
  int x = PROGRESS_BAR_X;
  int y = PROGRESS_BAR_Y;
  int w = PROGRESS_BAR_W;
  int h = PROGRESS_BAR_H;

  tft_.fillRoundRect(x, y, w, h, 4, UI_PANEL);
  tft_.drawRoundRect(x, y, w, h, 4, UI_TEXT_MUTED);

  int filled = (int)(progress * w);
  if (filled > w) filled = w;
  tft_.fillRoundRect(x, y, filled, h, 4, UI_ACCENT2);

  uint32_t posSec = (positionMs / 1000UL);
  uint32_t durSec = (durationMs / 1000UL);

  char posBuf[16];
  char durBuf[16];
  snprintf(posBuf, sizeof(posBuf), "%02d:%02d", posSec / 60, posSec % 60);
  snprintf(durBuf, sizeof(durBuf), "%02d:%02d", durSec / 60, durSec % 60);

  tft_.setTextColor(UI_TEXT, currentBgColor_);
  tft_.setTextSize(1);
  tft_.setCursor(24, 170);
  tft_.print(posBuf);

  tft_.setCursor(270, 170);
  tft_.print(durBuf);
}
