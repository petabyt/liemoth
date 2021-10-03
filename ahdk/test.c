// Quick custom hello world test.
// `make minimal file=test.c`

#include "stdlib.h"
#include "ambarella.h"
#include "ahdk.h"

void start(int *env, int argc, char *argv[]) {
	// Print arguments to cardmgr
	for (int i = 0; i < argc; i++) {
		printf(env, "%s\n", argv[i]);
	}

	printf(env, "Hello, World\n");
}