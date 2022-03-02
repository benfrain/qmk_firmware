#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define PRODUCT         dactyl_bf
// Serial, not i2c wiring
#define USE_SERIAL

// Default to master left
// #define MASTER_LEFT
#define SPLIT_USB_DETECT
#define SOFT_SERIAL_PIN D5
// Rows are doubled-up, because it is the total number of rows between the two halves.
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { F7, B1, B3, B2, B6, F6 }
#define MATRIX_COL_PINS { B5, B4, E6, D7, C6, D4 }

#define DIODE_DIRECTION COL2ROW

// Default diode direction
#define DIODE_DIRECTION COL2ROW


// Tapping term is used for many things, e.g.
// - how fast I need to double tap the number keys to get an F key
// - for mod-shifts, how long they need to be held to be considered a hold rather than a tap.
#define TAPPING_TERM 200
