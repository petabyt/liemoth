#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ashp/main.h"

int main(int argc, char *argv[]) {
	strcpy(mem.t[0].name, "MEM_LOADER");
	mem.t[0].integer = strtol(argv[1], NULL, 16);
	mem.len = 1;
	
	parseAmbsh("loader.ash");
}
