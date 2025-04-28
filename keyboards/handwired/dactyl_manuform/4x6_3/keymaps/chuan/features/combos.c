#include "combos.h"
#include "quantum.h"
#include "layers.h"
#include "keycodes.h"

static void handle_jk_combo(bool pressed, uint32_t last_combo_pressed) {
    if (pressed) {
        add_mods(MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_LEFT_CTRL));
        send_keyboard_report();
    } else {
        del_mods(MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_LEFT_CTRL));
        if (((int32_t)TIMER_DIFF_32(timer_read32(), last_combo_pressed)) < COMBO_TAP_TERM) {
            tap_code16(KC_LPRN);
        } else {
            send_keyboard_report();
        }
    }
}

static void handle_kl_combo(bool pressed, uint32_t last_combo_pressed) {
    if (pressed) {
        add_mods(MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_LEFT_ALT));
        send_keyboard_report();
    } else {
        del_mods(MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_LEFT_ALT));
        if (((int32_t)TIMER_DIFF_32(timer_read32(), last_combo_pressed)) < COMBO_TAP_TERM) {
            tap_code16(KC_RPRN);
        } else {
            send_keyboard_report();
        }
    }
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode,
                          keyrecord_t *record) {
    if (get_highest_layer(layer_state) == _GAMING) {
        return false;
    }

    return true;
}

static uint32_t last_combo_pressed = 0;

// https://github.com/stasmarkin/sm_voyager_keymap/blob/cf9dd93dcab8d8069c005abb973441f5b6c7609d/sm/sm_voyager_combo.h#L524*/
// This is copied from the above link t work with sm_td
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case JK_LPRN:
            handle_jk_combo(pressed, last_combo_pressed);
            break;
        case KL_RPRN:
            handle_kl_combo(pressed, last_combo_pressed);
            break;
    }

    if (pressed) {
        last_combo_pressed = timer_read32();
    }
}

#ifdef COMBO_TERM_PER_COMBO
uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    // decide by combo->keycode
    // switch (combo->keycode) {
    //     case KC_X:
    //         return 50;
    // }
    //
    // NOTE: the smaller the harder
    switch (combo_index) {
        case QW_CAPWORD:
            return 300;
        case WE_LT:
            return 60;
        case ER_GT:
            return 40;
        case ZX_LEADER:
            return 300;
        case DOTSLSH_DEL:
            return 300;
    }

    // And if you're feeling adventurous, you can even decide by the keys in the chord,
    // i.e. the exact array of keys you defined for the combo.
    // This can be useful if your combos have a common key and you want to apply the
    // same combo term for all of them.
    // if (combo->keys[0] == KC_ENT) { // if first key in the array is Enter
    //     return 150;
    // }

    return COMBO_TERM;
}
#endif
