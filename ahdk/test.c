// Quick custom hello world test.
// `make minimal`

#include "ambarella.h"
#include "ahdk.h"

void start(int *env) {
	// Startup
	msleep(20000);

	// Hijack lu_util function, talk to kernel
	char *hijack[] = {"lu_util", "exec", "mkdir /tmp/fuse_d/HELLO"};
	lu(env, 3, hijack);
}
