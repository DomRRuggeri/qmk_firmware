# Build Options
MCU = STM32F303
BOARD = QMK_PROTON_C
#
#DEFAULT_FOLDER = dahmo\beezenbach70
#BOOTMAGIC_ENABLE = yes # Virtual DIP switch configuration
BOOTMAGIC_ENABLE = lite
MOUSEKEY_ENABLE = yes  # Mouse keys
EXTRAKEY_ENABLE = yes  # Audio control and System control
CONSOLE_ENABLE = no    # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = no      # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no
#TAP_DANCE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
ENCODER_ENABLE = yes
OLED_DRIVER_ENABLE = yes
OLED_TIMEOUT = 0