// Yes, linker script written in C.
// Just in case I need to access the stubs.

// Default platform
#ifndef P_NAME
	#include "../../platform/activeondx.h"
#endif

ENTRY(_start)
SECTIONS
{
	. = MEM_MAIN;
}
