// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

SECTIONS {
	.text MEM_MAIN: { *(.text) }
}

