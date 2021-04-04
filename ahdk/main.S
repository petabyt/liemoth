// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

// Main entry function
.global _start
_start:
	push {r7, lr}
	bl start
	pop {r7, pc}

// Stub routers, dont
// want to bother with blx for now
.global amb_printf
amb_printf:
	push {r7, lr}
	bl AMB_PRINTF
	pop {r7, pc}

.global amb_msleep
amb_msleep:
	push {r7, lr}
	bl AMB_MSLEEP
	pop {r7, pc}

.global amb_sprintf
amb_sprintf:
	push {r7, lr}
	bl AMB_SPRINTF
	pop {r7, pc}

.global amb_fopen
amb_fopen:
	push {r7, lr}
	bl AMB_FOPEN
	pop {r7, pc}

.global amb_fread
amb_fread:
	push {r7, lr}
	bl AMB_FREAD
	pop {r7, pc}

.global amb_fwrite
amb_fwrite:
	push {r7, lr}
	bl AMB_FWRITE
	pop {r7, pc}

.global amb_fclose
amb_fclose:
	push {r7, lr}
	bl AMB_FCLOSE
	pop {r7, pc}

.global amb_gpio
amb_gpio:
	push {r7, lr}
	bl AMB_GPIO
	pop {r7, pc}

.global amb_exp
amb_exp:
	push {r7, lr}
	bl AMB_EXP
	pop {r7, pc}

.global amb_alloc
amb_alloc:
	push {r7, lr}
	bl AMB_ALLOC
	pop {r7, pc}

.global amb_free
amb_free:
	push {r7, lr}
	bl AMB_FREE
	pop {r7, pc}

.global amb_openDir
amb_openDir:
	push {r7, lr}
	bl AMB_OPENDIR
	pop {r7, pc}

.global amb_nextFile
amb_nextFile:
	push {r7, lr}
	bl AMB_NEXTFILE
	pop {r7, pc}
