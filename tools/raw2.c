// This utility prints an Ambarella A7 screen buffer
// Requires gfx.h
// wget https://raw.githubusercontent.com/petabyt/gfx/master/gfx.h
// cc screen.c -lX11; ./a.out
#include <stdio.h>
#include <stdlib.h>

#include "gfx.h"

#define WIDTH 1920
#define HEIGHT 1080

int main() {
	// Open a new window for drawing.
	struct gfx_window window = gfx_open(WIDTH, HEIGHT, "ahdk");

	FILE *f = fopen("/media/daniel/8765-4321/myvideo.raw", "r");

	// Ambarella display buffer is bottom left to top right
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			unsigned char a = fgetc(f);
			gfx_setColor(&window, a, a, a);
			gfx_pixel(&window, x, y);
		}
	}
	
	struct gfx_interaction ia = gfx_event();
	gfx_close(&window);

	fclose(f);

	return 0;
}