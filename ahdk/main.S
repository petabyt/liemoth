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
.global ambsh_printf
ambsh_printf:
	push {r7, lr}
	bl AMBSH_PRINTF
	pop {r7, pc}

.global ambsh_msleep
ambsh_msleep:
	push {r7, lr}
	bl AMBSH_MSLEEP
	pop {r7, pc}

.global ambsh_sprintf
ambsh_sprintf:
	push {r7, lr}
	bl AMBSH_SPRINTF
	pop {r7, pc}

.global ambsh_fopen
ambsh_fopen:
	push {r7, lr}
	bl AMBSH_FOPEN
	pop {r7, pc}

.global ambsh_fread
ambsh_fread:
	push {r7, lr}
	bl AMBSH_FREAD
	pop {r7, pc}

.global ambsh_close
ambsh_fclose:
	push {r7, lr}
	bl AMBSH_FCLOSE
	pop {r7, pc}

.global ambsh_gpio
ambsh_gpio:
	push {r7, lr}
	bl 0xc0107f64
	pop {r7, pc}
