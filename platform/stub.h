// Use ARM bytecode if address independent
// code generation requested (STANDALONE)
#ifdef STANDALONE
	#ifdef P_THUMB
		#undef P_THUMB
		#define P_ARM
	#endif
#endif

#ifdef P_THUMB
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

#define NSTUB(name, addr) ROUTE name addr