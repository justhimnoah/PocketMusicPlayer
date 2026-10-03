#include "MusicUI.h"

MusicUI::MusicUI() : display_(nullptr) {
}

void MusicUI::begin(DisplayManager& display) {
  display_ = &display;
}

void MusicUI::renderWaitingForDevice() {
  if (!display_) return;
  display_->showBluetoothWaiting(false);
}

void MusicUI::renderConnected() {
  if (!display_) return;
  display_->showBluetoothWaiting(true);
}

void MusicUI::renderDisconnected() {
  if (!display_) return;
  display_->showBluetoothWaiting(false);
}

uint16_t MusicUI::resolveBackgroundColor(const BluetoothManager& bt) const {
  const String title = bt.getTitle();
  const String artist = bt.getArtist();

  uint16_t derived = colorFromString(title + artist);
  if (derived == 0) {
    return UI_BG_MEDIUM;
  }
  return derived;
}

uint16_t MusicUI::colorFromString(const String& text) {
  uint32_t hash = 2166136261u;
  for (size_t i = 0; i < text.length(); ++i) {
    hash ^= (uint8_t)text[i];
    hash *= 16777619u;
  }
  uint8_t r = (hash >> 16) & 0x1F;
  uint8_t g = (hash >> 8) & 0x3F;
  uint8_t b = hash & 0x1F;

  // Merge to a warm/dark, readable 16-bit color.
  return ((r << 11) | (g << 5) | b);
}

void MusicUI::renderNowPlaying(const BluetoothManager& bt,
                               uint16_t backgroundColor,
                               uint8_t hour,
                               uint8_t minute) {
  if (!display_) return;

  const String source = bt.getSource();
  const String title = bt.getTitle();
  const String artist = bt.getArtist();
  const String album = bt.getAlbum();
  uint32_t durationMs = bt.getDurationMs();
  uint32_t positionMs = bt.getPositionMs();
  bool playing = (bt.getState() == MediaState::PLAYING);

  float progress = 0.0f;
  if (durationMs > 0) {
    progress = constrain((float)positionMs / (float)durationMs, 0.0f, 1.0f);
  }

  bool artAvailable = false;
  display_->drawNowPlaying(title.c_str(),
                          artist.c_str(),
                          album.c_str(),
                          source.c_str(),
                          !artAvailable,
                          progress,
                          positionMs,
                          durationMs,
                          playing,
                          backgroundColor);

  display_->drawClock(hour, minute);
}

UIAction MusicUI::evaluateTouch(int x, int y) const {
  // Buttons are placed roughly as:
  //  left: x 0..100
  //  center: x 100..220
  //  right: x 220..320
  if (x >= 16 && x <= 88 && y >= 210 && y <= 230) {
    return UIAction::PREVIOUS;
  }
  if (x >= 118 && x <= 208 && y >= 210 && y <= 230) {
    return UIAction::PLAY_PAUSE;
  }
  if (x >= 228 && x <= 300 && y >= 210 && y <= 230) {
    return UIAction::NEXT;
  }
  return UIAction::NONE;
}
