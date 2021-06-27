// Quick custom hello world test.
// `make minimal FILE=test.c`

#include "ambarella.h"
#include "ahdk.h"

char *name = "Bob";
void start(int *env, long addr) {
	// Linker troubles
	char *name2 = (char*)(addr + (long)name);
	printf(env, "%s\n", name2);
}