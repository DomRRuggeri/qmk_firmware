#include "kb.h"

enum custom_keycodes {
  REBOOT = SAFE_RANGE,
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
  }
  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = KEYMAP(
		REBOOT,        LGUI(KC_L),
		LT(1, KC_4), KC_3),

	[1] = KEYMAP(
		RESET, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS)

};


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
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