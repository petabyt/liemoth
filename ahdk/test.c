// Quick custom hello world test.
// `make minimal`

#include "ambarella.h"
#include "ahdk.h"

void start(int *env) {
	printf(env, "Hello");
	char *hijackExp[5] = {"ia2", "-ae", "exp", "200", "85"};
	setExp(5, hijackExp);
}
