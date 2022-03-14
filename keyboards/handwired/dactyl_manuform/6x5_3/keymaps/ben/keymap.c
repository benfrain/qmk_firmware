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

enum sofle_layers {
    _COLEMAK,
    _RAISE,
};

enum custom_keycodes {
    KC_COLEMAK,
    KC_RAISE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_COLEMAK] = LAYOUT(
    HYPR_T(KC_ESC),     KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                      KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_LBRC,
    KC_TAB,             KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                                      KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN,    KC_RBRC,
    KC_DEL,             KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                                      KC_M,       KC_N,       KC_E,       KC_I,       KC_O,       KC_BSPC,
    SFT_T(KC_PGUP),     KC_Z,   KC_X,    KC_C,    KC_D,    KC_V,                                      KC_K,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH,    SFT_T(KC_PGDN),
    OSL(1), KC_LCTL,    LALT_T(KC_MINS),LGUI_T(KC_GRV),    KC_SPC,  TD(CMD_MNS),              TD(CMD_PLUS),       KC_ENT,     KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,
                                                                          KC_QUOT,         RSFT(KC_QUOT)

),

[_RAISE] = LAYOUT(
    KC_F11,             KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                   KC_F6,       KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F12,
    _______,            _______, KC_MS_U,_______, _______, _______,                                  _______,     _______,    _______,    _______,    _______,    _______,
    _______,            KC_MS_L, KC_MS_D, KC_MS_R, KC_GRV, _______,                                  _______,     _______,    _______,    _______,    _______,    _______,
    _______,            _______, _______, _______, _______, _______,                                 _______,     _______,    _______,    _______,    KC_BSLS,    _______,
    TO(0),              _______, _______, KC_MINS,G(KC_X),G(KC_C),                          _______,     KC_MPLY,    KC_MPRV,    KC_VOLD,    KC_VOLU,    KC_MNXT,
                                                                    G(KC_V),               _______
)};

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,120,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,224,252,255,255,255,255,127, 15,  1,225,249,249,249,253,255,255,255,191,131,128,  0,  0,  0,  0,  0,  0,248,248,248, 64,224,192,128,  0,192,192, 96, 96,192,128,  0,224,224,192, 96,224,192,  0, 64, 96,240,248,120,120, 72, 64, 96,224,224,192,192,192,  0,192, 96, 96,224,192,  0,  0, 96, 96,248,248,  0,  0,  0,224,224,192, 96,224,192,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224, 96,224,192,  0,128,192,224, 96,224,192,128,192,224, 64,224,192,224,192,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,192,248,255,255,255,255,255, 31,  3,192,224,239,239,239,255,255,255,255,255,255,255,127,  7,  0,  0,  0,  0,  0,  0, 15, 15, 15, 12, 14, 15,  7,  1, 15, 15, 15, 15, 15, 11,  0, 15, 15,  0,  0, 15, 15,  0, 12, 12, 15, 15, 12, 12,  0,  8, 12, 15, 15, 12, 12,  0,  6, 15, 15, 11, 15, 15, 12,  0, 12, 12, 15, 15, 12, 12,  0, 15, 15,  0,  0, 15, 15,  0,  0,  0, 12, 14, 12,  0,  0,  7, 15, 15, 12, 12, 12,  0,  7, 15, 15, 12, 14, 15,  7, 15, 15,  0, 15, 15, 15, 15,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0, 12, 31, 31, 31, 31, 31,  7,  0,  0, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void print_status_narrow(void) {
    // Print current layer
    oled_write_ln_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
            oled_write_P(PSTR("BASE\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("SYMS\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            return false;
    }
    return true;
}

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
