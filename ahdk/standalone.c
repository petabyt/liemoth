#include "ambarella.h"
#include "ahdk.h"

// linker vars
extern long DATA_START;
extern long DATA_END;

char *name = "Bob";
char *name_ = "Bobie";

void start(int *env, long addr) {
	// Get absolule data address
	long *dataStart = (long*)((long)&DATA_START + (long)addr);

	// Add to all the 32 bit addresses
	#define DATASIZE ((long)(&DATA_END) - (long)(&DATA_START))
	for (int i = 0; i < DATASIZE / 2; i++) {
		dataStart[i] += addr;
	}

	printf(env, "%s\n", name);
	printf(env, "%s\n", name_);
}