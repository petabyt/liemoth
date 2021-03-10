#include <stdio.h>
#include "../gen.h"

int main() {
	// Inject assembly into cardmgr command
	writeBin("loader.o", MEM_LOADER);
	
	//writeBin("main.o", MEM_MAIN);
	puts("touch fart");
	puts("cardmgr >> fart");	
}
