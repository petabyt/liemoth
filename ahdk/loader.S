.global _start

#ifdef P_THUMB
_start:
	.thumb
	push {r4, lr}
	
	// Preserve r0, which holds env
	mov r6, r0
	
	// Open the file
	ldr r0, =file
	ldr r1, =read
	bl AMB_FOPEN

	movs r5, r0

	#ifdef ARM_ALLOC
		// Allocate 10k and get address into r4
		sub sp, #8 // Push stack
		mov r0, #1
		ldr r1, =10000 // size
		add r2, sp, #4
		bl AMB_ALLOC
		add sp, #8 // Pop stack

		// Load it into r7 for later
		add r7, sp, #4
		ldr r7, [r7]

		mov r4, r7
	#else
		ldr r4, =MEM_MAIN
	#endif
	
	top:
		mov r0, r4
		mov r1, #1
		ldr r2, =255
		mov r3, r5
		bl AMB_FREAD
		add r4, #255
		cmp r0, #1
	bgt top

	// Move env pointer back
	mov r0, r6

	// TODO: fclose

	// Now jump to code and hope its there
	#ifdef ARM_ALLOC
		blx r7
	#else
		bl MEM_MAIN
	#endif
				
	// Hack an early return.
	pop {r4, pc}
#endif

#ifdef P_ARM
_start:
	.arm
	stmia sp!, {r4, lr}
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
