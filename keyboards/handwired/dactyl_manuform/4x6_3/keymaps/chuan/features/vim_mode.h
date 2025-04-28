#pragma once
#include QMK_KEYBOARD_H

void set_vim_rgb_layer(uint8_t layer);
bool process_vim_mode(uint16_t keycode, const keyrecord_t *record);
void process_vim_activation(const keyrecord_t *record);
