#include QMK_KEYBOARD_H

#define _DEFAULT 0
#define _FUNC 1
#define _LEDS 2

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum {
  TD_ESC_CMD = 0,
  TD_QUOTE,
};

enum custom_keycodes {
  DRUGGERI = SAFE_RANGE,
  NOTEPAD,
  CTRL_CTV,
  ALT_TAB,
  LBRC,
  RBRC
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DRUGGERI:
      if (record->event.pressed) {
		uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
    uint8_t ctrld = get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL));
		if (shifted) {
			uint8_t mods = get_mods();
			clear_mods();
			SEND_STRING("EAS\\druggeri$$"SS_TAP(X_TAB));
			set_mods(mods);
      } else if (ctrld) {
        uint8_t mods = get_mods();
			  clear_mods();
			  SEND_STRING("druggeri1@ellsworth.onmicrosoft.com"SS_TAP(X_TAB));
			  set_mods(mods);
      } else {
		  SEND_STRING("druggeri$$"SS_TAP(X_TAB));
      }
	  } else {
      }
      break;

	case NOTEPAD:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_LGUI)"notepad"SS_TAP(X_ENTER));
      } else {
      }
      break;

	case LBRC:
      if (record->event.pressed) {
        uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
        if (shifted) {
			uint8_t mods = get_mods();
            clear_mods();
            tap_code(KC_LBRC);
            set_mods(mods);
        } else {
            register_mods(MOD_LSFT);
            tap_code(KC_LBRC);
            unregister_mods(MOD_LSFT);
        }
    }
	return false;

	case RBRC:
      if (record->event.pressed) {
        uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
        if (shifted) {
			uint8_t mods = get_mods();
            clear_mods();
            tap_code(KC_RBRC);
            set_mods(mods);
        } else {
            register_mods(MOD_LSFT);
            tap_code(KC_RBRC);
            unregister_mods(MOD_LSFT);
        }
    }
	return false;

	case CTRL_CTV:
	  if (record->event.pressed) {
		  SEND_STRING(SS_LCTRL("ctv")SS_TAP(X_ENTER));
	  }else {
      }
      break;

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

  }
  return true;
};

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1500) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

void dance_cmd_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_ESC);
  } else {
	register_code (KC_LCTL);
    register_code (KC_GRV);
  }
}

void dance_cmd_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_ESC);
  } else {
	unregister_code (KC_LCTL);
    unregister_code (KC_GRV);
  }
}

void dance_quote_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_QUOT);
  } else {
	register_code (KC_RSFT);
    register_code (KC_QUOT);
  }
}

void dance_quote_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_QUOT);
  } else {
	unregister_code (KC_RSFT);
    unregister_code (KC_QUOT);
  }
}

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _DEFAULT:
      rgblight_mode(30);
      rgblight_sethsv(224, 255, 240);
      break;

    case _FUNC:
      rgblight_mode(18);
      rgblight_sethsv(8, 255, 240);
      break;

    case _LEDS:
      rgblight_mode(14);
      rgblight_sethsv(128, 255, 240);
      break;
  }
  return state;
}

extern rgblight_config_t rgblight_config;

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    rgblight_mode(36);
    rgblight_sethsv(128, 255, 240);
  } else {
    (layer_state_set_user(layer_state));
  };

}

qk_tap_dance_action_t tap_dance_actions[] = {

  [TD_ESC_CMD]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cmd_finished, dance_cmd_reset),
  [TD_QUOTE] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_quote_finished, dance_quote_reset),

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DEFAULT] = LAYOUT_65_ansi(
    TD(TD_ESC_CMD),   KC_1,      KC_2,      KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,      KC_9,      KC_0,            KC_MINS,        KC_EQL,   KC_BSPC,   KC_HOME, 
    KC_TAB,           KC_Q,      KC_W,      KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,      KC_O,      KC_P,            LBRC,           RBRC,     KC_BSLS,   KC_END,
    LT(1, KC_CAPS),   KC_A,      KC_S,      KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,      KC_L,      KC_SCLN,         TD(TD_QUOTE),   KC_ENT,              KC_PGUP,
    KC_LSPO,          KC_Z,      KC_X,      KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,   KC_DOT,    KC_SLSH,         KC_RSPC,                  KC_UP,     KC_PGDN,
    KC_LCTL,          KC_LGUI,   KC_LALT,                      KC_SPC,                         KC_RALT,   LT(1, KC_APP),   KC_RCTL,        KC_LEFT,  KC_DOWN,   KC_RGHT
    ),
	
  [_FUNC] = LAYOUT_65_ansi(
    KC_GRV,    KC_F1,          KC_F2,     KC_F3,      LALT(KC_F4),   KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,        KC_F10,         KC_F11,        KC_F12,               KC_DEL,    RESET, 
    ALT_TAB,   LCTL(KC_GRV),   KC_TRNS,   KC_MYCM,    KC_TRNS,       KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,      KC_PSCR,        KC_TRNS,       LCTL(LSFT(KC_ESC)),   KC_TRNS,   TG(2), 
    KC_TRNS,   KC_TRNS,        KC_TRNS,   DRUGGERI,   KC_TRNS,       KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   LGUI(KC_L),   KC_TRNS,        LCTL(KC_F5),   KC_TRNS,                         TG(3),  
    KC_TRNS,   KC_TRNS,        KC_TRNS,   KC_CALC,    CTRL_CTV,      KC_TRNS,   NOTEPAD,   KC_MUTE,   KC_VOLD,   KC_VOLU,      LCTL(KC_GRV),   KC_TRNS,                             KC_PGUP,   KC_TRNS, 
    KC_TRNS,   KC_TRNS,        KC_TRNS,                              KC_TRNS,                                    KC_TRNS,      KC_TRNS,        KC_TRNS,       KC_HOME,              KC_PGDN,   KC_END
    ),
	
  [_LEDS] = LAYOUT_65_ansi(
    TG(2),     RGB_M_P,   RGB_M_B,   RGB_M_R,   RGB_M_SW,   RGB_M_SN,   RGB_M_K,   RGB_M_X,   RGB_M_G,   KC_NO,   KC_MUTE,   KC_VOLD,   KC_VOLU,   KC_NO,   DEBUG,   
    KC_NO,     RGB_TOG,   RGB_MOD,   RGB_RMOD,  KC_NO,      KC_NO,      KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_TRNS, 
    KC_NO,     RGB_HUI,   RGB_SAI,   RGB_VAI,   RGB_SPI,    KC_NO,      KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,     KC_NO,     KC_NO,              KC_NO,   
    KC_NO,     RGB_HUD,   RGB_SAD,   RGB_VAD,   RGB_SPD,    KC_NO,      KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,     KC_NO,                KC_NO,   KC_NO,   
    KC_NO,     KC_NO,     KC_NO,     KC_NO,                             KC_NO,                                    KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO
    ),
	
  // [3] = LAYOUT_65_ansi(
  //  KC_ESC, TO(0), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_U, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN3, KC_TRNS, KC_ACL2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_U, KC_NO, KC_ACL0, KC_NO, KC_NO, KC_BTN1, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_WH_D, KC_BTN2)
};
