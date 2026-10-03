#pragma once

#include <Arduino.h>
#include <BluetoothSerial.h>
#include "Config.h"

enum class MediaState {
  UNKNOWN,
  PLAYING,
  PAUSED,
  STOPPED
};

class BluetoothManager {
 public:
  BluetoothManager();
  void begin();
  void update();
  bool isConnected() const;

  void setSource(const String& source);
  void setMetadata(const String& title,
                   const String& artist,
                   const String& album,
                   uint32_t durationMs,
                   uint32_t positionMs,
                   MediaState state);

  void sendPrevious();
  void sendPlayPause();
  void sendNext();

  String getSource() const;
  String getTitle() const;
  String getArtist() const;
  String getAlbum() const;
  uint32_t getDurationMs() const;
  uint32_t getPositionMs() const;
  MediaState getState() const;

 private:
  BluetoothSerial btSerial_;
  bool connected_;
  String source_;
  String title_;
  String artist_;
  String album_;
  uint32_t durationMs_;
  uint32_t positionMs_;
  MediaState state_;
};
