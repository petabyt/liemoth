// Quick custom hello world test.
// `make minimal`

#include "ambarella.h"
#include "ahdk.h"

#define BUFSIZE 10000000

void start(int *env) {
	printf(env, "Hello");
	
	unsigned char *f = (unsigned char*)(0xc45f0472);
									//  0xc4592782


	FILE *file = fopen("d:/raw", "w");
	fwrite(f, 1, BUFSIZE, file);
	fclose(file);
}
