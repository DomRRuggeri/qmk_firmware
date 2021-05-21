#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
#define _BASE 0

enum custom_keycodes {
  UP_URL = SAFE_RANGE
};


// Enum Macros
enum my_keycodes {
  PHRASES = SAFE_RANGE,
  WINOPEN,
  CTRL_CTV,
  LBRC,
  RBRC,
  COPYPASTE,
  CYCLEDIAL,
  CYCLEUNDO,
  CYCLESCRUB,
  CYCLEVSCRUB
};

enum dial_modes {
  SCROLL,
  CYCLEWIN,
  CYCLETAB,
  VOL,
  UNDOREDO,
  SCRUB,
  VSCRUB
};

bool is_alt_tab_active = false;
bool isRecording = false;
uint16_t alt_tab_timer = 0;

char DIAL_MODE = SCROLL;
char PREV = SCROLL;


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
    case 3:
      oled_write_P(PSTR("Guitar Pro\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  oled_write_P(PSTR("Dial 1: "), false);
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

      case UNDOREDO:
        oled_write_P(PSTR("Undo/Redo\n"), false);
        break;

      case SCRUB:
        oled_write_P(PSTR("Scrub\n"), false);
        break;

      case VSCRUB:
        oled_write_P(PSTR("Vertical Scrub\n"), false);
        break;
    }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();

  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
  //oled_write_P(PSTR(" ---- PocBox ----\n Proof of Concept\n"), false);
  oled_write_P(isRecording ? PSTR("Recording Macro...") : PSTR("                   "), false);

  

}
#endif

 void dynamic_macro_record_start_user(void) { 
  isRecording = true;
 }
  
void dynamic_macro_record_end_user(int8_t direction) {
  isRecording = false;
  }

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

        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        if (clockwise) {
          alt_tab_timer = timer_read();
          tap_code16(KC_TAB);
        } else {
          alt_tab_timer = timer_read();
          tap_code16(S(KC_TAB));
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

      case UNDOREDO:
        if (clockwise) {
          tap_code16(C(KC_Y));
        } else {
          tap_code16(C(KC_Z));
        }
        break;

      case SCRUB:
        if (clockwise) {
          uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
          if (shifted) {
            tap_code(KC_L);
          } else {
            tap_code(KC_RGHT);
          }
        } else { 
          uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
            if (shifted) {
              tap_code(KC_J);
            } else {
            tap_code(KC_LEFT);
            }
        }
        break;

      case VSCRUB:
        if (clockwise) {
          tap_code16(KC_DOWN);
        } else {
          tap_code16(KC_UP);
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
            tap_code(KC_F16);
            break;
          
          case CYCLEWIN:
            DIAL_MODE = CYCLETAB;
            tap_code(KC_F17);
            break;
        
          case CYCLETAB:
            DIAL_MODE = VOL;
            tap_code(KC_F18);
            break;

          case VOL:
            DIAL_MODE = SCROLL;
            tap_code(KC_F15);
            break;

          default:
            DIAL_MODE = SCROLL;
            tap_code(KC_F15);
            break;
        }
      }
      break;

    case CYCLEUNDO:
      if (record->event.pressed) {
        if (DIAL_MODE != UNDOREDO) {
            PREV = DIAL_MODE;
            DIAL_MODE = UNDOREDO;
            tap_code(KC_F19);
          } else { 
            DIAL_MODE = PREV;
          }
        }  
        break;
      
    case CYCLESCRUB:
      if (record->event.pressed) {
        if (DIAL_MODE != SCRUB) {
            PREV = DIAL_MODE;
            DIAL_MODE = SCRUB;
            tap_code(KC_F20);
          } else { 
            DIAL_MODE = PREV;
          }
        }  
        
        break;

    case CYCLEVSCRUB:
      if (record->event.pressed) {
        if (DIAL_MODE != VSCRUB) {
            PREV = DIAL_MODE;
            DIAL_MODE = VSCRUB;
            tap_code(KC_F21);
          } else { 
            DIAL_MODE = PREV;
          }
        }  
        
        break;
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_default(
    KC_ESC,          KC_1,      KC_2,      KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,      KC_9,      KC_0,            KC_MINS,        KC_EQL,   KC_BSPC,  KC_BSPC,        CYCLEDIAL,   KC_B,
    KC_TAB,          KC_Q,      KC_W,      KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,      KC_O,      KC_P,            KC_LBRC,        KC_RBRC,     KC_BSLS,       
    LT(1, KC_CAPS),  KC_A,      KC_S,      KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,      KC_L,      KC_SCLN,         KC_QUOTE,            KC_ENT,                  KC_4,     KC_5,    KC_6,    
    KC_LSPO,         KC_Z,      KC_X,      KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,   KC_DOT,    KC_SLSH,         KC_RSPC,  KC_RSPC,                            KC_1,     KC_UP,   KC_3,
    KC_LCTL,         KC_LGUI,   KC_LALT,                      KC_SPC,                          KC_RALT,  KC_APP,  KC_RGUI,  KC_RCTL,                                    KC_LEFT,  KC_DOWN, KC_RIGHT),

    [1] = LAYOUT_default(
    KC_ESC,   KC_1,      KC_2,      KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,      KC_9,      KC_0,            KC_MINS,        KC_EQL,   KC_BSPC,  KC_BSPC,        CYCLEDIAL,   KC_B,
    KC_TAB,   KC_Q,      KC_W,      KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,      KC_O,      KC_P,            KC_LBRC,        KC_RBRC,     KC_BSLS,       
    KC_CAPS,  KC_A,      KC_S,      KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,      KC_L,      KC_SCLN,         KC_QUOTE,            KC_ENT,                  KC_4,     KC_5,    RESET,    
    KC_LSPO,  KC_Z,      KC_X,      KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,   KC_DOT,    KC_SLSH,         KC_RSPC,  KC_RSPC,                            KC_1,     KC_UP,   KC_3,
    KC_LCTL,  KC_LGUI,   KC_LALT,                      KC_SPC,                          KC_RALT,  KC_APP,  KC_RGUI,  KC_RCTL,                                    KC_LEFT,  KC_DOWN, KC_RIGHT),


};

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 700) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}