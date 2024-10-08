# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#
BOOTMAGIC_ENABLE = no               # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no                # Mouse keys
EXTRAKEY_ENABLE = no                # Audio control and System control
CONSOLE_ENABLE = no                 # Console for debug
COMMAND_ENABLE = no                 # Commands for debug and configuration
NKRO_ENABLE = yes                   # Enable N-Key Rollover
BACKLIGHT_ENABLE = no               # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes               # Enable keyboard RGB underglow
AUDIO_ENABLE = no                   # Audio output
SPLIT_KEYBOARD = yes
CAPS_WORD_ENABLE = yes              # Enable Caps Word
COMBO_ENABLE = yes                  # Enable combo/chording
REPEAT_KEY_ENABLE = yes             # Enable repeat and reverse repeat
EXTRAFLAGS += -flto

DEFERRED_EXEC_ENABLE = yes          # Custom Tap Dance https://github.com/stasmarkin/sm_td
