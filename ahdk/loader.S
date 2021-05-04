// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

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

	// No fclose because Im lazy
	
	mov r1, #0 // TODO: insert param
	bl MEM_MAIN
				
	// Hack an early return.
	pop {r4, pc}
#endif

#ifdef P_ARM
_start:
	.arm
	ldmia sp!,{r4 lr}
#endif

file: .string "d:/ahdk/ahdk.bin"
read: .string "r"


