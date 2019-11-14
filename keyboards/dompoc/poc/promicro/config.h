#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x2011
#define DEVICE_VER      0x0001

/* key matrix pins */
#define MATRIX_ROW_PINS { F6, B1 }
#define MATRIX_COL_PINS { D4, D7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
