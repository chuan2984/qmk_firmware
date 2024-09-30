/*
  Copyright (c) 2020 Fred Silberberg

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include QMK_KEYBOARD_H

// layer declarations
enum custom_layers {
    _CHUAN = 0,
    _SYMBOL = 1,
    _EXTEND = 2,
    _GAMING = 3,
};

enum custom_keycodes {
    INV_1P = SAFE_RANGE,
    DB_COLN,
    PARENT_DIR,
    SMTD_KEYCODES_BEGIN,
    CKC_A, // reads as C(ustom) + KC_A, but you may give any name here
    CKC_S,
    CKC_D,
    CKC_F,
    CKC_J,
    CKC_K,
    CKC_L,
    CKC_SCLN,
    SMTD_KEYCODES_END,
};

// needs to be after custom_keycode declariation according to sm_td
#include "sm_td.h"

// define keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case INV_1P:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LCTL) SS_TAP(X_X) SS_UP(X_LCTL) SS_UP(X_LSFT));
            }
            return false;
        case DB_COLN:
            if (record->event.pressed) {
                SEND_STRING("::");
            }
            return false;
        case PARENT_DIR:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            return false;
        default:
            return true;
    }
};

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(CKC_A, KC_A, KC_LEFT_GUI)
        SMTD_MT(CKC_S, KC_S, KC_LEFT_ALT)
        SMTD_MT(CKC_D, KC_D, KC_LSFT)
        SMTD_MT(CKC_F, KC_F, KC_LEFT_CTRL)
        SMTD_MT(CKC_J, KC_J, KC_RIGHT_CTRL)
        SMTD_MT(CKC_K, KC_K, KC_RIGHT_SHIFT)
        SMTD_MT(CKC_L, KC_L, KC_LEFT_ALT)
        SMTD_MT(CKC_SCLN, KC_SCLN, KC_RIGHT_GUI)
    }
}

uint32_t get_smtd_timeout(uint16_t keycode, smtd_timeout timeout) {
    switch (keycode) {
        case CKC_A:
            if (timeout == SMTD_TIMEOUT_TAP) return 250;
        case CKC_L:
            if (timeout == SMTD_TIMEOUT_TAP) return 250;
    }

    return get_smtd_timeout_default(timeout);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_CHUAN] = LAYOUT_5x6_5(
        INV_1P,      KC_1,      KC_2,        KC_3,          KC_4,          KC_5,                                                                         KC_6,        KC_7,      KC_8,         KC_9,       KC_0,        TT(_GAMING),
        KC_TAB,      KC_Q,      KC_W,        KC_E,          KC_R,          KC_T,                                                                         KC_Y,        KC_U,      KC_I,         KC_O,       KC_P,        KC_UNDS,
        KC_ESC,      CKC_A,     CKC_S,       CKC_D,         CKC_F,         KC_G,                                                                         KC_H,        CKC_J,     CKC_K,        CKC_L,      CKC_SCLN,    KC_QUOT,
        KC_LSFT,     KC_Z,      KC_X,        KC_C,          KC_V,          KC_B,                                                                         KC_N,        KC_M,      KC_COMM,      KC_DOT,     KC_SLSH,     KC_RSFT,
                                KC_LBRC,     KC_RBRC,                      KC_BSPC,     KC_LCTL,       TT(_EXTEND),       TT(_EXTEND),    KC_LGUI,       KC_SPC,                 KC_EQL,       KC_DEL,
                                                                                        KC_LALT,       TT(_SYMBOL),       TT(_SYMBOL),    KC_ENT
    ),

    [_SYMBOL] = LAYOUT_5x6_5(
        KC_TRNS,    KC_F1,      KC_F2,        KC_F3,        KC_F4,         KC_F5,                                                                        KC_F6,      KC_F7,      KC_F8,        KC_F9,      KC_F10,      KC_TRNS,
        KC_TRNS,    KC_QUOT,    KC_LT,        KC_GT,        KC_DQUO,       KC_HASH,                                                                      KC_AMPR,    DB_COLN,    KC_LBRC,      KC_RBRC,    KC_PERC,     KC_TRNS,
        KC_TRNS,    KC_EXLM,    KC_MINS,      KC_PLUS,      KC_EQL,        KC_GRV,                                                                       KC_PIPE,    KC_COLN,    KC_LPRN,      KC_RPRN,    KC_QUES,     KC_TRNS,
        KC_TRNS,    KC_CIRC,    KC_SLSH,      KC_ASTR,      KC_BSLS,       PARENT_DIR,                                                                   KC_TILD,    KC_DLR,     KC_LCBR,      KC_RCBR,    KC_AT,       KC_TRNS,
                                KC_PGUP,      KC_PGDN,                     KC_TRNS,     KC_TRNS,        KC_TRNS,         KC_TRNS,        KC_TRNS,        KC_TRNS,                KC_HOME,      KC_END,
                                                                                        KC_TRNS,        KC_TRNS,         KC_TRNS,        KC_TRNS
    ),

    [_EXTEND] = LAYOUT_5x6_5(
        KC_TRNS,    KC_NO,      KC_NO,        KC_NO,        KC_NO,         KC_NO,                                                                        KC_NO,      KC_NO,      KC_BRIU,      KC_MPLY,    KC_VOLU,     KC_NO,
        KC_TRNS,    KC_NO,      KC_P7,        KC_P8,        KC_P9,         KC_NO,                                                                        KC_NO,      KC_NO,      KC_BRID,      KC_MSTP,    KC_VOLD,     KC_NO,
        KC_TRNS,    KC_NO,      KC_P4,        KC_P5,        KC_P6,         KC_NO,                                                                        KC_LEFT,    KC_DOWN,    KC_UP,        KC_RGHT,    KC_NO,       KC_NO,
        KC_TRNS,    KC_NO,      KC_P1,        KC_P2,        KC_P3,         KC_NO,                                                                        KC_NO,      KC_NO,      KC_MS_L,      KC_MS_R,    KC_NO,       KC_NO,
                                KC_P0,        KC_PDOT,                     KC_TRNS,    KC_TRNS,        KC_TRNS,         KC_TRNS,        KC_TRNS,         KC_TRNS,                KC_NO,        KC_NO,
                                                                                       KC_TRNS,        KC_TRNS,         KC_TRNS,        KC_TRNS
    ),

    [_GAMING] = LAYOUT_5x6_5(
        INV_1P,      KC_1,      KC_2,        KC_3,          KC_4,          KC_5,                                                                         KC_6,        KC_7,      KC_8,         KC_9,       KC_0,        TT(_GAMING),
        KC_TAB,      KC_Q,      KC_W,        KC_E,          KC_R,          KC_T,                                                                         KC_Y,        KC_U,      KC_I,         KC_O,       KC_P,        KC_UNDS,
        KC_ESC,      KC_A,      KC_S,        KC_D,          KC_F,          KC_G,                                                                         KC_H,        KC_J,      KC_K,         KC_L,       KC_SCLN,     KC_QUOT,
        KC_LSFT,     KC_Z,      KC_X,        KC_C,          KC_V,          KC_B,                                                                         KC_N,        KC_M,      KC_COMM,      KC_DOT,     KC_SLSH,     KC_RSFT,
                                KC_LBRC,     KC_RBRC,                      KC_BSPC,     KC_LCTL,       TT(_EXTEND),       TT(_EXTEND),    KC_LGUI,       KC_SPC,                 KC_EQL,       KC_DEL,
                                                                                        KC_LALT,       TT(_SYMBOL),       TT(_SYMBOL),    KC_ENT
    ),
};

// RGB Modes
// 1 = Static
// 2-5 = Breathing
// 6-8 = Rainbow
// 9-14 = Swirl
// 15-20 = Snake
// 21-24 = Nightrider
// 25 = Christmas
// 26-30 = Static Gradient

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

// Light LEDs 1 through 8 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_LUNA}
);

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_LUNA},
    {3, 4, HSV_ORANGE},
    {7, 3, HSV_LUNA},
    {10, 3, HSV_LUNA},
    {13, 4, HSV_ORANGE},
    {17, 3, HSV_LUNA}
);

const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_LUNA},
    {3, 4, HSV_CHARTREUSE},
    {7, 3, HSV_LUNA},
    {10, 3, HSV_LUNA},
    {13, 4, HSV_CHARTREUSE},
    {17, 3, HSV_LUNA}
);

const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_LUNA},
    {3, 4, HSV_RED},
    {7, 3, HSV_LUNA},
    {10, 3, HSV_LUNA},
    {13, 4, HSV_RED},
    {17, 3, HSV_LUNA}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _CHUAN));
    rgblight_set_layer_state(1, layer_state_cmp(state, _SYMBOL));
    rgblight_set_layer_state(2, layer_state_cmp(state, _EXTEND));
    rgblight_set_layer_state(3, layer_state_cmp(state, _GAMING));
    return state;
}
