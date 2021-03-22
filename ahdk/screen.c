#include "header.h"

// Severely broken functions
void drawPixel(int x, int y, unsigned char col) {
	unsigned char *screen = (unsigned char*)MEM_BUFFER;
	y += 20;
	x += 5;
	screen[x * SCREEN_HEIGHT - y] = col;
}

void clearScreen() {
	unsigned char *screen = (unsigned char*)MEM_BUFFER;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		screen[i] = 0xff;
	}
}
