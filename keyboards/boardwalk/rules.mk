# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
AUDIO_ENABLE = no           # Audio output
AUTO_SHIFT_ENABLE = yes
BACKLIGHT_ENABLE = no # Enable keyboard backlight functionality
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
COMMAND_ENABLE = yes        # Commands for debug and configuration
CONSOLE_ENABLE = no         # Console for debug
EXTRAKEY_ENABLE = yes       # Audio control and System control
LAYOUTS = ortho_5x14
MOUSEKEY_ENABLE = yes        # Mouse keys
NKRO_ENABLE = yes           # Enable N-Key Rollover
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
TAP_DANCE_ENABLE = yes
UNICODE_ENABLE = yes        # Unicode
