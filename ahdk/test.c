// Quick custom hello world test.
// `make minimal file=test.c`

#include "ambarella.h"
#include "ahdk.h"

void start(int *env, int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		printf(env, "%s\n", argv[i]);
	}
}