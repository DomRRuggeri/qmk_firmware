/* Copyright 2019 Sebastian Williams
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xB195
#define DEVICE_VER      0x0001
#define MANUFACTURER    Dom Ruggeri
#define PRODUCT         Twain Enterpriser
#define DESCRIPTION     60% Bluetooth Keyboard

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 1

#define DIODE_DIRECTION COL2ROW

/* Pancake default pinout */
#define MATRIX_ROW_PINS { F7 }
#define MATRIX_COL_PINS { F4 }
#define UNUSED_PINS

#define AdafruitBleResetPin D4
#define AdafruitBleCSPin B4
#define AdafruitBleIRQPin E6