// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

.global _start
_start:
	ldmia sp!,{r4, pc}
	mov r0, #1000
	blx 0xC026CC9c
	stmdb sp!,{r4, lr}
