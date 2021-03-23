#include <stdio.h>
#include <string.h>
#include "../ashp/main.h"

int main() {
	strcpy(mem.t[0].name, "MEM_LOADER");
	mem.t[0].integer = MEM_LOADER;
	strcpy(mem.t[1].name, "P_CTRLMAN");
	mem.t[1].integer = P_CTRLMAN;
	mem.len = 2;
	
	parseAmbsh("loader.ash");
}
