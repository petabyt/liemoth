/*
Main Assembly file for AHDK

This contains stub routers and any other assembly
that helps the main C code.

Stub routers:
Request to use blx by adding +1 to the function
address. The ROUTE macro will notice this and
use `blx` instead of `bl` (and subtract 1)

This file is preprocessed by the c preprocessor (for
working with camera info and C level), and the standard
ARM preprocessor for working at the assembly level.
*/

/*
fpic stub router:

.global mkdir
mkdir:
	ldr r11, addr
jump:
	add r10, pc
	bx r11
addr:
	.long AMB_MKDIR + 1
*/

// Use ARM bytecode if address independent
// code generation requested (STANDALONE)
#ifdef STANDALONE
	#ifdef P_THUMB
		#undef P_THUMB
		#define P_ARM
	#endif
#endif

#ifdef P_THUMB
	.thumb

	// Main entry function
	// (this function is beginning of the binary)
	.global _start
	_start:
		push {r7, lr}
		bl start
		pop {r7, pc}

	#ifdef STANDALONE
		// ...
	#else
		.macro ROUTE name, addr
		.global \name
		\name:
			push {r7, lr}

			// Check if stub was passed with
			// blx request (+1).
			.if (\addr % 2) != 0
				blx \addr - 1
			.else
				bl \addr
			.endif
			pop {r7, pc}
		.endm
	#endif

	.global jumptest
	jumptest:
		push {r7, lr}
		blx r1
		pop {r7, pc}
#endif

#ifdef P_ARM
	.arm

	.global _start
	_start:
		stmdb sp!, {r7, lr}
		bl start
		ldmia sp!, {r7, pc}

	#ifdef STANDALONE
		.macro ROUTE name, addr
		.global \name
		\name:
			push {r11, lr}
			.if (\addr % 2) != 0
				ldr r11, =(\addr)
			.else
				ldr r11, =(\addr + 1)
			.endif
			mov lr, pc
			bx r11
			pop {r11, lr}
			bx lr
		.endm
	#else
		.macro ROUTE name, addr
		.global \name
		\name:
			stmdb sp!, {r7, lr}
			.if (\addr % 4) != 0
				blx \addr - 1
			.else
				bl \addr
			.endif
			ldmia sp!, {r7, pc}
		.endm
	#endif
#endif

// POSIX
ROUTE printf AMB_PRINTF
ROUTE sprintf AMB_SPRINTF
ROUTE fopen AMB_FOPEN
ROUTE fread AMB_FREAD
ROUTE fwrite AMB_FWRITE
ROUTE fclose AMB_FCLOSE
ROUTE msleep AMB_MSLEEP

// Etc camera internals
ROUTE gpio AMB_GPIO
ROUTE ambaMalloc AMB_ALLOC
ROUTE ambaFree AMB_FREE
ROUTE openDir AMB_OPENDIR
ROUTE nextFile AMB_NEXTFILE
//ROUTE remove AMB_REMOVE

// Experimental optional functions
#ifdef AMB_MKDIR
	ROUTE mkdir AMB_MKDIR
#endif
#ifdef AMB_LU
	ROUTE lu AMB_LU
#endif
#ifdef AMB_EXP
	ROUTE setExp AMB_EXP
#endif

// Platform specific
#ifdef P_GOPRO
	ROUTE fpstring GP_FPSTRING
	ROUTE showBuffer GP_SHOWBUFFER
#endif
