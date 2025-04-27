#include QMK_KEYBOARD_H

#ifndef COMBO_TAP_TERM
#define COMBO_TAP_TERM TAPPING_TERM
#endif

enum custom_layers {
    _CHUAN = 0,
    _SYMBOL = 1,
    _EXTEND = 2,
    _GAMING = 3,
};

enum custom_keycodes {
    C_PBRAC = SAFE_RANGE,
    TOG_VIM
};

static uint8_t current_vim_layer = 255;

void set_vim_rgb_layer(uint8_t layer) {
    if (layer == current_vim_layer) return;

    rgblight_set_layer_state(4, false);
    rgblight_set_layer_state(5, false);
    rgblight_set_layer_state(6, false);
    rgblight_set_layer_state(7, false);

    if (layer != 255) {
        rgblight_set_layer_state(layer, true);
    }
    current_vim_layer = layer;
}

#include "qmk-vim/src/vim.h"
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_vim_mode(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case TOG_VIM:
            if (record->event.pressed) {
                toggle_vim_mode();

                if (!vim_mode_enabled()) {
                    set_vim_rgb_layer(255);
                }
            }
            return false;
        case C_PBRAC:
            if (record->event.pressed) {
                SEND_STRING("{}");
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            }
            return false;
        default:
            return true;
    }
};

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
    ER_GT,
    ZX_TOG_VIM
};

const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM hj_combo[] = {KC_H, CTL_J, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM oi_combo[] = {KC_O, KC_I, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {CTL_J, SFT_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {SFT_K, ALT_L, COMBO_END};
const uint16_t PROGMEM mcomm_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM commdot_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM dotslsh_combo[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM we_lt[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM er_gt[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM zx_tog_vim[] = {KC_Z, KC_X, COMBO_END};

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
    [ER_GT] = COMBO(er_gt, KC_GT),
    [ZX_TOG_VIM] = COMBO(zx_tog_vim, TOG_VIM)
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if(get_highest_layer(layer_state) == _CHUAN) {
        return true;
    }

    return false;
}

static uint8_t mods_before_combo = 0;
static uint32_t last_combo_pressed = 0;

// https://github.com/stasmarkin/sm_voyager_keymap/blob/cf9dd93dcab8d8069c005abb973441f5b6c7609d/sm/sm_voyager_combo.h#L524*/
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
//    ┌─────────┬───────┬───────┬───────┬───────┬──────┐                                               ┌─────┬───────┬───────┬───────┬──────────┬──────────────┐
//    │   no    │   1   │   2   │   3   │   4   │  5   │                                               │  6  │   7   │   8   │   9   │    0     │ OSL(_GAMING) │
//    ├─────────┼───────┼───────┼───────┼───────┼──────┤                                               ├─────┼───────┼───────┼───────┼──────────┼──────────────┤
//    │   tab   │   q   │   w   │   e   │   r   │  t   │                                               │  y  │   u   │   i   │   o   │    p     │      _       │
//    ├─────────┼───────┼───────┼───────┼───────┼──────┤                                               ├─────┼───────┼───────┼───────┼──────────┼──────────────┤
//    │   esc   │ GUI_A │ ALT_S │ SFT_D │ CTL_F │  g   │                                               │  h  │ CTL_J │ SFT_K │ ALT_L │ GUI_SCLN │      '       │
//    ├─────────┼───────┼───────┼───────┼───────┼──────┤                                               ├─────┼───────┼───────┼───────┼──────────┼──────────────┤
//    │ QK_AREP │   z   │   x   │   c   │   v   │  b   │                                               │  n  │   m   │   ,   │   .   │    /     │      :       │
//    └─────────┴───────┼───────┼───────┼───────┼──────┼──────────────┬──────┐   ┌──────┬──────────────┼─────┼───────┼───────┼───────┼──────────┴──────────────┘
//                      │ left  │ rght  │       │ bspc │ OSL(_EXTEND) │ pgup │   │ home │ OSL(_SYMBOL) │ spc │       │  up   │ down  │
//                      └───────┴───────┘       └──────┼──────────────┼──────┤   ├──────┼──────────────┼─────┘       └───────┴───────┘
//                                                     │    QK_REP    │ pgdn │   │ end  │     ent      │
//                                                     └──────────────┴──────┘   └──────┴──────────────┘
[_CHUAN] = LAYOUT_5x6_5(
  KC_NO   , KC_1  , KC_2    , KC_3    , KC_4  , KC_5    ,                                                       KC_6   , KC_7  , KC_8    , KC_9    , KC_0     , OSL(_GAMING),
  KC_TAB  , KC_Q  , KC_W    , KC_E    , KC_R  , KC_T    ,                                                       KC_Y   , KC_U  , KC_I    , KC_O    , KC_P     , KC_UNDS     ,
  KC_ESC  , GUI_A , ALT_S   , SFT_D   , CTL_F , KC_G    ,                                                       KC_H   , CTL_J , SFT_K   , ALT_L   , GUI_SCLN , KC_QUOT     ,
  QK_AREP , KC_Z  , KC_X    , KC_C    , KC_V  , KC_B    ,                                                       KC_N   , KC_M  , KC_COMM , KC_DOT  , KC_SLSH  , KC_COLN     ,
                    KC_LEFT , KC_RGHT ,         KC_BSPC , OSL(_EXTEND) , KC_PGUP ,     KC_HOME , OSL(_SYMBOL) , KC_SPC ,         KC_UP   , KC_DOWN                          ,
                                                          QK_REP       , KC_PGDN ,     KC_END  , KC_ENT
),

//    ┌──────┬─────┬─────┬─────┬─────┬─────┐                            ┌─────┬─────┬─────┬─────┬─────┬─────┐
//    │ caps │     │     │     │     │     │                            │     │     │     │     │     │     │
//    ├──────┼─────┼─────┼─────┼─────┼─────┤                            ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │      │     │     │     │     │     │                            │     │     │     │     │     │     │
//    ├──────┼─────┼─────┼─────┼─────┼─────┤                            ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │      │  a  │  s  │  d  │  f  │     │                            │     │  j  │  k  │  l  │  ;  │     │
//    ├──────┼─────┼─────┼─────┼─────┼─────┤                            ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │ lsft │     │     │     │     │     │                            │     │     │     │     │     │     │
//    └──────┴─────┼─────┼─────┼─────┼─────┼──────┬─────┐   ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┴─────┘
//                 │     │     │     │     │ lctl │     │   │     │     │     │     │     │     │
//                 └─────┴─────┘     └─────┼──────┼─────┤   ├─────┼─────┼─────┘     └─────┴─────┘
//                                         │ lalt │     │   │     │     │
//                                         └──────┴─────┘   └─────┴─────┘
[_GAMING] = LAYOUT_5x6_5(
  KC_CAPS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                                             KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                                             KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_TRNS , KC_A    , KC_S    , KC_D    , KC_F    , KC_TRNS ,                                             KC_TRNS , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_TRNS,
  KC_LSFT , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                                             KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                      KC_TRNS , KC_TRNS ,           KC_TRNS , KC_LCTL , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS , KC_TRNS                    ,
                                                              KC_LALT , KC_TRNS ,     KC_TRNS , KC_TRNS
),

//    ┌─────┬────┬─────┬─────┬────┬─────┐                           ┌─────┬─────────┬─────┬─────┬─────┬─────┐
//    │     │ f1 │ f2  │ f3  │ f4 │ f5  │                           │ f6  │   f7    │ f8  │ f9  │ f10 │     │
//    ├─────┼────┼─────┼─────┼────┼─────┤                           ├─────┼─────────┼─────┼─────┼─────┼─────┤
//    │     │ '  │  <  │  >  │ "  │  #  │                           │  &  │ C_PBRAC │  [  │  ]  │  %  │     │
//    ├─────┼────┼─────┼─────┼────┼─────┤                           ├─────┼─────────┼─────┼─────┼─────┼─────┤
//    │     │ !  │  -  │  +  │ =  │  `  │                           │  |  │    :    │  (  │  )  │  ?  │     │
//    ├─────┼────┼─────┼─────┼────┼─────┤                           ├─────┼─────────┼─────┼─────┼─────┼─────┤
//    │     │ ^  │  /  │  *  │ \  │ no  │                           │  ~  │    $    │  {  │  }  │  @  │     │
//    └─────┴────┼─────┼─────┼────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼─────────┼─────┼─────┼─────┴─────┘
//               │     │     │    │     │     │     │   │     │     │     │         │     │     │
//               └─────┴─────┘    └─────┼─────┼─────┤   ├─────┼─────┼─────┘         └─────┴─────┘
//                                      │     │     │   │     │     │
//                                      └─────┴─────┘   └─────┴─────┘
[_SYMBOL] = LAYOUT_5x6_5(
  KC_TRNS , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                                             KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_TRNS,
  KC_TRNS , KC_QUOT , KC_LT   , KC_GT   , KC_DQUO , KC_HASH ,                                             KC_AMPR , C_PBRAC , KC_LBRC , KC_RBRC , KC_PERC , KC_TRNS,
  KC_TRNS , KC_EXLM , KC_MINS , KC_PLUS , KC_EQL  , KC_GRV  ,                                             KC_PIPE , KC_COLN , KC_LPRN , KC_RPRN , KC_QUES , KC_TRNS,
  KC_TRNS , KC_CIRC , KC_SLSH , KC_ASTR , KC_BSLS , KC_NO   ,                                             KC_TILD , KC_DLR  , KC_LCBR , KC_RCBR , KC_AT   , KC_TRNS,
                      KC_TRNS , KC_TRNS ,           KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS , KC_TRNS                    ,
                                                              KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS
),

//    ┌─────┬──────┬──────┬─────────┬──────┬─────┐                           ┌─────┬──────┬──────┬──────┬──────┬─────┐
//    │     │      │      │         │      │     │                           │     │      │      │      │      │     │
//    ├─────┼──────┼──────┼─────────┼──────┼─────┤                           ├─────┼──────┼──────┼──────┼──────┼─────┤
//    │     │      │      │         │      │     │                           │     │      │      │      │      │     │
//    ├─────┼──────┼──────┼─────────┼──────┼─────┤                           ├─────┼──────┼──────┼──────┼──────┼─────┤
//    │     │ kp_6 │ kp_4 │  kp_0   │ kp_2 │     │                           │     │ kp_3 │ kp_1 │ kp_5 │ kp_7 │     │
//    ├─────┼──────┼──────┼─────────┼──────┼─────┤                           ├─────┼──────┼──────┼──────┼──────┼─────┤
//    │     │      │      │ LSFT(g) │ kp_8 │     │                           │     │ kp_9 │      │      │      │     │
//    └─────┴──────┼──────┼─────────┼──────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼──────┼──────┼──────┼──────┴─────┘
//                 │      │         │      │     │     │     │   │     │     │     │      │      │      │
//                 └──────┴─────────┘      └─────┼─────┼─────┤   ├─────┼─────┼─────┘      └──────┴──────┘
//                                               │     │     │   │     │     │
//                                               └─────┴─────┘   └─────┴─────┘
[_EXTEND] = LAYOUT_5x6_5(
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS    , KC_TRNS , KC_TRNS ,                                             KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS    , KC_TRNS , KC_TRNS ,                                             KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_TRNS , KC_P6   , KC_P4   , KC_P0      , KC_P2   , KC_TRNS ,                                             KC_TRNS , KC_P3   , KC_P1   , KC_P5   , KC_P7   , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS , LSFT(KC_G) , KC_P8   , KC_TRNS ,                                             KC_TRNS , KC_P9   , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                      KC_TRNS , KC_TRNS    ,           KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS , KC_TRNS                    ,
                                                                 KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS
)
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
    {0, 20, HSV_RED}
);

const rgblight_segment_t PROGMEM symbol_2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM extend_3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM vim_insert_4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_CYAN}
);

const rgblight_segment_t PROGMEM vim_normal_5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_BLUE}
);

const rgblight_segment_t PROGMEM vim_visual_6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_PINK}
);

const rgblight_segment_t PROGMEM vim_visual_line_7_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_PURPLE}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    base_0_layer,
    gaming_1_layer,
    symbol_2_layer,
    extend_3_layer,
    vim_insert_4_layer,
    vim_normal_5_layer,
    vim_visual_6_layer,
    vim_visual_line_7_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

void insert_mode_user(void) {
  set_vim_rgb_layer(4);
}

void normal_mode_user(void) {
  set_vim_rgb_layer(5);
}

void visual_mode_user(void) {
  set_vim_rgb_layer(6);
}

void visual_line_mode_user(void) {
  set_vim_rgb_layer(7);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _CHUAN));
    rgblight_set_layer_state(1, layer_state_cmp(state, _GAMING));
    rgblight_set_layer_state(2, layer_state_cmp(state, _SYMBOL));
    rgblight_set_layer_state(3, layer_state_cmp(state, _EXTEND));

    // TODO: while vim-mode is on, the other layer lights dont come thru
    if (!vim_mode_enabled()) {
        set_vim_rgb_layer(255);
    }

    return state;
}
