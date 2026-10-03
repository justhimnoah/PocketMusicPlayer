# Pocket Music Player — Stage 1

A lightweight Bluetooth Classic touchscreen music player for the ESP32, intended for a 320x240 landscape TFT UI.

## Purpose
This project is a stage-1 Bluetooth-only music player UI.
It is designed to show metadata and media controls from a paired phone/laptop using Classic Bluetooth AVRCP-style behavior.
It does not attempt to:
- receive audio
- act as a Bluetooth speaker
- decode audio
- perform Wi-Fi or cloud actions
- use Spotify APIs or OAuth
- use a web server

## Hardware list
- ESP32-S / ESP32-WROOM-32 board
- 2.4-inch 240x320 ILI9341 TFT display
- Touchscreen panel (controller must be confirmed from the physical hardware docs)
- 18650 Li-ion cell
- TP4056 charging module
- power switch
- battery holder
- common GND wiring

## Power-system warning
The firmware does not control the TP4056 charging behavior.
The battery, TP4056 module, switch, and regulated 3.3V logic power must be wired according to the actual board and module documentation.

Do not connect raw battery voltage directly to the ESP32 3.3V pin.
Use the board's real power path and regulated 3.3V rail only.

## Wiring table
TFT wiring:
- ESP32 GPIO18 -> TFT SCK
- ESP32 GPIO23 -> TFT MOSI
- ESP32 GPIO19 -> TFT MISO
- ESP32 GPIO5  -> TFT CS
- ESP32 GPIO16 -> TFT DC
- ESP32 GPIO17 -> TFT RST
- 3V3 -> TFT logic power where appropriate
- GND -> common ground

Touch wiring:
- Touch pins must come from the actual hardware datasheet
- Do not assume a controller without documentation
- Set the exact controller type, CS, IRQ, and calibration in Config.h

## Exact controller note
The project intentionally leaves the touch controller selection as a hardware-doc-driven value in `Config.h`.
This prevents guessing and keeps the app modifiable.

## Arduino IDE installation
1. Install Arduino IDE 2.x
2. Install ESP32 board package:
   - Boards Manager -> ESP32 by Espressif Systems
3. Select board:
   - ESP32 Dev Module
   - ESP32-WROOM-32 compatible
4. Select the correct COM port
5. Open `PocketMusicPlayer.ino`
6. Upload

## Required board package
- ESP32 Arduino Core by Espressif

Recommended stable target:
- Arduino-ESP32 core 2.0.11

## Required libraries
- Adafruit GFX Library
- Adafruit ILI9341
- XPT2046_Touchscreen (only if the actual controller is XPT2046-compatible)
- BluetoothSerial (built into the ESP32 core)

## Bluetooth pairing procedure
1. Power on the device
2. Ensure the paired phone or laptop is discoverable
3. Pair with the ESP32 using the configured Bluetooth name:
   - PocketMusicPlayer
4. Start media playback on the phone/laptop
5. The ESP32 will show connected/disconnected state and metadata updates

## Expected display behavior
- Startup screen with "POCKET MUSIC PLAYER"
- "DISPLAY OK" screen before Bluetooth initialization
- Bluetooth waiting screen
- connected state when a device pairs
- landscape 320x240 music UI
- title / artist / album / progress bar / controls

## Album-art limitations
- Real album art is only used if the actual Bluetooth stack exposes it
- if no real artwork is available, the app uses a clean square "NO ART" placeholder
- no fake artwork or generated art is used

## Troubleshooting
- TFT not lighting: verify TFT power, GND, SPI wiring, RST/CS pins
- display upside down: check rotation and `DISPLAY_ROTATION`
- touch not responding: re-check actual controller type, CS, IRQ, and calibration
- Bluetooth not connecting: verify board package and pairing flow
- no metadata: the host may not expose AVRCP metadata on the current pairing

## How to modify pins
Edit the constants in `Config.h`:
- TFT pins
- touch pins
- display rotation
- calibration values
- Bluetooth name

## How to modify UI
- Colors: `Config.h`
- layout: `MusicUI.cpp`
- drawing primitives: `DisplayManager.cpp`

## Final note
This is a clean Arduino IDE project scaffold. The exact touchscreen hardware values are intentionally isolated in `Config.h` so the project remains honest and does not invent undocumented hardware behavior.