// Buffer rip test, unfinished
// `make minimal FILE=rawtest.c`

#include "ambarella.h"
#include "ahdk.h"

int raw();

// logger
// 0xc026cf60

void start(int *env) {
	char *a = (char*)MEM_PARAM;
	printf(env, "%d\n", *a);
}
