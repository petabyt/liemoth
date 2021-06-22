// Quick custom hello world test.
// `make minimal FILE=test.c`

#include "ambarella.h"
#include "ahdk.h"

void start(int *env) {
	printf(env, "fartsnstuff");
	int *a;
	malloc(1, 400, &a);
	printf(env, "%d", &a);
}