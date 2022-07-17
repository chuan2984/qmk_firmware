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
    _LUNA = 0,
    _CHUAN = 1,
    _SYMBOL = 2,
  _NUMBER = 3,
};uu

// define song
#ifdef AUDIO_ENABLE
float tone_zelda[][2] = SONG(ZELDA_TREASURE);
#endif

enum custom_keycodes {
  INV_1P = SAFE_RANGE, 
};

// define keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case INV_1P:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LCTL) SS_TAP(X_X) SS_UP(X_LCTL) SS_UP(X_LSFT) SS_DELAY(500) "secret" SS_DELAY(100) SS_TAP(X_ENT));
      }
      return false;
    default:
      return true;
  }
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_LUNA] = LAYOUT_5x6_5(
    KC_GRV,        KC_1,        KC_2,  KC_3,  KC_4,    KC_5,                                                        KC_6,    KC_7,     KC_8,      KC_9,     KC_0,           KC_BSPC,
    KC_TAB,        KC_Q,        KC_W,  KC_E,  KC_R,    KC_T,                                                        KC_Y,    KC_U,     KC_I,      KC_O,     KC_P,           KC_TAB,
    KC_ESC,        KC_A,        KC_S,  KC_D,  KC_F,    KC_G,                                                        KC_H,    KC_J,     KC_K,      KC_L,     KC_QUOT,        KC_ENT,
    KC_LSPO,       KC_Z,        KC_X,  KC_C,  KC_V,    KC_B,                                                        KC_N,    KC_M,     KC_COMM,   KC_DOT,   KC_SLSH,        KC_RSPC,
                                KC_LCTL,      KC_LALT, KC_SPC,  KC_SCLN, KC_EQL,               KC_LEFT,             KC_UP,   KC_RGHT,  KC_RGUI,   KC_RCTL,
                                                                KC_LBRC, LT(_SYMBOL,KC_BSLS),  LT(_NUMBER,KC_MINS), KC_DOWN
  ),
  
  [_CHUAN] = LAYOUT_5x6_5(
    KC_ESC,      KC_1,      KC_2,     KC_3,     KC_4,                KC_5,                                               KC_6,                  KC_7,         KC_8,      KC_9,      KC_0,      KC_PSCR,
    KC_TAB,      KC_Q,      KC_W,     KC_E,     KC_R,                KC_T,                                               KC_Y,                  KC_U,         KC_I,      KC_O,      KC_P,      KC_UNDS,
    TT(_SYMBOL), KC_A,      KC_S,     KC_D,     KC_F,                KC_G,                                               KC_H,                  KC_J,         KC_K,      KC_L,      KC_SCLN,   KC_QUOT,
    KC_LSFT,     KC_Z,      KC_X,     KC_C,     KC_V,                KC_B,                                               KC_N,                  KC_M,         KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSFT,
                            KC_LGUI,  INV_1P,   LT(_SYMBOL,KC_BSPC), LCTL_T(KC_PLUS), KC_HOME, KC_PGUP, RCTL_T(KC_EQL),  LT(_SYMBOL,KC_SPC),  TT(_NUMBER),  KC_DEL,
                                                                     LALT_T(KC_MINS), KC_END,  KC_PGDN, RALT_T(KC_ENT)    
  ),

  [_SYMBOL] = LAYOUT_5x6_5(
    KC_ESC,       KC_F1,      KC_F2,        KC_F3,        KC_F4,      KC_F5,                                                  KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,      KC_NO,
    KC_TAB,       KC_NO,      KC_NO,        KC_NO,        KC_NO,      KC_NO,                                                  KC_ASTR,    KC_HASH,    KC_UP,      KC_CIRC,    KC_DLR,      KC_NO,
    TT(_SYMBOL),  KC_LCBR,    KC_LBRC,      KC_LPRN,      KC_LT,      KC_PIPE,                                                KC_NO,      KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_COLN,     KC_DQUO,
    KC_LSPO,      KC_RCBR,    KC_RBRC,      KC_RPRN,      KC_GT,      KC_AMPR,                                                KC_PERC,    KC_EXLM,    KC_AT,      KC_TILD,    KC_QUES,     KC_RSPC,
                              KC_LGUI,      KC_NO,        KC_BSPC,    KC_LCTL,    KC_HOME,        KC_PGUP,    KC_RCTL,        KC_SPC,     KC_NO,      KC_DEL,
                                                                      KC_LALT,    KC_END,         KC_PGDN,    RALT_T(KC_ENT)
  ),

  [_NUMBER] = LAYOUT_5x6_5(
    TO(_LUNA),    TO(_CHUAN),   KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,                                             KC_TRNS,      KC_NO,      KC_PSLS,   KC_PAST,   KC_PMNS,      KC_NO,
    KC_TRNS,      KC_TRNS,      KC_NO,        KC_NO,        KC_NO,        KC_NO,                                               KC_NO,        KC_7,       KC_8,      KC_9,      KC_PPLS,      KC_NO,
    TT(_NUMBER),  RGB_TOG,      RGB_HUI,      RGB_SAI,      RGB_VAD,      RGB_SPI,                                             KC_PDOT,      KC_4,       KC_5,      KC_6,      KC_PCMM,      KC_NO,
    KC_TRNS,      RGB_MOD,      RGB_HUD,      RGB_SAD,      RGB_VAI,      RGB_SPD,                                             KC_P0,        KC_1,       KC_2,      KC_3,      KC_PEQL,      KC_NO,
                                KC_LGUI,      KC_TRNS,      KC_SPC,       KC_LCTL, KC_HOME,        KC_PGUP,   KC_RCTL,         KC_BSPC,      KC_TRNS,    KC_DEL,
                                                                          KC_LALT, KC_END,         KC_PGDN,   RALT_T(KC_ENT) 
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

// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_AZURE}
);

const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_TEAL}
);

const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_RED}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,    
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer    // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _LUNA));
    rgblight_set_layer_state(1, layer_state_cmp(state, _CHUAN));
    rgblight_set_layer_state(2, layer_state_cmp(state, _SYMBOL));
    rgblight_set_layer_state(3, layer_state_cmp(state, _NUMBER));
    return state;
}