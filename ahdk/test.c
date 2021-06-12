// Quick custom hello world test.
// `make minimal`

#include "ambarella.h"
#include "ahdk.h"

void start(int *env) {
	printf(env, "Hello");
	
	char *f = (char*)(0xc3f180eb + 100000);
	while (1) {
		for (int i = 0; i < 10000; i++) {
			f[i] = 1;
		} 
	}
}
