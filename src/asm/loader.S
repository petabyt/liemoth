// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

.global _start

_start:
	ldr r0, =(0xc2413880)
	mov r1, #0x5d
	mov r2, #0
	
	a:
		add r0, #1
		add r1, #1
		add r2, #1
		strb r1, [r0]
	b a
	
	// Hack an early return.
	pop {r4, pc}
// Note: distance must be multiple of 4
//.byte 0, 0


