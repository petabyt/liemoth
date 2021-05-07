// Quick demonstration of custom boot stuff
// `make demo`

#include "ambarella.h"
#include "ahdk.h"
#include "gopro.h"

int FUN_c0219d3a();

void start(int *env) {
	char buf[100];
	sprintf(buf, "SPRINTF%d", 1234567);
	fpstring(buf, 0, 1);
}
