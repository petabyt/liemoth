// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

.global _start
_start:
	push {r7, lr}
	ldr r1, =foo
	bl 0xc0272996
	pop {r7, pc}
foo: .string "%s"
