// Test assembly injections here

.thumb

#define SIZE 1000

.global _start
_start:
	push {r4, lr}
	sub sp, #8

	mov r7, r0

	// Alloc size
	mov r0, #1
	ldr r1, =SIZE
	add r2, sp, #4
	bl AMB_ALLOC

	ldr r0, =file
	ldr r1, =read
	bl AMB_FOPEN
	mov r3, r0

	// fread binary into allocated
	// address	
	add r0, sp, #4
	ldr r0, [r0]
	mov r1, #1
	ldr r2, =SIZE
	bl AMB_FREAD

	// Jump to it
	add r0, sp, #4
	ldr r0, [r0]
	blx r0

	add sp, #8
	pop {r4, pc}

file: .string "d:/ahdk/ahdk.bin"
read: .string "r"