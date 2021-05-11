// This routes stubs, dont want to bother with blx.
#ifdef P_THUMB
	.thumb

	// Main entry function
	// (this function is beginning of the binary)
	.global _start
	_start:
		push {r7, lr}
		bl start
		pop {r7, pc}

	.macro ROUTE name, addr
	.global \name
	\name:
		push {r7, lr}
		bl \addr
		pop {r7, pc}
	.endm
#endif

#ifdef P_ARM
	.arm

	.global _start
	_start:
		stmdb sp!, {r7, lr}
		bl start
		ldmia sp!, {r7, pc}

	.macro ROUTE name, addr
	.global \name
	\name:
		stmdb sp!, {r7, lr}
		// Check if stub was passed with
		// blx request (+1).
		.if (\addr % 4) != 0
			blx \addr - 1
		.else
			bl \addr
		.endif
		ldmia sp!, {r7, pc}
	.endm
#endif

ROUTE printf AMB_PRINTF
ROUTE sprintf AMB_SPRINTF
ROUTE fopen AMB_FOPEN
ROUTE fread AMB_FREAD
ROUTE fwrite AMB_FWRITE
ROUTE fclose AMB_FCLOSE
ROUTE gpio AMB_GPIO
ROUTE setExp AMB_EXP
ROUTE malloc AMB_ALLOC
ROUTE free AMB_FREE
ROUTE openDir AMB_OPENDIR
ROUTE nextFile AMB_NEXTFILE
ROUTE msleep AMB_MSLEEP

// This is experimental
#ifdef AMB_MKDIR
	ROUTE mkdir AMB_MKDIR
#endif

// Platform specific
#ifdef P_GOPRO
	ROUTE fpstring GP_FPSTRING
	ROUTE showBuffer GP_SHOWBUFFER
#endif
