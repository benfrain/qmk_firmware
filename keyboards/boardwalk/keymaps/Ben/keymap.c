
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
 
typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;




// Layer shorthand
enum layer_names {
    _BASE,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base Layer
     
     */
    [_BASE] = LAYOUT_ortho_5x14(
LT(1, KC_ESC),  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LPRN,  KC_RPRN,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    CW_TOGG,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_LBRC, KC_RBRC, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_GRAVE,
        KC_DEL,  LCTL_T(KC_A),    LALT_T(KC_R),    LGUI_T(KC_S),    LSFT_T(KC_T),    HYPR_T(KC_G),    KC_MINS, KC_EQL, HYPR_T(KC_M),    LSFT_T(KC_N),    LGUI_T(KC_E),    LALT_T(KC_I),    LCTL_T(KC_O),    KC_BSPC,
SFT_T(KC_QUOT), KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    LGUI(KC_C), LGUI(KC_V), KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,  KC_DQUO,
        _______,  LCTL(LSFT(KC_TAB)), KC_PGDN, KC_PGUP, LCTL(KC_TAB), KC_SPC,  KC_SPC,  KC_ENT,  KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______
    ),

    /* Function Layer
    
     */
    [_FN] = LAYOUT_ortho_5x14(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,   KC_F12,   KC_F6,   KC_F7,   KC_F8,  KC_F9,  KC_F10, RGB_TOG,
        _______, _______, KC_MS_U,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
        LAG(KC_MEDIA_EJECT), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_MPLY, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______
    )

};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BASE:
            rgblight_setrgb(RGB_BLUE);
            break;
        case _FN:
            rgblight_setrgb(RGB_RED);
            break;
        default: // for any other layers, or the default layer
            rgblight_setrgb (RGB_WHITE);
            break;
    }
  return state;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LCTL, KC_A):
            return TAPPING_TERM + 151;
        case MT(MOD_LALT, KC_R):
            return TAPPING_TERM + 151;
        case MT(MOD_LGUI, KC_S):
            return TAPPING_TERM + 151;
        case MT(MOD_LSFT, KC_T):
            return TAPPING_TERM + 1;
        case ALL_T(KC_G):
            return TAPPING_TERM + 151;
        case ALL_T(KC_M):
            return TAPPING_TERM + 151;
        case MT(MOD_RSFT, KC_N):
            return TAPPING_TERM + 1;
        case MT(MOD_LGUI, KC_E):
            return TAPPING_TERM + 101;
        case MT(MOD_LALT, KC_I):
            return TAPPING_TERM + 151;
        case MT(MOD_LCTL, KC_O):
            return TAPPING_TERM + 151;
        default:
            return TAPPING_TERM;
    }
}