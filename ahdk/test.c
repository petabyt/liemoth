// Quick demonstration of custom boot stuff
// `make demo`

#include "ambarella.h"
#include "ahdk.h"

void start() {
	// Fill half the screen
	unsigned char *screen = (unsigned char*)MEM_BUFFER;
	for (int i = 0; i < (SCREEN_WIDTH / 2) * SCREEN_HEIGHT; i++) {
		screen[i] = COL_BLUE;
	}

	// Halt
	while (1);
}
