#pragma once

#include "quantum.h"

// Any changes to the layout names and/or definitions must also be made to info.json

#define LAYOUT_default( \
    K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,  K0E,  K4E,        K2E, \
    K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D,                         \
    K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,              K1E,  K2D,  K3D, \
    K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,              K48,  K49,  K4A, \
    K40,  K41,  K42,                    K43,              K44,  K45,  K46,  K47,              K4B,  K4C,  K4D  \
) { \
    { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,  K0E    }, \
    { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D,  K1E    }, \
    { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D,  K2E    }, \
    { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  K3D,  KC_NO  }, \
    { K40,  K41,  K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A,  K4B,  K4C,  K4D,  K4E    }  \
}

/*
#define LAYOUT_default( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,   K0E,   K0E,   K0E, \
    K10, K11, K12, K31, K41, K51, K61, K71, K81, K91, KA1, KB1, KC1, KD1,   KC_NO, KC_NO, KC_NO, \
    K20, K21, K22, K32, K42, K52, K62, K72, K82, K92, KA2, KB2, KC2, KC_NO, KE1,   KD1,   KD3, \
    K30, K31, K32, K33, K43, K53, K63, K73, K83, K93, KA3, KB3, KC3, KC_NO  K84,   K94,   KA4, \
    K40, K41, K42,                K34,           K44, K54, K64, K74, KC_NO, KB4,   KC4,   KD4 \

) { \
    { K00, K10, K20, K30,   K40,   K50,   K60,   K70,   K80,   K90, KA0, KB0, KC0, KD0,    KE0   }, \
    { K01, K11, K21, K31,   K41,   K51,   K61,   K71,   K81,   K91, KA1, KB1, KC1, KD1     KE1   }, \
    { K02, K12, K22, K32,   K42,   K52,   K62,   K72,   K82,   K92, KA2, KB2, KC2, KD2,    KE2   }, \
    { K03, K13, K23, K33,   K43,   K53,   K63,   K73,   K83,   K93, KA3, KB3, KC3, KD3,    KC_NO }, \
    { K04, K14, K24, K34,   K44,   K54,   K64,   K74,   K84,   K94, KA4, KB4, KC4, KD4,    KE4   }  \
}
*/
