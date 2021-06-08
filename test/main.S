// 0xc0419d04
// Thumb inst test
.global _start
_start:
	mov r0, #0
	bl MEM_MAIN ; main(0);
	b 0xc0419d1a ; break;
