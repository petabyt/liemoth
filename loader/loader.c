#include <stdio.h>
#include <string.h>
#include "../ashp/main.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {return -1;}
	#ifdef MEM_GPIOHACK
		defineInt("MEM_GPIOHACK", MEM_GPIOHACK);
	#endif
	defineInt("P_CTRLMAN", P_CTRLMAN);

	defineStr("TEST", "hello, world");
	
	parseAmbsh(argv[1]);
}
