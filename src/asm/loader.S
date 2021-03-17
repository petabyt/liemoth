// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

.global _start

_start:
	bl MEM_MAIN
	
	// Hack an early return.
	pop {r4, pc}
// Note: distance must be multiple of 4
//.byte 0, 0


