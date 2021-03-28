// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif
.arm
.global _start
_start:
	ldrb r0, [sp, #0x10]
	add sp, sp, #0x1c
