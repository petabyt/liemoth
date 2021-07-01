#include "ambarella.h"
#include "ahdk.h"

void start(int *env, long addr) {
	unsigned char *b = (unsigned char*)MEM_BUFFER;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		b[i] = COL_BLUE;
	}

	msleep(3000);
}
