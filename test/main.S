// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

.global _start
_start:
	mov r3, r2
	mov r2, r1
	ldr r1, =foo
	bl AMBSH_PRINTF
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}

foo: .string "%d_%s"

