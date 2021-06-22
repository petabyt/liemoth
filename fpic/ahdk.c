/*
ldr r3, [asd]
str r3, [r11, #-0x8] (?)
ldr r3, [r11, #-0x8] (?)
mov lr, pc
bx r3
...
asd: .word AMB_MKDIR
*/

int farts();

void _start() {
	farts();
}