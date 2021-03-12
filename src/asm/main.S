// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

.global _start

_start:
	push {r4, lr}
	bl AMBSH_PRINTF
	pop {r4, pc}

