#include QMK_KEYBOARD_H
#include <customizations.h>

// Layers
#define _DEFAULT 0
#define _FUNC 1
#define _MEDIA 2
#define _MUSIC 3

// Enum Tap Dances
enum tap_dances {
  TD_ESC_LOCK = 0,
  TD_QUOTE
};

// Enum Macros
enum my_keycodes {
  PHRASES = SAFE_RANGE,
  WINOPEN,
  CTRL_CTV,
  LBRC,
  RBRC,
  COPYPASTE,
  CYCLEDIAL
};

enum dial_modes {
  SCROLL,
  CYCLEWIN,
  CYCLETAB,
  VOL
}

DIAL_MODE = SCROLL;


#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);
  switch (get_highest_layer(layer_state)) {
    case 0:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case 1:
      oled_write_P(PSTR("FN\n"), false);
      break;
    case 2:
      oled_write_P(PSTR("ADJ\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  oled_write_P(PSTR("Dial: "), false);
    switch (DIAL_MODE) {
      case SCROLL:
        oled_write_P(PSTR("Scroll\n"), false);
        break;
          
      case CYCLEWIN:
        oled_write_P(PSTR("Window\n"), false);
        break;
        
      case CYCLETAB:
        oled_write_P(PSTR("Tab\n"), false);
        break;

      case VOL:
        oled_write_P(PSTR("Volume\n"), false);
        break;
    }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
  //oled_write_P(PSTR(" ---- PocBox ----\n Proof of Concept\n"), false);
}
#endif

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    switch (DIAL_MODE) {
      case SCROLL:
        if (clockwise) {
          tap_code(KC_PGDN);
        } else {
          tap_code(KC_PGUP);
        }
        break;
          
      case CYCLEWIN:
        if (clockwise) {
          register_code(KC_LALT);
          tap_code(KC_TAB);
          wait_ms(1000);
          unregister_code(KC_LALT);
        } else {
          register_code(KC_LALT);
          register_code(KC_LSFT);
          tap_code(KC_TAB);
          wait_ms(1000);
          unregister_code(KC_LALT);
          unregister_code(KC_LSFT);
        }
        break;
        
      case CYCLETAB:
        if (clockwise) {
          register_code(KC_LCTL);
          tap_code(KC_PGDN);
          unregister_code(KC_LCTL);
        } else {
          register_code(KC_LCTL);
          tap_code(KC_PGUP);
          unregister_code(KC_LCTL);
        }
        break;

      case VOL:
        if (clockwise) {
          tap_code(KC_VOLU);
          tap_code(KC_VOLU);
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
          tap_code(KC_VOLD);
          tap_code(KC_VOLD);
        }
        break;
    }
  }
}


// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {

    case CYCLEDIAL:
      if (record->event.pressed) {
        switch (DIAL_MODE) {
          case SCROLL:
            DIAL_MODE = CYCLEWIN;
            break;
          
          case CYCLEWIN:
            DIAL_MODE = CYCLETAB;
            break;
        
          case CYCLETAB:
            DIAL_MODE = VOL;
            break;

          default:
            DIAL_MODE = SCROLL;
            break;
        }
      }
      break;

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
          wait_ms(300);
          send_string(WinOpen2);
          wait_ms(300);
          SEND_STRING(SS_TAP(X_ENTER));
        } else if (ctrld) {
          clear_mods();
          SEND_STRING(SS_TAP(X_LGUI));
          wait_ms(300);
          send_string(WinOpen3);
          wait_ms(300);
          SEND_STRING(SS_TAP(X_ENTER));
        } else {
          SEND_STRING(SS_TAP(X_LGUI));
          wait_ms(300);
          send_string(WinOpen1);
          wait_ms(300);
          SEND_STRING(SS_TAP(X_ENTER));
        }
        return true;
      }

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
	return true;

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
	return true;

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

void shutdown_user() {
    /*
    rgblight_mode(RGB_Reset[0]);
    rgblight_sethsv(RGB_Reset[1],RGB_Reset[2],RGB_Reset[3]);
    */
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

/*
uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _DEFAULT:
      rgblight_mode(RGB_Def[0]);
      rgblight_sethsv(RGB_Def[1],RGB_Def[2],RGB_Def[3]);
      break;

    case _FUNC:
      rgblight_mode(RGB_Func[0]);
      rgblight_sethsv(RGB_Func[1],RGB_Func[2],RGB_Func[3]);
      break;

    case _MEDIA:
      rgblight_mode(RGB_Media[0]);
      rgblight_sethsv(RGB_Media[1],RGB_Media[2],RGB_Media[3]);
      break;
  }
  return state;
}

extern rgblight_config_t rgblight_config;

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    rgblight_mode(RGB_Caps[0]);
      rgblight_sethsv(RGB_Caps[1],RGB_Caps[2],RGB_Caps[3]);
  } else {
    (layer_state_set_user(layer_state));
  };

}*/


qk_tap_dance_action_t tap_dance_actions[] = {

  [TD_ESC_LOCK]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cmd_finished, dance_cmd_reset),
  [TD_QUOTE] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_quote_finished, dance_quote_reset),

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DEFAULT] = LAYOUT(
    
    CYCLEDIAL,
    TD(TD_ESC_LOCK),   KC_1,      KC_2,      KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,      KC_9,      KC_0,            KC_MINS,        KC_EQL,   KC_BSPC, KC_DEL,   KC_HOME,   KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,            KC_Q,      KC_W,      KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,      KC_O,      KC_P,            LBRC,           RBRC,     KC_BSLS,   KC_END,            KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    LT(1, KC_CAPS),    KC_A,      KC_S,      KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,      KC_L,      KC_SCLN,         TD(TD_QUOTE),   KC_ENT,              KC_PGUP,           KC_P4,   KC_P5,   KC_P6,
    KC_LSPO,           KC_Z,      KC_X,      KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,   KC_DOT,    KC_SLSH,         KC_RSPC,                  KC_UP,     KC_PGDN,           KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_LCTL,           KC_LGUI,   KC_LALT,                      KC_SPC,                         KC_RALT,   LT(1, KC_APP),   KC_RCTL,        KC_LEFT,  KC_DOWN,   KC_RGHT,                KC_0,        KC_PDOT   
    ),

  [_FUNC] = LAYOUT(
    
    CYCLEDIAL,
    KC_GRV,    KC_F1,          KC_F2,     KC_F3,      LALT(KC_F4),      KC_F5,          KC_F6,           KC_F7,     KC_F8,     KC_F9,        KC_F10,         KC_F11,        KC_F12,               KC_DEL, KC_DEL,    RESET,  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,    LCTL(KC_GRV),   KC_TRNS,   KC_MYCM,    DYN_REC_START1,   DYN_REC_STOP,   DYN_MACRO_PLAY1,   KC_TRNS,   KC_TRNS,   KC_TRNS,      KC_PSCR,        KC_TRNS,       LCTL(LSFT(KC_ESC)),   KC_TRNS,   TG(2), KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_TRNS,   COPYPASTE,      KC_TRNS,   PHRASES,    KC_TRNS,          KC_TRNS,        KC_TRNS,         KC_TRNS,   KC_TRNS,   LGUI(KC_L),   KC_TRNS,        LCTL(KC_F5),   KC_TRNS,                         TG(3),   KC_P4,   KC_P5,   KC_P6,
    KC_TRNS,   KC_TRNS,        KC_TRNS,   KC_CALC,    CTRL_CTV,         KC_TRNS,        WINOPEN,         KC_MUTE,   KC_VOLD,   KC_VOLU,      LCTL(KC_GRV),   KC_TRNS,                             KC_PGUP,   KC_NO, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_TRNS,   KC_TRNS,        KC_TRNS,                                 KC_TRNS,                                               KC_TRNS,      KC_TRNS,        KC_TRNS,       KC_HOME,              KC_PGDN,   KC_END,  KC_0,        KC_PDOT 
    ),

		/*
  [_MEDIA] = LAYOUT(
    TG(2),     RGB_M_P,   RGB_M_B,   RGB_M_R,   RGB_M_SW,   RGB_M_SN,   RGB_M_K,   RGB_M_X,   RGB_M_G,   KC_NO,   KC_MUTE,   KC_VOLD,   KC_VOLU,   KC_NO, KC_NO,   DEBUG,   
    KC_NO,     RGB_TOG,   RGB_MOD,   RGB_RMOD,  KC_NO,      KC_NO,      KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_TRNS, 
    KC_NO,     RGB_HUI,   RGB_SAI,   RGB_VAI,   RGB_SPI,    KC_NO,      KC_NO,     KC_NO,     KC_MPRV,   KC_NO,   KC_MNXT,   KC_MPLY,   KC_NO,              KC_NO,   
    KC_NO,     RGB_HUD,   RGB_SAD,   RGB_VAD,   RGB_SPD,    KC_NO,      KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,     KC_NO,                KC_K,   KC_NO,   
    KC_NO,     KC_NO,     KC_NO,     KC_NO,                             KC_NO,                                    KC_NO,     KC_NO,     KC_H,     KC_J,   KC_L
    ),

[_MUSIC] = LAYOUT(
    KC_NO,     MU_TOG,  MU_MOD,  KC_NO,  KC_NO,    KC_NO,    KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,   KC_NO,   
    KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO, 
    KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,     KC_NO,     KC_NO,              TG(3),   
    KC_NO,     PSONG,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,     KC_NO,                         KC_NO,   KC_NO,   
    KC_NO,     KC_NO,   KC_NO,                                               KC_NO,                     KC_NO,    KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO
    ),
    */
};
