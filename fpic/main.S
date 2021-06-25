// Test assembly injections here

.thumb

#define SIZE 1000

.global _start
_start:
	push {r4, lr}

	// Preserve env
	push {r0}

	// push stack
	sub sp, #8

	// Alloc size
	mov r0, #1
	ldr r1, size
	add r2, sp, #4
	bl AMB_ALLOC

	// Fopen into r3
	ldr r0, =file
	ldr r1, =read
	bl AMB_FOPEN
	mov r3, r0

	// fread binary into allocated
	// address
	add r0, sp, #4
	ldr r0, [r0]
	mov r1, #1
	ldr r2, size
	bl AMB_FREAD

	// Load code address into r1
	add r1, sp, #4
	ldr r1, [r1]

	// pop stack
	add sp, #8

	// Pop back env
	pop {r0}

	// Jump to code, hope
	// nothing bad happens
	blx r1
	pop {r4, pc}

.align 4
size: .long 20000
file: .string "d:/ahdk/ahdk.bin"
read: .string "r"