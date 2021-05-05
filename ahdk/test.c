// Quick demonstration of custom boot stuff
// `make demo`

#include "ambarella.h"
#include "ahdk.h"
#include "gopro.h"

void start(int *env) {
	printf(env, "Hey, I'm a GoPro Hero 3+!");
}
