// Serial, not i2c wiring
#define USE_SERIAL

// Default to master left
#define MASTER_LEFT

// Rows are doubled-up, because it is the total number of rows between the two halves.
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// wiring of each half, use the bottom left 6 and the bottom right 6 pins.
#define MATRIX_ROW_PINS { F7, B1, B3, B2, B6 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }

// Mirror the pins on the other side.
// #define MATRIX_COL_PINS_RIGHT { B5, B4, E6, D7, C6, D4 }
// #define MATRIX_ROW_PINS_RIGHT { F7, B1, B3, B2, B6 }

// Default diode direction
#define DIODE_DIRECTION COL2ROW

// See https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#ignore-mod-tap-interrupt
// Turning this on would prevent a quick `'s` from resulting in `S` if the right quote key was a shift mod tap key.
// However, it means I need to properly hold shift and the key to be shifted for longer than
// the tapping term, which is worse. So this is disabled for now.
// #define IGNORE_MOD_TAP_INTERRUPT
// See explanation in `get_ignore_mod_tap_interrupt` of `keymap.c`
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY

// Tapping term is used for many things, e.g.
// - how fast I need to double tap the number keys to get an F key
// - for mod-shifts, how long they need to be held to be considered a hold rather than a tap.
#define TAPPING_TERM 200
