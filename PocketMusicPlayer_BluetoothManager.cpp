#include "BluetoothManager.h"

BluetoothManager::BluetoothManager()
  : btSerial_(),
    connected_(false),
    source_("Bluetooth Music"),
    title_("Waiting for track..."),
    artist_("No artist"),
    album_("No album"),
    durationMs_(0),
    positionMs_(0),
    state_(MediaState::UNKNOWN) {
}

void BluetoothManager::begin() {
  Serial.println("[BT] Starting...");
  btSerial_.begin(BLUETOOTH_DEVICE_NAME);
  Serial.println("[BT] Ready");
}

void BluetoothManager::update() {
  connected_ = btSerial_.connected();

  if (connected_) {
    Serial.println("[BT] Connected");
  } else {
    // Keep running even while disconnected.
    // The UI should show a waiting state without rebooting or crashing.
  }
}

bool BluetoothManager::isConnected() const {
  return connected_;
}

void BluetoothManager::setSource(const String& source) {
  source_ = source;
}

void BluetoothManager::setMetadata(const String& title,
                                   const String& artist,
                                   const String& album,
                                   uint32_t durationMs,
                                   uint32_t positionMs,
                                   MediaState state) {
  title_ = title;
  artist_ = artist;
  album_ = album;
  durationMs_ = durationMs;
  positionMs_ = positionMs;
  state_ = state;
}

void BluetoothManager::sendPrevious() {
  Serial.println("[BT] Previous");
  // In a real AVRCP CT implementation, this is where the ESP-IDF AVRCP
  // call for previous would be inserted.
}

void BluetoothManager::sendPlayPause() {
  Serial.println("[BT] Play/Pause");
  // In a real AVRCP CT implementation, this is where the ESP-IDF AVRCP
  // call for play/pause would be inserted.
}

void BluetoothManager::sendNext() {
  Serial.println("[BT] Next");
  // In a real AVRCP CT implementation, this is where the ESP-IDF AVRCP
  // call for next would be inserted.
}

String BluetoothManager::getSource() const {
  return source_;
}

String BluetoothManager::getTitle() const {
  return title_;
}

String BluetoothManager::getArtist() const {
  return artist_;
}

String BluetoothManager::getAlbum() const {
  return album_;
}

uint32_t BluetoothManager::getDurationMs() const {
  return durationMs_;
}

uint32_t BluetoothManager::getPositionMs() const {
  return positionMs_;
}

MediaState BluetoothManager::getState() const {
  return state_;
}