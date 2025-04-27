#pragma once

// The serial pin is defined on the root level, can only be set to 5 pins
#define USE_SERIAL
#define EE_HANDS

// two taps to toggle a layer on with TT
#define TAPPING_TOGGLE 2
#define ONESHOT_TAP_TOGGLE 3

#define TAPPING_TERM 180
#define QUICK_TAP_TERM 0

// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define CTL_F LCTL_T(KC_F)

// Right-hand home row mods
#define CTL_J RCTL_T(KC_J)
#define SFT_K RSFT_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

// Vim related
#define BETTER_VISUAL_MODE
#define VIM_I_TEXT_OBJECTS
#define VIM_A_TEXT_OBJECTS
#define VIM_G_MOTIONS
#define VIM_COLON_CMDS
#define VIM_PASTE_BEFORE
#define VIM_REPLACE
#define VIM_DOT_REPEAT
#define VIM_W_BEGINNING_OF_WORD
#define VIM_NUMBERED_JUMPS
#define ONESHOT_VIM
#define VIM_FOR_MAC
