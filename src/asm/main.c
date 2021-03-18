// Default platform
#ifndef P_NAME
	#include "../../platform/activeondx.h"
#endif

void ambsh_msleep();
void ambsh_printf();

// GPIO thing?
int thing() {
	__asm__("bl 0xc026e518");
}

// Screen weird, needs magic numbers
void drawPixel(int x, int y, unsigned char col) {
	unsigned char *screen = (unsigned char*)MEM_BUFFER;
	y += 20;
	x += 5;
	screen[x * SCREEN_HEIGHT - y] = col;
}

void fillRect(int x, int y, int x1, int y1, int col) {
	for (int tx = x; tx < x1; tx++) {
		for (int ty = y; ty < y1; ty++) {
			drawPixel(tx, ty, col);
		}
	}
}

void clearScreen() {
	unsigned char *screen = (unsigned char*)MEM_BUFFER;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		screen[i] = 0xff;
	}
}

void start(void *env) {
	int sel = 0;
	unsigned char *param = (unsigned char*)MEM_PARAM;
	if (*param == 0) {
		// This will be sent into log
		ambsh_printf(env, "Hello, World");

		// Draw main box
		fillRect(10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 40, 0x5d);

		// Draw selector box
		fillRect(20, 20, SCREEN_WIDTH - 30, 40 + (sel * 10), 0x20);

		// Horizontal lines
		for (int i = 10; i < SCREEN_WIDTH - 20; i++) {
			drawPixel(i, 10, 0x1);
			drawPixel(i, 215, 0x1);
		}

		// Vertical lines
		for (int i = 10; i < SCREEN_HEIGHT - 40; i++) {
			drawPixel(10, i, 0x1);
			drawPixel(300, i, 0x1);
		}

		ambsh_msleep(5000);
	} else {
		clearScreen();
	}
}
