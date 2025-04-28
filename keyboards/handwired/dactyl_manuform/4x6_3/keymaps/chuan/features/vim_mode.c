#include "vim_mode.h"
#include "qmk-vim/src/vim.h"
#include "layers.h"
#include "keycodes.h"
#include "quantum.h"

static uint8_t current_vim_layer = _NULL;

static void set_rgb_layer(uint8_t layer) {
    if (layer == current_vim_layer) return;

    rgblight_set_layer_state(_VIM_INSERT, false);
    rgblight_set_layer_state(_VIM_NORM, false);
    rgblight_set_layer_state(_VIM_VISUAL, false);
    rgblight_set_layer_state(_VIM_VISUAL_LINE, false);

    if (layer != _NULL) {
        rgblight_set_layer_state(layer, true);
    }
    current_vim_layer = layer;
}

// TODO: fix while vim-mode is on, the other layer lights dont come thru
void set_vim_rgb_layer(uint8_t layer) {
    if (!vim_mode_enabled()) {
        set_rgb_layer(layer);
    }
}

void process_vim_activation(const keyrecord_t *record) {
    if (record->event.pressed) {
        toggle_vim_mode();
        set_vim_rgb_layer(_NULL);
    }
}

void insert_mode_user(void) {
    set_rgb_layer(_VIM_INSERT);
}

void normal_mode_user(void) {
    set_rgb_layer(_VIM_NORM);
}

void visual_mode_user(void) {
    set_rgb_layer(_VIM_VISUAL);
}

void visual_line_mode_user(void) {
    set_rgb_layer(_VIM_VISUAL_LINE);
}
