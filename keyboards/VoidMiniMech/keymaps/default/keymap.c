#include QMK_KEYBOARD_H

#define _BASE 0

enum custom_keycodes {
  UP_URL = SAFE_RANGE
};

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Hello Zack.\nI made it work in QMK\n...faster than you! >:)"), false);
}
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UP_URL:
            if (record->event.pressed) {
                SEND_STRING("http://1upkeyboards.com");
            }
            return false;
            break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_default(
    KC_1, KC_2, KC_3),

};
