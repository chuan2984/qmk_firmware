#pragma once

#include QMK_KEYBOARD_H

typedef void *(*leader_func_t)(uint16_t);

// Check to see if we are leading
bool is_leading(void);
// Start leader sequence
void start_leading(void);
// Stop leader sequence
void stop_leading(void);

// Process keycode for leader sequences
bool process_leader(uint16_t keycode, const keyrecord_t *record);

#ifdef LEADER_DISPLAY_STR
char *leader_display_str(void);

#    define OLED_LEADER_DISPLAY()                           \
        {                                                   \
            static uint16_t timer = 0;                      \
            if (is_leading()) {                             \
                oled_write_ln(leader_display_str(), false); \
                timer = timer_read();                       \
            } else if (timer_elapsed(timer) < 175) {        \
                oled_write_ln(leader_display_str(), false); \
            } else {                                        \
                /* prevent it from ever looping around */   \
                timer = timer_read() - 200;                 \
                oled_write_ln("", false);                   \
            }                                               \
        }
#endif
