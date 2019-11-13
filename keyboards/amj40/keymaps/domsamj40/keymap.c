#include QMK_KEYBOARD_H
#include <customizations.h>

// Layers
#define _DEFAULT 0
#define _NUM 1
#define _SHIFT 2
#define _FUNC 3

// Enum Tap Dances
enum tap_dances {
  TD_ESC_LOCK = 0
};

// Enum Macros
enum my_keycodes {
  PHRASES = SAFE_RANGE,
  WINOPEN,
  CTRL_CTV,
  COPYPASTE
};

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PHRASES:
      if (record->event.pressed) {
	    	uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
        uint8_t ctrld = get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL));
		  if (shifted) {
			  uint8_t mods = get_mods();
			  clear_mods();
			  send_string(Phrase2);
        SEND_STRING(SS_TAP(X_TAB));
			  set_mods(mods);
      } else if (ctrld) {
        uint8_t mods = get_mods();
        clear_mods();
        send_string(Phrase3);
        SEND_STRING(SS_TAP(X_ENTER));
        set_mods(mods);
      } else {
        send_string(Phrase1);
		    SEND_STRING(SS_TAP(X_TAB));
      }
      return true;
	  }

	case WINOPEN:
      if (record->event.pressed) {
        uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
        uint8_t ctrld = get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL));
        if (shifted){
          clear_mods();
          SEND_STRING(SS_TAP(X_LGUI));
          _delay_ms(300);
          send_string(WinOpen2);
          _delay_ms(300);
          SEND_STRING(SS_TAP(X_ENTER));
        } else if (ctrld) {
          clear_mods();
          SEND_STRING(SS_TAP(X_LGUI));
          _delay_ms(300);
          send_string(WinOpen3);
          _delay_ms(300);
          SEND_STRING(SS_TAP(X_ENTER));
        } else {
          SEND_STRING(SS_TAP(X_LGUI));
          _delay_ms(300);
          send_string(WinOpen1);
          _delay_ms(300);
          SEND_STRING(SS_TAP(X_ENTER));
        }
        return true;
      }

	case CTRL_CTV:
	  if (record->event.pressed) {
		  SEND_STRING(SS_LCTRL("ctv")SS_TAP(X_ENTER));
	  }else {
      }
      break;

  case COPYPASTE:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("c"));
      } else {
        SEND_STRING(SS_LCTRL("v"));
      }
      return true;

  }
  return true;
};

//void matrix_init_user() {
//    rgblight_mode(RGB_0[0]);
//    rgblight_sethsv(RGB_0[1],RGB_0[2],RGB_0[3]);
//}
extern rgblight_config_t rgblight_config;

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case 0:
      rgblight_mode(RGB_0[0]);
      rgblight_sethsv(RGB_0[1],RGB_0[2],RGB_0[3]);
      break;

    case  1:
      rgblight_mode(RGB_1[0]);
      rgblight_sethsv(RGB_1[1],RGB_1[2],RGB_1[3]);
      break;

    case 2:
      rgblight_mode(RGB_2[0]);
      rgblight_sethsv(RGB_2[1],RGB_2[2],RGB_2[3]);
      break;

    case 3:
      rgblight_mode(RGB_3[0]);
      rgblight_sethsv(RGB_3[1],RGB_3[2],RGB_3[3]);
      break;
  }
  return state;
}

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
      rgblight_mode(RGB_Caps[0]);
      rgblight_sethsv(RGB_Caps[1],RGB_Caps[2],RGB_Caps[3]);
  } else {
    (layer_state_set_user(layer_state));
  };

}

void shutdown_user() {
  rgblight_mode(RGB_Reset[0]);
  rgblight_sethsv(RGB_Reset[1],RGB_Reset[2],RGB_Reset[3]);
}

void dance_cmd_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_ESC);
  } else {
	  register_code (KC_LGUI);
    register_code (KC_L);
  }
}

void dance_cmd_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_ESC);
  } else {
	 unregister_code (KC_LGUI);
    unregister_code (KC_L);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_LOCK]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cmd_finished, dance_cmd_reset),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Default Layer
  [0] = LAYOUT( \
      TD(TD_ESC_LOCK), KC_Q,    KC_W,         KC_E, KC_R, KC_T,    KC_Y, KC_U,    KC_I,    KC_O,           KC_P,   KC_BSPC,\
      LT(3, KC_TAB),   KC_A,    KC_S,         KC_D, KC_F, KC_G,    KC_H, KC_J,    KC_K,    KC_L,           LT(2, KC_ENT),\
      KC_LSPO,         KC_Z,    KC_X,         KC_C, KC_V, KC_B,    KC_N, KC_M,    KC_SLSH, KC_UP,          KC_RSPC,\
      KC_LCTL,         KC_LGUI, ALT_T(KC_APP),      LT(1, KC_SPC), LT(2, KC_SPC), KC_LEFT, KC_DOWN,  KC_RGHT \
      ),

  // Number Layer
  [1] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
      KC_TRNS, KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_SCLN, KC_DQUO, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_COMM, KC_DOT, KC_LBRC, KC_RBRC, MT(MOD_RSFT, KC_BSLS), \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS\
      ),

  // More Layer
  [2] = LAYOUT( \
      KC_TILD, KC_EXLM, KC_AT,     KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,\
      KC_TRNS, KC_F11,  KC_F12,  DEBUG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_VAI, KC_COMM, KC_DOT,
       LCTL(KC_GRV), KC_TRNS, KC_PIPE, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS\
      ),

  // Macro Layer
  [3] = LAYOUT( \
      KC_TRNS, KC_F1,         KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_PSCR, RESET,\
      KC_TRNS, LCTL(KC_GRV),  COPYPASTE, PHRASES, KC_DQUO, TG(4), KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS, \
      KC_TRNS, KC_TRNS,       KC_TRNS,   KC_CAPS, CTRL_CTV, KC_TRNS, WINOPEN, KC_TRNS, KC_LCBR, KC_PGUP, KC_TRNS, \
      KC_TRNS, KC_TRNS,       KC_TRNS,   KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END\
      ),

 // Game Layer
  [4] = LAYOUT( \
      KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,\
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS,   KC_SPC, KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS\
      ),
};
