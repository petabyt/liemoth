#include "ambarella.h"
#include "ahdk.h"

void start(int *env, long addr) {
	unsigned char *screen = (unsigned char*)MEM_BUFFER;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		screen[i] = 111;
	}
}