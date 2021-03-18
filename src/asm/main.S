// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

// Jump to main entry function.
.global _start
_start:
	push {r7, lr}
	add  r7, sp, #0
	bl start
	mov  r8, r8
	mov  sp, r7
	pop  {r7, pc}
	mov  r8, r8

// Blx not working. Use bl hacks
// for now, to have easy changable
// stubs.
.global ambsh_printf
ambsh_printf:
	push {r7, lr}
	add  r7, sp, #0
	bl AMBSH_PRINTF
	mov  r8, r8
	mov  sp, r7
	pop  {r7, pc}
	mov  r8, r8

.global ambsh_msleep
ambsh_msleep:
	push {r7, lr}
	add  r7, sp, #0
	bl AMBSH_MSLEEP
	mov  r8, r8
	mov  sp, r7
	pop  {r7, pc}
	mov  r8, r8
