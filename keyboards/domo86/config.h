/*
Copyright 2019 Dom Ruggeri

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    Dom Ruggeri
#define PRODUCT         DOMO86
#define DESCRIPTION     65% board with numpad PCB

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 20

/*
 * Keyboard Matrix Assignments
 */
#define MATRIX_ROW_PINS { B15, B9, B10, B11, B12 }
#define MATRIX_COL_PINS { B14, B4, B3, B2, B1, B0, A6, A7, A8, A15, A2, A1, A0, B8, B13, A13, A5, A4, A14, B5 }

#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { A9 }
#define ENCODERS_PAD_B { A10 }

#define ENCODER_RESOLUTION 4

#define TAP_CODE_DELAY 5
/*
#define RGB_DI_PIN C13
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
*/