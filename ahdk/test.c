// Quick demonstration of custom boot stuff
// `make demo`

#include "ambarella.h"
#include "ahdk.h"

void start() {
	char buffer[50];
	int i = 0;
	while (1) {
		sprintf(buffer, "d:/Hi %d", i);
		mkdir(buffer);
		i++;
		msleep(2000);
	}
}
