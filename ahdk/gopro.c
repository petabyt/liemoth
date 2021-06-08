// Special GoPro video test
#include "ambarella.h"
#include "ahdk.h"
#include "gopro.h"

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

void start() {
	playVideo();
}
