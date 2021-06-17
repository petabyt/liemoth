// Quick custom hello world test.
// `make minimal FILE=test.c`

#include "ambarella.h"
#include "ahdk.h"

void start(int *env) {
	printf(env, "Hello, World - 0x%x", &env);
}