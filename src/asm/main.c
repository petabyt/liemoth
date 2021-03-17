// Default platform
#ifndef P_NAME
	#include "../../platform/activeondx.h"
#endif

// Asm jumps to start of this file, functions have to be moved.
// TODO: Fix? With linker?
void drawPixel(int x, int y);
void clearScreen();

void _start(void *env) {
	unsigned char *param = (unsigned char*)MEM_PARAM;
	if (*param == 0) {
		for (int a = 0; a < 256; a++) {
			drawPixel(a, a);
			// TODO: reference functions with linker
			__asm__("ldr r0, =50\nbl 0xc026cc9c");
		}
	} else {
		clearScreen();
	}
}

void drawPixel(int x, int y) {
	unsigned char *screen = (unsigned char*)MEM_BUFFER;
	screen[y * SCREEN_HEIGHT - x] = 1;
}

void clearScreen() {
	unsigned char *screen = (unsigned char*)MEM_BUFFER;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		screen[i] = 0xff;
	}
}
