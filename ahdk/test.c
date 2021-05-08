// Quick demonstration of custom boot stuff
// `make demo`

#include "ambarella.h"
#include "ahdk.h"
#include "gopro.h"

unsigned char screenBuf[1000];

#if 0
// NOTE: Not working
void setPixel(int x, int y) {
	screenBuf[y * SCREEN_WIDTH + (x >> 3)] |= 1 << (x % 8);
}
#endif

void start() {
	for (int i = 0; i < 1000; i++) {
		screenBuf[i] = 0;
	}

	screenBuf[0] = 255;

	char buffer[20];
	int i = 0;
	
	while (1) {
		sprintf(buffer, "d:/F/F%d", i);

		FILE *f = fopen(buffer, "r");
		fread(&screenBuf, 1000, 1000, f);
		fclose(f);

		showBuffer(screenBuf);
		
		msleep(250);
		if (i == 25) {
			i = 0;
		} else {
			i++;
		}
	}
}
