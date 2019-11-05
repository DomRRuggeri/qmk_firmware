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

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_LOCK]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cmd_finished, dance_cmd_reset),
};

// Enum Macros
enum my_keycodes {
  PHRASES = SAFE_RANGE,
  WINOPEN,
  CTRL_CTV,
  COPYPASTE,
  
  // Must be last:
  DYNAMIC_MACRO_RANGE,
};

#include <dynamic_macro.h>

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
        return false;
  }

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Default Layer
  [_DEFAULT] = LAYOUT( \
      TD(TD_ESC_LOCK), KC_Q,    KC_W,   KC_E, KC_R, KC_T,    KC_Y, KC_U,    KC_I,    KC_O,           KC_P,   KC_BSPC,\
      LT(2, KC_TAB),   KC_A,    KC_S,   KC_D, KC_F, KC_G,    KC_H, KC_J,    KC_K,    KC_L,           LT(2, KC_ENT),\
      KC_LSFT,         KC_Z,    KC_X,   KC_C, KC_V, KC_B,    KC_N, KC_M,    KC_SLSH, KC_UP,          MT(MOD_RSFT, KC_SLSH),\
      KC_LCTL,         KC_LGUI, KC_LALT,      LT(1, KC_SPC), LT(3, KC_SPC), KC_LEFT, KC_DOWN  KC_RGHT \
      ),

  // Number Layer
  [_NUM] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
      KC_TRNS, KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, MT(MOD_RSFT, KC_BSLS), \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS\
      ),

  // Shifted Layer
  [_SHIFT] = LAYOUT( \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,\
      KC_TRNS, KC_UNDS, KC_PLUS, KC_COLN, KC_DQUO, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_PIPE, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS\
      ),

  // Fkey Layer
  [_FUNC] = LAYOUT( \
      KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, RESET,\
      KC_TRNS, KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS\
      ),

};
