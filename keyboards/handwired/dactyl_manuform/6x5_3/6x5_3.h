#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05,R00, R01, R02, R03, R04, R05, \
    K10, K11, K12, K13, K14, K15,R10, R11, R12, R13, R14, R15,\
    K20, K21, K22, K23, K24, K25,R20, R21, R22, R23, R24, R25,\
    K30, K31, K32, K33, K34, K35,R30, R31, R32, R33, R34, R35,\
    K40, K41, K42, K43, K44, K45,R40, R41, R42, R43, R44, R45,\
    K53, R53  \
) { \
    { K00, K01, K02, K03, K04, K05 }, \
    { K10, K11, K12, K13, K14, K15 }, \
    { K20, K21, K22, K23, K24, K25 }, \
    { K30, K31, K32, K33, K34, K35 }, \
    { K40, K41, K42, K43, K44, K45 }, \
    { XXX, XXX, XXX, K53, XXX, XXX }, \
    { R00, R01, R02, R03, R04, R05 }, \
    { R10, R11, R12, R13, R14, R15 }, \
    { R20, R21, R22, R23, R24, R25 }, \
    { R30, R31, R32, R33, R34, R35 }, \
    { R40, R41, R42, R43, R44, R45 }, \
    { XXX, XXX, XXX, R53, XXX, XXX }, \
}
