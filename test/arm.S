// Arm inst test
.global _start
_start:
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r0, =foo
	ldr r1, =fo
	mov r2, #0
	blx 0xc021a834

	mov r2, r0
	mov r0, r4
	adr r1, hello
	bl AMB_PRINTF
	ldmia sp!, {r4, pc}

hello: .string "%d"
