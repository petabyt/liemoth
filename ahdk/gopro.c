// Special GoPro video test
#include "ambarella.h"
#include "ahdk.h"
#include "gopro.h"

unsigned char screenBuf[1000];

// Not working, I think
void setPixel(int x, int y) {
	screenBuf[y * SCREEN_WIDTH + (x >> 3)] |= 1 << (x % 8);
}

#define FRAMES 6335
#define DELAY 40

void playVideo() {
	int i = 0;
	FILE *f = fopen("d:/video.bin", "r");
	while (1) {
		if (i == FRAMES) {
			fclose(f);
			f = fopen("d:/video.bin", "r");
			i = 0;
		} else {
			fread(&screenBuf, (SCREEN_WIDTH * 8) * SCREEN_HEIGHT / 7, 1, f);
			showBuffer(screenBuf);
			i++;
		}

		msleep(DELAY);
	}
}

void start(int *env) {
	printf(env, "Playing video on front panel...");
	playVideo();
}
