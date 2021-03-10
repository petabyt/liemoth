// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

.global _start

_start:
	adr r1, foo
	b a
	bl AMBSH_PRINTF
	a:
		
	// Hack an early return.
	pop {r4, pc}
.byte 0, 0 // Function padding required
foo: .string ":-)"
