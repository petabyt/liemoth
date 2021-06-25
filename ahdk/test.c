// Quick custom hello world test.
// `make minimal file=test.c`

#include "ambarella.h"
#include "ahdk.h"

char *name = "Bob";
void start(int *env) {
	printf(env, "Hello, World");
}