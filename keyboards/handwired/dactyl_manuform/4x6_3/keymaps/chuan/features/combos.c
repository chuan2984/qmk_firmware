#include "combos.h"
#include "layers.h"
#include "keycodes.h"

static void handle_jk_combo(bool pressed, uint32_t last_combo_pressed) {
    if (pressed) {
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
}

static void handle_kl_combo(bool pressed, uint32_t last_combo_pressed) {
    if (pressed) {
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
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if(get_highest_layer(layer_state) == _CHUAN) {
        return true;
    }

    return false;
}

static uint32_t last_combo_pressed = 0;

// https://github.com/stasmarkin/sm_voyager_keymap/blob/cf9dd93dcab8d8069c005abb973441f5b6c7609d/sm/sm_voyager_combo.h#L524*/
// This is copied from the above link t work with sm_td
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
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
