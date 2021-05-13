#ifndef __GOPRO
#define __GOPRO

// Width is 7 pixels * 8 bits, so 56 pixels
// Height is 90 layers
#define SCREEN_WIDTH 7
#define SCREEN_HEIGHT 80

// fpstring("HELLO", 0, 1);
void fpstring(char *text, unsigned int a, int b);
void showBuffer(unsigned char *buffer);

unsigned char screenBuf[1000];

void setPixel(int x, int y) {
	screenBuf[y * SCREEN_WIDTH + (x >> 3)] |= 1 << (x % 8);
}

#define FRAMES 1079
#define DELAY 30

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

#endif
