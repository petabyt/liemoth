#include <stdio.h>
#include <string.h>
#include "../ashp/main.h"

int main() {
	strcpy(mem.t[0].name, "MEM_LOADER");
	mem.t[0].integer = MEM_LOADER;
	mem.t[0].type = INTEGER;
	
	strcpy(mem.t[1].name, "P_CTRLMAN");
	mem.t[1].integer = P_CTRLMAN;
	mem.t[1].type = INTEGER;
	mem.len = 2;
	
	parseAmbsh("loader.ash");
}
