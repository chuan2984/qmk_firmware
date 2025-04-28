#include "quantum.h"
#include "vim_mode.h"
#include "layers.h"
#include "rgb_layers.h"

const rgblight_segment_t PROGMEM chuan_0_layer[]  = RGBLIGHT_LAYER_SEGMENTS({0, 16, HSV_LUNA});
const rgblight_segment_t PROGMEM gaming_1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 16, HSV_RED});
const rgblight_segment_t PROGMEM symbol_2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 16, HSV_ORANGE});
const rgblight_segment_t PROGMEM number_3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 16, HSV_YELLOW});
const rgblight_segment_t PROGMEM vim_insert_4_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 16, HSV_CYAN});
const rgblight_segment_t PROGMEM vim_normal_5_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 16, HSV_BLUE});
const rgblight_segment_t PROGMEM vim_visual_6_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 16, HSV_PINK});
const rgblight_segment_t PROGMEM vim_visual_line_7_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 16, HSV_PURPLE});
const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    chuan_0_layer, gaming_1_layer, symbol_2_layer, number_3_layer, vim_insert_4_layer,
    vim_normal_5_layer, vim_visual_6_layer, vim_visual_line_7_layer);

void rgb_layers_init(void) {
    rgblight_layers = my_rgb_layers;
}

layer_state_t rgb_layers_update(layer_state_t state) {
    rgblight_set_layer_state(_CHUAN, layer_state_cmp(state, _CHUAN));
    rgblight_set_layer_state(_GAMING, layer_state_cmp(state, _GAMING));
    rgblight_set_layer_state(_SYMBOL, layer_state_cmp(state, _SYMBOL));
    rgblight_set_layer_state(_NUMBER, layer_state_cmp(state, _NUMBER));
    set_vim_rgb_layer(_NULL);
    return state;
}
