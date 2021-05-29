// Quick custom hello world test.
// `make minimal`

#include "ambarella.h"
#include "ahdk.h"

void start(int *env) {
	// Startup
	msleep(100000);

	unsigned char *screen = (unsigned char*)MEM_BUFFER;

	for (int i = 0; i < 1000; i++) {
		screen[i] = 13;
	}
}
