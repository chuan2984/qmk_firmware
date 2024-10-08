#pragma once

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }
#define MATRIX_ROW_PINS { F6, F7, B1, B3, B2, B6 }

#define DIODE_DIRECTION COL2ROW

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 500

// WS2812 RGB LED strip input and number of LEDs
#define WS2812_DI_PIN D1
#define RGBLED_NUM 20
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT { 10, 10 }
#define RGBLIGHT_LAYERS
#define RGBLIGHT_SLEEP // If defined, the RGB lighting will be switched off when the host goes to sleep
#define RGBLIGHT_LIMIT_VAL 200 // max 255 (0.32A one side for 24 leds with 255, 0.29A at 250)
#define RGBLIGHT_HUE_STEP 10 // The number of steps to cycle through the hue by
#define RGBLIGHT_SAT_STEP 17 // The number of steps to increment the saturation by
#define RGBLIGHT_VAL_STEP 17 // The number of steps to increment the brightness by
