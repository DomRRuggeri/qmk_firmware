#include "pocbox.h"

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
  REBOOT = SAFE_RANGE,
  ALT_TAB,
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
          tap_code(KC_PGDN);
        } else {
          tap_code(KC_PGUP);
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
        } else {
          tap_code(KC_VOLD);
        }
        break;
    }
  }
}

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

    case REBOOT:
      if (record->event.pressed) {
		  SEND_STRING(SS_TAP(X_LGUI));
		  _delay_ms(300);
		  SEND_STRING("powershell");
		  _delay_ms(500);
		  SEND_STRING(SS_TAP(X_ENTER));
		  _delay_ms(500);
		  SEND_STRING("restart-computer -force");
		  SEND_STRING(SS_TAP(X_ENTER));
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
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		RGB_MOD,    CYCLEDIAL,
		LT(1, KC_4), ALT_TAB),

	[1] = LAYOUT(
		RESET, REBOOT, 
		KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

};


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
	if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}

}