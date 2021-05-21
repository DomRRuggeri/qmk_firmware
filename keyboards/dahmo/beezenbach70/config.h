#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    Dahmo Keyboards
#define PRODUCT         Beezenbach70
#define DESCRIPTION     69% board with rotary encoders and oled screen

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { A2, A1, A0, B8, B13 }
#define MATRIX_COL_PINS { B14, B15, B9, B10, B11, B12, A14, A13, A8, B2, B3, B4, B5, A10, A9 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Encoder pins */
#define ENCODERS_PAD_A { A7, B0 }
#define ENCODERS_PAD_B { A6, B1 }
#define ENCODER_RESOLUTION 4

#define TAP_CODE_DELAY 5

#define ENCODER_DIRECTION_FLIP

/* number of backlight levels 
#define BACKLIGHT_LEVELS 10

Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE

Locking resynchronize hack 
#define LOCKING_RESYNC_ENABLE
*/
