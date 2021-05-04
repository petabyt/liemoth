// This is main assembly file to help C
// It is GCC preprocessed

#ifdef P_THUMB
.thumb

// Main entry function
// (this function is beginning of the binary)
.global _start
_start:
	push {r7, lr}
	bl start
	pop {r7, pc}

// Stub routers, dont
// want to bother with blx for now
.macro ROUTE name, addr
.global \name
\name:
	push {r7, lr}
	bl \addr
	pop {r7, pc}
.endm

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
ROUTE mkdir AMB_MKDIR
ROUTE msleep AMB_MSLEEP

#endif
