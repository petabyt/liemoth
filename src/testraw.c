// Quick custom hello world test.
// `make minimal file=test.c`

#include "stdlib.h"
#include "ambarella.h"
#include "ahdk.h"

#define WIDTH 864
#define HEIGHT 480
#define MARGIN 95

#define SCALE 4

unsigned char *buf;
void plot(int x, int y, int c) {
	x += 5;
	y += 20;
	buf[x * SCREEN_HEIGHT - y] = c;
}

void readBuffer() {
	buf = (unsigned char *)MEM_BUFFER;
	unsigned char *sensor = (unsigned char *)0xc45a1a00;

	// Ambarella display buffer is bottom left to top right
	for (int y = 0; y < HEIGHT / SCALE; y++) {
		for (int x = 0; x < WIDTH / SCALE; x++) {
			plot(x, y, (*sensor));

			sensor++;

			// Horizontal Pixel skip
			for (int i = 0; i < SCALE - 1; i++) {
				sensor++;
			}
		}

		// Vertical Pixel skip
		sensor += (SCALE - 1) * WIDTH;
	}
}

void start(int *env, int argc, char *argv[]) {
	while (1) {
		readBuffer();
	}
}
