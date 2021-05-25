// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

// TODO: Safe memory copying

.global _start

#ifdef P_THUMB
_start:
	.thumb
	// Preserve r0, which holds env
	push {r0}
	
	// Open the file
	ldr r0, =file
	ldr r1, =read
	bl AMB_FOPEN

	// Load the binary into memory
	movs r5,r0
	ldr r4, =MEM_MAIN
	top:
		mov r0, r4
		mov r1, #1
		ldr r2, =255
		mov r3, r5
		bl AMB_FREAD
		add r4, #255
		cmp r0, #1
	bgt top

	pop {r0}

	// TODO: fclose

	// Now jump to code and hope its there
	bl MEM_MAIN
				
	// Hack an early return.
	pop {r4, pc}
#endif

#ifdef P_ARM
_start:
	.arm
	mov r6, r0
	
	ldr r0, =file
	ldr r1, =read
	bl AMB_FOPEN

	mov r5, r0
	ldr r4, =MEM_MAIN
	top:
		mov r0, r4
		mov r1, #1
		mov r2, #255
		mov r3, r5
		bl AMB_FREAD
		add r4, #255
		cmp r0, #1
	bgt top

	mov r0, r6
	bl MEM_MAIN
	
	ldmia sp!, {r4, pc}
#endif

file: .string "d:/ahdk/ahdk.bin"
read: .string "r"
