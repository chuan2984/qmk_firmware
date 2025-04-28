#include "config.h"
#include "quantum.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_D:
            return TAPPING_TERM - 20;
        case SFT_K:
            return TAPPING_TERM - 20;
        default:
            return TAPPING_TERM;
    }
}
