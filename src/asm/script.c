#include <stdio.h>
#include "../main.h"

int main() {
	// Inject assembly into cardmgr command
	puts("touch log");
	writeBin("loader.o", MEM_LOADER);
	puts("writeb 0xc012d5ac 0x0"); // main
	puts("suspend 18");
	puts("cardmgr >> log");
	puts("writeb 0xc012d5ac 0x1"); // clear screen
	puts("cardmgr");
	puts("resume 18");
}
