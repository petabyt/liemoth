// Quick demonstration of custom boot stuff
// `make demo`

#include "ambarella.h"
#include "ahdk.h"
#include "gopro.h"

unsigned char screenBuf[1000];

void setPixel(int x, int y) {
	screenBuf[y * SCREEN_WIDTH + (x >> 3)] |= 1 << (x % 8);
}

void start(int *env) {
	for (int i = 0; i < 1000; i++) {
		screenBuf[i] = 0;
	}
	
	FILE *f = fopen("d:/LOGO.BIN", "r");
	fread(&screenBuf, 1000, 1000, f);
	showBuffer(screenBuf);
}
