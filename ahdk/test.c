// Quick custom hello world test.
// `make minimal FILE=test.c`

#include "ambarella.h"
#include "ahdk.h"

char *name = "Bob";
void start(int *env) {
	// &name == 240
	// should be 0xc0123...
}