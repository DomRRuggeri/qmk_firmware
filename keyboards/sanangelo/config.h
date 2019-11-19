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
#define PRODUCT         San Angelo
#define DESCRIPTION     San Angelo 69-Key Handwired Winebox Keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/*
 * Keyboard Matrix Assignments
 */
#define MATRIX_ROW_PINS { B0, B0, B0, B3, B4 }
#define MATRIX_COL_PINS { B5, B6, B7, C0, C1, C2, C3, C4, C5, C6, C7, D0, D1, D2, D3, D4 }

#define DIODE_DIRECTION COL2ROW

/*
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 13
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
*/
#define RGB_DI_PIN D1
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 32
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8