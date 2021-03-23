// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

SECTIONS {
	.text MEM_MAIN: { *(.text) }
	veener = ABSOLUTE(AMBSH_MSLEEP);
}
