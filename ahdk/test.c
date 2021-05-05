// Quick demonstration of custom boot stuff
// `make demo`

#include "ambarella.h"
#include "ahdk.h"

#ifdef GOPRO
	#include "gopro.h"
#endif

void start(int *env) {
	for (int i = 0; i < 10; i++) {
		printf(env, "Test demo written in C\n");
	}
}
