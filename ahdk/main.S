// This is main assembly file to help C
// It is GCC preprocessed

#ifdef P_THUMB

// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

// Main entry function
// (this function is beginning of the binary)
.global _start
_start:
	push {r7, lr}
	bl start
	pop {r7, pc}

// Stub routers, dont
// want to bother with blx for now
.global printf
printf:
	push {r7, lr}
	bl AMB_PRINTF
	pop {r7, pc}

.global msleep
msleep:
	push {r7, lr}
	bl AMB_MSLEEP
	pop {r7, pc}

.global sprintf
sprintf:
	push {r7, lr}
	bl AMB_SPRINTF
	pop {r7, pc}

.global fopen
fopen:
	push {r7, lr}
	bl AMB_FOPEN
	pop {r7, pc}

.global fread
fread:
	push {r7, lr}
	bl AMB_FREAD
	pop {r7, pc}

.global fwrite
fwrite:
	push {r7, lr}
	bl AMB_FWRITE
	pop {r7, pc}

.global fclose
fclose:
	push {r7, lr}
	bl AMB_FCLOSE
	pop {r7, pc}

.global gpio
gpio:
	push {r7, lr}
	bl AMB_GPIO
	pop {r7, pc}

.global setExp
setExp:
	push {r7, lr}
	bl AMB_EXP
	pop {r7, pc}

.global malloc
malloc:
	push {r7, lr}
	bl AMB_ALLOC
	pop {r7, pc}

.global free
free:
	push {r7, lr}
	bl AMB_FREE
	pop {r7, pc}

.global openDir
openDir:
	push {r7, lr}
	bl AMB_OPENDIR
	pop {r7, pc}

.global nextFile
nextFile:
	push {r7, lr}
	bl AMB_NEXTFILE
	pop {r7, pc}

.global mkdir
mkdir:
	push {r7, lr}
	bl AMB_MKDIR
	pop {r7, pc}

#endif
