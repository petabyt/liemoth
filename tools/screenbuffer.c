// This utility prints an Ambarella A7 screen buffer
// Requires gfx.h
// wget https://raw.githubusercontent.com/petabyt/gfx/master/gfx.h
// cc screen.c -lX11; ./a.out
#include <stdio.h>
#include <stdlib.h>

#include "gfx.h"

int WIDTH = 500;
int HEIGHT = 500;

struct Col {
	int r;
	int g;
	int b;
};

struct Col rgb(int c) {
	struct Col col;
	col.r = (c >> 5) * 32;
	col.g = ((c & 28) >> 2) * 32;
	col.b = (c & 3) * 64;
	return col;
}

int main() {
	// Open a new window for drawing.
	struct gfx_window window = gfx_open(WIDTH, HEIGHT, "ahdk");

	for (WIDTH = 0; WIDTH < 400; WIDTH++) {
		FILE *f = fopen("/media/daniel/8765-4321/asd", "r");
		// Ambarella display buffer is bottom left to top right
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				int a = fgetc(f);
				//struct Col col = rgb((char)a);
				gfx_setColor(&window, a, a, a);
				gfx_pixel(&window, x, y);
				//struct gfx_interaction ia = gfx_event();
				//printf("%d\n", x);
			}
		}

		fclose(f);
	}

	struct gfx_interaction ia = gfx_event();
	gfx_close(&window);

	return 0;
}
