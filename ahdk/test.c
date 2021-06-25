// Quick custom hello world test.
// `make minimal file=test.c`

#include "ambarella.h"
#include "ahdk.h"

void start(int *env) {
	printf(env, "Hello, World");
}