#pragma once

#include <Arduino.h>

// -----------------------------------------------------------------------------
// Display configuration
// -----------------------------------------------------------------------------
#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240
#define DISPLAY_ROTATION 1  // 1 = landscape, 320x240

#define TFT_SCK  18
#define TFT_MOSI 23
#define TFT_MISO 19
#define TFT_CS    5
#define TFT_DC   16
#define TFT_RST  17
#define TFT_BACKLIGHT 4  // Optional; set to -1 if not connected to a PWM pin

// -----------------------------------------------------------------------------
// Bluetooth
// -----------------------------------------------------------------------------
#define BLUETOOTH_DEVICE_NAME "PocketMusicPlayer"

// -----------------------------------------------------------------------------
// Touch configuration
// -----------------------------------------------------------------------------
/*
  IMPORTANT:
  The supplied hardware documentation must determine the actual touchscreen controller,
  SPI bus usage, touch CS, IRQ, and calibration values.
  Do not invent them.
  If the documentation does not specify enough information, leave the values here
  as explicit placeholders instead of guessing.
*/
#define TOUCH_CONTROLLER_NAME "SET_FROM_HARDWARE_DOCS"

#define TOUCH_SCK  18
#define TOUCH_MISO 19
#define TOUCH_MOSI 23
#define TOUCH_CS   0   // REQUIRED: set from hardware datasheet
#define TOUCH_IRQ  0   // REQUIRED: set from hardware datasheet

#define TOUCH_SPI_FREQ 2000000

// Generic calibration defaults; these are intentionally easy to edit
#define TOUCH_CAL_X_MIN 150
#define TOUCH_CAL_X_MAX 3900
#define TOUCH_CAL_Y_MIN 150
#define TOUCH_CAL_Y_MAX 3900

#define TOUCH_INVERT_X false
#define TOUCH_INVERT_Y true
#define TOUCH_SWAP_XY false

// -----------------------------------------------------------------------------
// App tuning
// -----------------------------------------------------------------------------
#define UI_BG_DARK      0x0010
#define UI_BG_MEDIUM    0x0821
#define UI_PANEL        0x2124
#define UI_TEXT         0xFFFF
#define UI_TEXT_MUTED   0xBDF7
#define UI_ACCENT       0xF800 // warm red/orange accent
#define UI_ACCENT2      0x001F // cyan accent
#define UI_OK           0x07E0

#define PROGRESS_BAR_X  24
#define PROGRESS_BAR_Y  188
#define PROGRESS_BAR_W  272
#define PROGRESS_BAR_H   8

#define ALBUM_ART_X    190
#define ALBUM_ART_Y    58
#define ALBUM_ART_SIZE 110

#define SOURCE_LABEL_X  12
#define SOURCE_LABEL_Y  12

#define TEXT_TITLE_X    16
#define TEXT_TITLE_Y    48
#define TEXT_ARTIST_X   16
#define TEXT_ARTIST_Y   70
#define TEXT_ALBUM_X    16
#define TEXT_ALBUM_Y    92