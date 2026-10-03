#include <Arduino.h>
#include "Config.h"
#include "DisplayManager.h"
#include "TouchManager.h"
#include "BluetoothManager.h"
#include "MusicUI.h"

DisplayManager display;
TouchManager touch;
BluetoothManager bluetooth;
MusicUI ui;

bool initialized = false;
bool connectedState = false;

void setup() {
  Serial.begin(115200);
  delay(200);

  display.begin();
  display.showStartupScreen();

  touch.begin();
  bluetooth.begin();

  ui.begin(display);

  initialized = true;
  Serial.println("[APP] Ready");
}

void loop() {
  bluetooth.update();
  connectedState = bluetooth.isConnected();

  // UI state
  if (!initialized) {
    return;
  }

  // Real hardware should determine the time from the board RTC or local clock.
  uint8_t hour = (millis() / 3600000UL) % 24;
  uint8_t minute = (millis() / 60000UL) % 60;

  if (!connectedState) {
    ui.renderDisconnected();
    delay(200);
    return;
  }

  // Example metadata; real AVRCP metadata should replace this when available.
  if (millis() % 10000 < 50) {
    bluetooth.setMetadata(
      "Midnight Motion",
      "Signal Drift",
      "Night Drive",
      243000,
      84000,
      MediaState::PLAYING
    );
  }

  uint16_t bg = ui.resolveBackgroundColor(bluetooth);
  ui.renderNowPlaying(bluetooth, bg, hour, minute);

  // Touch reading is intentionally minimal and hardware-doc driven.
  // Real touch implementation should poll the controller here.
  // Example event handling:
  // if (touch.isTouched()) {
  //   TouchPoint pt = touch.getTouch();
  //   UIAction action = ui.evaluateTouch(pt.x, pt.y);
  //   switch (action) { ... }
  // }

  delay(150);
}