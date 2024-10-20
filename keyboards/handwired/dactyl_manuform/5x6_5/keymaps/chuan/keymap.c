#include QMK_KEYBOARD_H

#ifndef COMBO_TAP_TERM
#define COMBO_TAP_TERM TAPPING_TERM
#endif

#define TWO_KEY_WINDOW 700

enum custom_layers {
    _CHUAN = 0,
    _SYMBOL = 1,
    _EXTEND = 2,
    _GAMING = 3,
};

enum custom_keycodes {
    C_PBRAC = SAFE_RANGE,
    C_RBRC_M,
    C_RBRC_F,
    C_RBRC_B,
    C_RBRC_Q,
    C_RBRC_I,
    C_RBRC_H,
    C_LBRC_M,
    C_LBRC_F,
    C_LBRC_B,
    C_LBRC_Q,
    C_LBRC_I,
    C_LBRC_H,
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

// needs to be after custom_keycode declaration according to sm_td
#include "sm_td.h"

static uint16_t last_two_keys[2] = {KC_NO, KC_NO};
static uint32_t last_keypress_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }

    // this may not work with smtd mod keys as this would be skipped
    // not worrying about it right now since the mods will not be used
    // in the 2 key repeat combos
    // TODO: keep the last 2 keys around if no other keys have been pressed
    if (record->event.pressed) {
        uint32_t time_elapsed = timer_elapsed32(last_keypress_timer);
        if (time_elapsed < TWO_KEY_WINDOW) {
            last_two_keys[1] = last_two_keys[0];
            last_two_keys[0] = keycode;
        } else {
            // If not, start a new potential combo
            last_two_keys[1] = KC_NO;
            last_two_keys[0] = keycode;
        }
        last_keypress_timer = timer_read32();
    }

    switch (keycode) {
        case C_PBRAC:
            if (record->event.pressed) {
                SEND_STRING("{}");
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            }
            return false;
        case C_RBRC_M:
            if (record->event.pressed) {
                SEND_STRING("]m");
            }
            return false;
        case C_RBRC_F:
            if (record->event.pressed) {
                SEND_STRING("]f");
            }
            return false;
        case C_RBRC_B:
            uprintf("in rbrc_b");
            if (record->event.pressed) {
                SEND_STRING("]b");
            }
            return false;
        case C_RBRC_Q:
            if (record->event.pressed) {
                SEND_STRING("]q");
            }
            return false;
        case C_RBRC_I:
            if (record->event.pressed) {
                SEND_STRING("[i");
            }
            return false;
        case C_RBRC_H:
            if (record->event.pressed) {
                SEND_STRING("[h");
            }
            return false;
        case C_LBRC_M:
            if (record->event.pressed) {
                SEND_STRING("[m");
            }
            return false;
        case C_LBRC_F:
            if (record->event.pressed) {
                SEND_STRING("[f");
            }
            return false;
        case C_LBRC_B:
            uprintf("in lbrc_b");
            if (record->event.pressed) {
                SEND_STRING("[b");
            }
            return false;
        case C_LBRC_Q:
            if (record->event.pressed) {
                SEND_STRING("[q");
            }
            return false;
        case C_LBRC_I:
            if (record->event.pressed) {
                SEND_STRING("[i");
            }
            return false;
        case C_LBRC_H:
            if (record->event.pressed) {
                SEND_STRING("]h");
            }
            return false;
        default:
            return true;
    }
};

typedef struct {
    uint16_t prev;
    uint16_t curr;
    uint16_t alt;
} repeat_key_table_t;

const repeat_key_table_t repeat_key_table[] = {
    { KC_LBRC, KC_M, C_RBRC_M },
    { KC_LBRC, KC_F, C_RBRC_F },
    { KC_LBRC, KC_B, C_RBRC_B },
    { KC_LBRC, KC_Q, C_RBRC_Q },
    { KC_LBRC, KC_I, C_RBRC_I },
    { KC_LBRC, KC_H, C_RBRC_H },
    { KC_RBRC, KC_M, C_LBRC_M },
    { KC_RBRC, KC_F, C_LBRC_F },
    { KC_RBRC, KC_B, C_LBRC_B },
    { KC_RBRC, KC_Q, C_LBRC_Q },
    { KC_RBRC, KC_I, C_LBRC_I },
    { KC_RBRC, KC_H, C_LBRC_H },
};

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    if ((mods & MOD_MASK_CTRL)) {
        switch (keycode) {
            case KC_R: return KC_U;
        }
    }

    if (last_two_keys[1] != KC_NO) {
        for (int i = 0; i < sizeof(repeat_key_table) / sizeof(repeat_key_table_t); i++) {
            if (last_two_keys[0] == repeat_key_table[i].curr && last_two_keys[1] == repeat_key_table[i].prev) {
                return repeat_key_table[i].alt;
            }
        }
    }

    switch (keycode) {
        case KC_U: return C(KC_R);
        case KC_SCLN: return KC_COMM;
        case KC_COMM: return KC_SCLN;
        case KC_ASTR: return KC_HASH;
        case KC_HASH: return KC_ASTR;
        case KC_DLR: return KC_CIRC;
        case KC_CIRC: return KC_DLR;
    }

    return KC_TRNS;  // Defer to default definitions.
}

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
            if (timeout == SMTD_TIMEOUT_TAP) return 280;
            if (timeout == SMTD_TIMEOUT_RELEASE) return 25;
        case CKC_L:
            if (timeout == SMTD_TIMEOUT_TAP) return 280;
            if (timeout == SMTD_TIMEOUT_RELEASE) return 30;
    }

    return get_smtd_timeout_default(timeout);
}

enum combos {
    QW_CAPWORD,
    HJ_EQL,
    UI_LBRC,
    OI_RBRC,
    JK_LPRN,
    KL_RPRN,
    MCOMM_LCBR,
    COMMDOT_RCBR,
    NM_DLR,
    DOTSLSH_DEL,
    WE_LT,
    ER_GT
};

const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM hj_combo[] = {KC_H, CKC_J, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM oi_combo[] = {KC_O, KC_I, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {CKC_J, CKC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {CKC_K, CKC_L, COMBO_END};
const uint16_t PROGMEM mcomm_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM commdot_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM dotslsh_combo[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM we_lt[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM er_gt[] = {KC_E, KC_R, COMBO_END};

combo_t key_combos[] = {
    [QW_CAPWORD] = COMBO(qw_combo, CW_TOGG),
    [HJ_EQL] = COMBO(hj_combo, KC_EQL),
    [UI_LBRC] = COMBO(ui_combo, KC_LBRC),
    [OI_RBRC] = COMBO(oi_combo, KC_RBRC),
    [JK_LPRN] = COMBO_ACTION(jk_combo),
    [KL_RPRN] = COMBO_ACTION(kl_combo),
    [MCOMM_LCBR] = COMBO(mcomm_combo, KC_LCBR),
    [COMMDOT_RCBR] = COMBO(commdot_combo, KC_RCBR),
    [NM_DLR] = COMBO(nm_combo, KC_DLR),
    [DOTSLSH_DEL] = COMBO(dotslsh_combo, KC_DEL),
    [WE_LT] = COMBO(we_lt, KC_LT),
    [ER_GT] = COMBO(er_gt, KC_GT)
};

static uint8_t mods_before_combo = 0;
static uint32_t last_combo_pressed = 0;
// https://github.com/stasmarkin/sm_voyager_keymap/blob/cf9dd93dcab8d8069c005abb973441f5b6c7609d/sm/sm_voyager_combo.h#L524
// This is copied from the above link t work with sm_td
void process_combo_event(uint16_t combo_index, bool pressed) {
    if (pressed) {
        mods_before_combo = get_mods();
    }

    switch(combo_index) {
        // send keycode for ( when tapped
        // otherwise add left shift and alt as if they were held
        case JK_LPRN:
            if (pressed) {
                mods_before_combo = timer_read32();
                add_mods(MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_LEFT_CTRL));
                send_keyboard_report();
            } else {
                del_mods(MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_LEFT_CTRL));
                if (((int32_t) TIMER_DIFF_32(timer_read32(), last_combo_pressed)) < COMBO_TAP_TERM) {
                    tap_code16(KC_LPRN);
                } else {
                    send_keyboard_report();
                }
            }
            break;
        // send keycode for ) when tapped
        // otherwise add left shift and alt as if they were held
        case KL_RPRN:
            if (pressed) {
                mods_before_combo = timer_read32();
                add_mods(MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_LEFT_ALT));
                send_keyboard_report();
            } else {
                del_mods(MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_LEFT_ALT));
                if (((int32_t) TIMER_DIFF_32(timer_read32(), last_combo_pressed)) < COMBO_TAP_TERM) {
                    tap_code16(KC_RPRN);
                } else {
                    send_keyboard_report();
                }
            }
            break;
    }
    if (pressed) {
        last_combo_pressed = timer_read32();
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_CHUAN] = LAYOUT_5x6_5(
        KC_NO,       KC_1,      KC_2,        KC_3,          KC_4,          KC_5,                                                                         KC_6,        KC_7,      KC_8,         KC_9,       KC_0,        OSL(_GAMING),
        KC_TAB,      KC_Q,      KC_W,        KC_E,          KC_R,          KC_T,                                                                         KC_Y,        KC_U,      KC_I,         KC_O,       KC_P,        KC_UNDS,
        KC_ESC,      CKC_A,     CKC_S,       CKC_D,         CKC_F,         KC_G,                                                                         KC_H,        CKC_J,     CKC_K,        CKC_L,      CKC_SCLN,    KC_QUOT,
        QK_AREP,     KC_Z,      KC_X,        KC_C,          KC_V,          KC_B,                                                                         KC_N,        KC_M,      KC_COMM,      KC_DOT,     KC_SLSH,     KC_COLN,
                                KC_LEFT,     KC_RGHT,                      KC_BSPC,     OSL(_EXTEND),   KC_PGUP,        KC_HOME,     OSL(_SYMBOL),       KC_SPC,                 KC_UP,        KC_DOWN,
                                                                                        QK_REP,         KC_PGDN,        KC_END,      KC_ENT
    ),

    [_GAMING] = LAYOUT_5x6_5(
        KC_CAPS,     KC_TRNS,   KC_TRNS,     KC_TRNS,       KC_TRNS,       KC_TRNS,                                                                      KC_TRNS,     KC_TRNS,   KC_TRNS,      KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,     KC_TRNS,   KC_TRNS,     KC_TRNS,       KC_TRNS,       KC_TRNS,                                                                      KC_TRNS,     KC_TRNS,   KC_TRNS,      KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,     KC_A,      KC_S,        KC_D,          KC_F,          KC_TRNS,                                                                      KC_TRNS,     KC_J,      KC_K,         KC_L,       KC_SCLN,     KC_TRNS,
        KC_LSFT,     KC_TRNS,   KC_TRNS,     KC_TRNS,       KC_TRNS,       KC_TRNS,                                                                      KC_TRNS,     KC_TRNS,   KC_TRNS,      KC_TRNS,    KC_TRNS,     KC_TRNS,
                                KC_TRNS,     KC_TRNS,                      KC_TRNS,     KC_LCTL,       KC_TRNS,         KC_TRNS,        KC_TRNS,         KC_TRNS,                KC_TRNS,      KC_TRNS,
                                                                                        KC_LALT,       KC_TRNS,         KC_TRNS,        KC_TRNS
    ),

    [_SYMBOL] = LAYOUT_5x6_5(
        KC_TRNS,    KC_F1,      KC_F2,        KC_F3,        KC_F4,         KC_F5,                                                                        KC_F6,      KC_F7,      KC_F8,        KC_F9,      KC_F10,      KC_TRNS,
        KC_TRNS,    KC_QUOT,    KC_LT,        KC_GT,        KC_DQUO,       KC_HASH,                                                                      KC_AMPR,    C_PBRAC,    KC_LBRC,      KC_RBRC,    KC_PERC,     KC_TRNS,
        KC_TRNS,    KC_EXLM,    KC_MINS,      KC_PLUS,      KC_EQL,        KC_GRV,                                                                       KC_PIPE,    KC_COLN,    KC_LPRN,      KC_RPRN,    KC_QUES,     KC_TRNS,
        KC_TRNS,    KC_CIRC,    KC_SLSH,      KC_ASTR,      KC_BSLS,       KC_NO,                                                                        KC_TILD,    KC_DLR,     KC_LCBR,      KC_RCBR,    KC_AT,       KC_TRNS,
                                KC_TRNS,      KC_TRNS,                     KC_TRNS,     KC_TRNS,        KC_TRNS,         KC_TRNS,        KC_TRNS,        KC_TRNS,                KC_TRNS,      KC_TRNS,
                                                                                        KC_TRNS,        KC_TRNS,         KC_TRNS,        KC_TRNS
    ),

    [_EXTEND] = LAYOUT_5x6_5(
        KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,      KC_TRNS,       KC_TRNS,                                                                      KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,      KC_TRNS,       KC_TRNS,                                                                      KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,    KC_P6,      KC_P4,        KC_P0,        KC_P2,         KC_TRNS,                                                                      KC_TRNS,    KC_P3,      KC_P1,        KC_P5,      KC_P7,       KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,      LSFT(KC_G),   KC_P8,         KC_TRNS,                                                                      KC_TRNS,    KC_P9,      KC_TRNS,      KC_TRNS,    KC_TRNS,     KC_TRNS,
                                KC_TRNS,      KC_TRNS,                     KC_TRNS,    KC_TRNS,        KC_TRNS,         KC_TRNS,        KC_TRNS,         KC_TRNS,                KC_TRNS,      KC_TRNS,
                                                                                       KC_TRNS,        KC_TRNS,         KC_TRNS,        KC_TRNS
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
const rgblight_segment_t PROGMEM base_0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_LUNA}
);

const rgblight_segment_t PROGMEM gaming_1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_LUNA},
    {3, 4, HSV_RED},
    {7, 3, HSV_LUNA},
    {10, 3, HSV_LUNA},
    {13, 4, HSV_RED},
    {17, 3, HSV_LUNA}
);

const rgblight_segment_t PROGMEM symbol_2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_LUNA},
    {3, 4, HSV_ORANGE},
    {7, 3, HSV_LUNA},
    {10, 3, HSV_LUNA},
    {13, 4, HSV_ORANGE},
    {17, 3, HSV_LUNA}
);

const rgblight_segment_t PROGMEM extend_3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_LUNA},
    {3, 4, HSV_CHARTREUSE},
    {7, 3, HSV_LUNA},
    {10, 3, HSV_LUNA},
    {13, 4, HSV_CHARTREUSE},
    {17, 3, HSV_LUNA}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    base_0_layer,
    gaming_1_layer,
    symbol_2_layer,
    extend_3_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _CHUAN));
    rgblight_set_layer_state(1, layer_state_cmp(state, _GAMING));
    rgblight_set_layer_state(2, layer_state_cmp(state, _SYMBOL));
    rgblight_set_layer_state(3, layer_state_cmp(state, _EXTEND));
    return state;
}
