// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

.global _start

_start:
	// r0 has r4, env
	adr r1, fart
	bl AMBSH_PRINTF

	bl MEM_MAIN
		
	// Hack an early return.
	pop {r4, pc}

fart: .string "Hey vsauce, michael here. Or am I?\n"
