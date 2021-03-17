#include <stdio.h>
#include "../main.h"

int main() {
	// Inject assembly into cardmgr command
	writeBin("loader.o", MEM_LOADER);
	writeBin("main.o", MEM_MAIN);
	puts("writeb 0xc012d5ac 0x0");
	puts("cardmgr");
	puts("suspend 18");
	puts("sleep 5");
	puts("writeb 0xc012d5ac 0x1");
	puts("cardmgr");
	puts("resume 18");
}
