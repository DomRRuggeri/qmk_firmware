#ifndef KB_H
#define KB_H

#include "quantum.h"

#define KEYMAP( \
	K01, K00,  \
	K11, K10  \
) { \
	{ K01,   K00 }, \
	{ K11,   K10 }  \
}

#endif
