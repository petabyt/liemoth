#include "ambarella.h"
#include "ahdk.h"

void start(int *env, long addr) {
	// A simple visual memory dumper
	unsigned char *f = (unsigned char*)0xc0000000;
	unsigned char *b = (unsigned char*)MEM_BUFFER;
	for (int i = 0; i < 2000; i++) {
		for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
			b[i] = *f;
			if (*f == 255) {
				b[i] = 254;
			}
			f++;
		}

		char buf[15] = {0};
		sprintf(buf, "%x\n", f);
		FILE *fd = fopen("d:/f", "w");
		fwrite(buf, 1, 14, fd);
		fclose(fd);
		

		msleep(70);
	}
}
