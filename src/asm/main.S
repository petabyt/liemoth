// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

.global _start

// Why crash? Thumb bad?
_start:
	adr r1, fart
	bl AMBSH_PRINTF
	bx lr

fart: .string "fasdss\n"

