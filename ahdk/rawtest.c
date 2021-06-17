// Buffer rip test, unfinished
// `make minimal FILE=rawtest.c`

#include "ambarella.h"
#include "ahdk.h"

// 10 meg
#define BUFSIZE 10000000

void start(int *env) {
	printf(env, "Hello");
	
	unsigned char *f = (unsigned char*)(0xc45f0472);
									//  0xc4592782

	FILE *file = fopen("d:/raw", "w");
	fwrite(f, 1, BUFSIZE, file);
	fclose(file);
}
