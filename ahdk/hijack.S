// These are memory hijack tests. Insert bytes into
// memory, and see what happens.

// Template:
// add hijack("MYHIJACK", 0x123456); to build.c
#ifdef MYHIJACK
	.thumb
	.global _start
	_start:
		mov r0, #1
#endif

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

#ifdef SYSLOG
	// Hijack syslog and send output into
	// env stdout. env is pulled from MEM_PARAM,
	// if not zero.
	// log(int mode, char fmt[], ...)
	.thumb
	.global _start
	_start:
		push {r7, lr}
		ldr r0, =MEM_PARAM
		ldr r0, [r0]
		cmp r0, #0
		beq q
		push {r0}
		bl AMB_PRINTF
		pop {r0}
		ldr r1, =newline
		bl AMB_PRINTF
		q:
		pop {r7, pc}
	newline: .string "\n"
#endif

#ifdef SYSLOG2
	// syslog2 hijacker
	// Params are incompatible with AMB_PRINTF,
	// So expect it to not work
	// log(char fmt[], ...)
	.thumb
	.global _start
	_start:
		push {r0, r1, r2, r3, r4, lr}
		// Shift regs
		mov r4, r3
		mov r3, r2
		mov r2, r1
		mov r1, r0
		
		ldr r0, =MEM_PARAM
		ldr r0, [r0]

		cmp r0, #0
		beq q

		push {r0}
		bl AMB_PRINTF
		pop {r0}

		// Hack in random {10, 0} for clean
		// printing (Activeon dx)
		ldr r1, =0xc013a5e8+7
		bl AMB_PRINTF

		q:
		pop {r0, r1, r2, r3, r4, pc}
#endif