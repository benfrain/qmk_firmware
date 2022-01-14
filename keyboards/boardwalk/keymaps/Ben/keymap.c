
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

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};

// Tap dance enums
enum {
    CMD_PLUS,
    CMD_MNS
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void plustap_finished(qk_tap_dance_state_t *state, void *user_data);
void plustap_reset(qk_tap_dance_state_t *state, void *user_data);
void mns_finished(qk_tap_dance_state_t *state, void *user_data);
void mns_reset(qk_tap_dance_state_t *state, void *user_data);

// Layer shorthand
enum layer_names {
    _BASE,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | TAB    | Q      | W      | E      | R      | T      | [      | ]      | Y      | U      | I      | O      | P      | '      |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * | CAP LK | A      | S      | D      | F      | G      | HOME   | PG UP  | H      | J      | K      | L      | ;      | ENTER  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * | LSHIFT | Z      | X      | C      | V      | B      | END    | PG DN  | N      | M      | ,      | .      | /      | RSHIFT |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
     * | LCTRL  | LGUI   | FN     | LALT   | SPACE  | SPACE  | SPACE  | SPACE  | SPACE  | LEFT   | DOWN   | UP     | RIGHT  | RCTRL  |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_BASE] = LAYOUT_ortho_5x14(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_F11,  KC_F12,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_BSLS, KC_SLSH, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_RBRC,
        KC_DEL,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    TD(CMD_MNS), TD(CMD_PLUS),KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_BSPC,
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    RGB_TOG, RGB_M_R, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_GRV,  KC_RSPC,
        TO(1),   KC_PGDN, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  KC_SPC,  KC_ENT,  KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, HYPR(KC_NO)
    ),

    /* Function Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * | `      | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | DEL    |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * |        |        | MENU   |        |        |        |        |        |        |        |        |        | PRT SC |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        | RESET  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * |        |        |        |        |        |        |        |        |        | MUTE   | VOL DN | VOL UP | \      |        |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_FN] = LAYOUT_ortho_5x14(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,   KC_NO,   KC_F6,   KC_F7,   KC_F8,  KC_F9,  KC_F10,  KC_NO,
        _______, _______, KC_MS_U,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        TO(0), KC_PGUP, _______, _______, _______, _______, _______, KC_BTN1, KC_MPLY, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, RESET
    )

};


/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}

// Create an instance of 'tap' for the 'x' tap dance.
static tap plustap_state = {
    .is_press_action = true,
    .state = 0
};

void plustap_finished(qk_tap_dance_state_t *state, void *user_data) {
    plustap_state.state = cur_dance(state);
    switch (plustap_state.state) {
        case SINGLE_TAP: register_code(KC_EQL); break;
        case SINGLE_HOLD: register_code16(G(KC_EQL)); break;
        case DOUBLE_TAP: register_code16(S(KC_EQL)); break;
        case DOUBLE_HOLD: register_code(KC_NO); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case DOUBLE_SINGLE_TAP: tap_code(KC_EQL); register_code(KC_EQL);
    }
}

void plustap_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (plustap_state.state) {
        case SINGLE_TAP: unregister_code(KC_EQL); break;
        case SINGLE_HOLD: unregister_code16(G(KC_EQL)); break;
        case DOUBLE_TAP: unregister_code16(S(KC_EQL)); break;
        case DOUBLE_HOLD: unregister_code(KC_NO);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_EQL);
    }
    plustap_state.state = 0;
}

// Create an instance of 'tap' for the 'x' tap dance.
static tap mnstap_state = {
    .is_press_action = true,
    .state = 0
};

void mns_finished(qk_tap_dance_state_t *state, void *user_data) {
    mnstap_state.state = cur_dance(state);
    switch (mnstap_state.state) {
        case SINGLE_TAP: register_code(KC_MINS); break;
        case SINGLE_HOLD: register_code16(G(KC_MINS)); break;
        case DOUBLE_TAP: register_code16(A(KC_MINS)); break;
        case DOUBLE_HOLD: register_code(KC_NO); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case DOUBLE_SINGLE_TAP: tap_code(KC_MINS); register_code(KC_MINS);
    }
}

void mns_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (mnstap_state.state) {
        case SINGLE_TAP: unregister_code(KC_MINS); break;
        case SINGLE_HOLD: unregister_code16(G(KC_MINS)); break;
        case DOUBLE_TAP: unregister_code16(S(KC_MINS)); break;
        case DOUBLE_HOLD: unregister_code(KC_NO);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_MINS);
    }
    mnstap_state.state = 0;
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [CMD_PLUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, plustap_finished, plustap_reset),
    [CMD_MNS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mns_finished, mns_reset)
};
