#include <stdio.h>
#include <string.h>
#include "../ashp/main.h"

int main(int argc, char *argv[]) {
	// Define MEM_NOCARD from header
	#ifndef NOSCREEN
		strcpy(mem.t[0].name, "MEM_TEXT");
		mem.t[0].integer = MEM_NOCARD;
	#endif
	strcpy(mem.t[1].name, "P_CTRLMAN");
	mem.t[1].integer = P_CTRLMAN;
	mem.len = 2;
	
	parseAmbsh(argv[1]);
}
