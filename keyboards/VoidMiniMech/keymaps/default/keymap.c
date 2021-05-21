#include QMK_KEYBOARD_H

#define _BASE 0


#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Hello Zack"), false);
  oled_write_P(PSTR("Line 2"), false);
  oled_write_P(PSTR("Line 3"), false);
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_default(
    KC_1, KC_2, KC_3),

};
