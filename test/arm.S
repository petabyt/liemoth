// Arm inst test
.global _start
_start:
	stmdb sp!, {r4, lr}
	ldmia sp!, {r4, pc}
