// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

.global _start
_start:
	blx 0xc0138870
	pop {r4, pc}
