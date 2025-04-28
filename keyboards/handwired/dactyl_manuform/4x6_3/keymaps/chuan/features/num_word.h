#pragma once

#include QMK_KEYBOARD_H

bool num_word_enabled(void);
void enable_num_word(void);
void disable_num_word(void);
void process_num_word_activation(const keyrecord_t *record);
bool process_num_word(uint16_t keycode, const keyrecord_t *record);
