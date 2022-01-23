#include QMK_KEYBOARD_H


enum sofle_layers {
    _COLEMAK,
    _RAISE,
};

enum custom_keycodes {
    KC_COLEMAK,
    KC_RAISE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  {   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  | }    |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | DEL  |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  | BSPC |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | TO(1)| LCTR | LALT | CMD |  / SPACE /       \ ENTER\  | LEFT | DOWN | UP   | RIGHT |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_COLEMAK] = LAYOUT(
  HYPR_T(KC_ESC),   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_LBRC,
  KC_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_RBRC,
  KC_DEL,   KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_O,  KC_BSPC,
  SFT_T(KC_QUOT),  KC_Z,   KC_X,    KC_C,    KC_D,    KC_V, KC_MPLY,      KC_F12,KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
    OSL(1),KC_LCTL, LALT_T(KC_MINS), LGUI_T(KC_GRV), KC_SPC,      KC_ENT,  KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
),
/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * | ~    | F1   | F2   | F3   | F4   | F5   |                    | F6   | F7   | F8   | F9   | F10  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | M_UP |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | M_L  | M_D  | M_R  | ~    |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | HYPR |      |      | BSLS |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /MINUS  /       \PLUS  \  |PREV  | VOLD | VOLU | NEXT |
 *            | TO(0)|      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
HYPR_T(KC_ESC),  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                KC_F6,   KC_F7,   KC_F8,  KC_F9,  KC_F10,  KC_NO,
  _______, _______, KC_MS_U,_______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_GRV, _______,                     _______,  _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,  KC_MPLY, _______, _______, _______, _______, KC_BSLS, _______,
                    TO(0), _______, _______, _______, KC_MINS,       KC_EQL, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
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
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("MAC"), false);
    } else {
        oled_write_ln_P(PSTR("WIN"), false);
    }

    switch (get_highest_layer(default_layer_state)) {
        case _COLEMAK:
            oled_write_ln_P(PSTR("Clmk"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
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
                // update_tri_layer(_RAISE);
            } else {
                layer_off(_RAISE);
                // update_tri_layer(_RAISE);
            }
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDOWN);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code16(G(KC_MINS));
        } else {
            tap_code16(G(KC_EQL));
        }
    }
    return true;
}

#endif
