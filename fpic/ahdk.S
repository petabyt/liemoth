.global _start
_start:
	ldr r0, =asd
	ldr r6, =0xc0275804
	add r6, #1
	mov lr, pc
	bx r6
	
	bx lr

asd: .string "d:/asd"