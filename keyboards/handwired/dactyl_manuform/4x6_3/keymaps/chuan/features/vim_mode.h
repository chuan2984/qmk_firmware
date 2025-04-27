#pragma once
#include QMK_KEYBOARD_H

void set_vim_rgb_layer(uint8_t layer);
bool process_vim_record(uint16_t keycode, keyrecord_t *record);
