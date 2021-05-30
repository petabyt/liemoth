// This utility prints an Ambarella A7 screen buffer
// Requires gfx.h
// wget https://raw.githubusercontent.com/petabyt/gfx/master/gfx.h
// cc screen.c -lX11; ./a.out
#include <stdio.h>
#include <stdlib.h>

#include "gfx.h"

// Start of buffer addr
int start = 0x2413880;

#define WIDTH 320
#define HEIGHT 256

int main() {
	// Open a new window for drawing.
	struct gfx_window window = gfx_open(500, 500, "ahdk");

	FILE *f = fopen("memdump.bin", "r");
	fseek(f, start, SEEK_SET);

	// Ambarella display buffer is bottom left to top right
	for (int x = 0; x < WIDTH; x++) {
		for (int y = HEIGHT; y > 0; y--) {
			int a = fgetc(f);
			gfx_setColor(&window, a, a, a);
			gfx_pixel(&window, x, y);
		}
	}

	struct gfx_interaction ia = gfx_event();
	gfx_close(&window);

	return 0;
}
