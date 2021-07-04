.global _start

#ifdef P_THUMB
_start:
	.thumb
	push {r4, lr}
	sub sp, #8

	// Preserve parameters
	push {r0, r1, r2}

	#ifdef STANDALONE
		// Alloc size
		mov r0, #1
		ldr r1, size
		add r2, sp, #4
		bl AMB_ALLOC
	#endif

	// Fopen into r3
	ldr r0, =file
	ldr r1, =read
	bl AMB_FOPEN
	mov r3, r0

	// Fread
	#ifdef STANDALONE
		// fread binary into allocated
		// address
		add r0, sp, #4
		ldr r0, [r0]
	#else
		// load into empty address
		ldr r0, =MEM_MAIN
	#endif
	mov r1, #1
	ldr r2, size
	bl AMB_FREAD

	#ifdef STANDALONE
		// Load code address into r1
		add r1, sp, #4
		ldr r1, [r1]
	
		// Pop back env
		pop {r0, r1, r2}
	
		// Jump to code, hope
		// nothing bad happens
		blx r1 // start(int *env, long addr)
	#else
		pop {r0, r1, r2}
		bl MEM_MAIN
	#endif

	add sp, #8
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

#ifdef STANDALONE
	.byte 0, 0
#else
	
#endif
size: .long 20000
file: .string "d:/ahdk/ahdk.bin"
read: .string "r"
