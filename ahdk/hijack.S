#ifdef BUTTON
// This attemps to hijack GUI code in order
// to launch AHDK on a UI button press.
// This is a WIP.

.thumb
.global _start
_start:
	// Default parameter
	mov r0, #0
	bl MEM_MAIN

#endif

// How many logs have been created?
.thumb
.global _start
_start:
	push {r7, lr}
	ldr r1, =MEM_PARAM
	ldr r2, [r1]
	add r2, #1
	str r2, [r1]
	pop {r7, pc}