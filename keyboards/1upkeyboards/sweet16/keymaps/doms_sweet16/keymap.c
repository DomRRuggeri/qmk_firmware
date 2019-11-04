#include QMK_KEYBOARD_H
#include <customizations.h>

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
  ALT_TAB = SAFE_RANGE,
  ONE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        } 
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;

    case ONE:
      if (record->event.pressed) {
        send_string(Phrase1);
      } else {
      }
      break;

  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_4x4(
    KC_P7, KC_P8, KC_P9,   KC_BSPC, 
    KC_P4, KC_P5, KC_P6,   KC_PPLS, 
    KC_P1, KC_P2, KC_P3,   KC_PMNS, 
    KC_P0, KC_P0, KC_PDOT, LT(1, KC_PENT)
    ),

  [1] = LAYOUT_ortho_4x4(
    TO(5),   TO(6),     TO(7),   RESET,
    TO(4),   KC_NO,     KC_NO,   KC_NO, 
    TO(3),   KC_NO,     KC_NO,   KC_NO, 
    TO(2),   KC_NLCK,   ONE,     KC_TRNS
    ),

	[2] = LAYOUT_ortho_4x4(
    KC_ESC,         LCTL(LSFT(KC_ESC)),   ALT_TAB,      LGUI(KC_L), 
    LCTL(KC_C),     LCTL(KC_V),           KC_NO,        LCTL(KC_F), 
    LCTL(KC_GRV),   LCTL(KC_F5),          LCTL(KC_T),   LCTL(KC_W),
    LCTL(KC_ENT),   KC_NO,                KC_NO,        TO(0)
    ),

	[3] = LAYOUT_ortho_4x4(
    KC_TRNS,         LCTL(KC_PGUP), LCTL(KC_PGDN),    KC_NO, 
    KC_CUT,          KC_TRNS,       LCTL(KC_Y),       LCTL(KC_H), 
    LCTL(KC_HOME),   LCTL(KC_END),  LCTL(LSFT(KC_T)), LCTL(LSFT(KC_N)),
    KC_F13,          KC_F14,        KC_F15,           TO(0)
    ),

	[4] = LAYOUT_ortho_4x4(
    TO(0),      KC_MUTE,    KC_VOLD,    KC_VOLU, 
    KC_LALT,    KC_LSFT,    KC_NO,      KC_TAB, 
    LGUI(KC_4), LGUI(KC_5), LGUI(KC_6), LGUI(KC_7), 
    LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), TO(0)
    ),

	[5] = LAYOUT_ortho_4x4(
    TO(0),         LGUI(KC_K),  LGUI(KC_LGUI), LGUI(KC_L), 
    LGUI(KC_LEFT), LGUI(KC_UP), LGUI(KC_DOWN), LGUI(KC_RGHT), 
    LGUI(KC_E),    LCTL(KC_L),  KC_NO,         KC_TRNS, 
    LALT(KC_F4),   KC_NO,       KC_NO,         TO(0)
    ),

	[6] = LAYOUT_ortho_4x4(
    KC_LBRC, KC_W,  KC_RBRC, KC_ESC, 
    KC_A,    KC_S,  KC_D,    KC_ENT, 
    KC_NO,   KC_NO, KC_NO,   KC_NO, 
    KC_NO,   KC_C,  KC_SPC,  TO(0)
    ),

  [7] = LAYOUT_ortho_4x4(
    RGB_TOG, RGB_MOD,  RGB_RMOD, KC_ESC, 
    RGB_HUI,    RGB_SAI,  RGB_VAI,    KC_ENT, 
    RGB_HUD,   RGB_SAD, RGB_VAD,   KC_NO, 
    KC_NO,   KC_C,  KC_SPC,  TO(0)
    )

};
