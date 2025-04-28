#include "features/leader.h"
#include "quantum.h"
#include "layers.h"

// https://github.com/andrewjrae/kyria-keymap#userspace-leader-sequences
void *leader_toggles_func(uint16_t keycode) {
    switch (keycode) {
        case KC_N:
            layer_invert(_NUMBER);
            return NULL;
        case KC_S:
            layer_invert(_SYMBOL);
            return NULL;
        case KC_G:
            layer_invert(_GAMING);
            return NULL;
        default:
            return NULL;
    }
}

void *leader_start_func(uint16_t keycode) {
    switch (keycode) {
        case KC_T:
            return leader_toggles_func;
        default:
            return NULL;
    }
}
