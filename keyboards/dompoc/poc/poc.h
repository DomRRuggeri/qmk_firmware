#pragma once

#include "quantum.h"

// Any changes to the layout names and/or definitions must also be made to info.json

#define LAYOUT_ortho_2x2( \
    K00, K01, \
    K02, K03 \
) { \
    { K00,   K01,}, \
    { K02,   K03 }  \
}