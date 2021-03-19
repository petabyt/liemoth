#include <stdio.h>
#include <string.h>
#include "../main.h"

int main() {
	strcpy(mem.t[0].name, "MEM_LOADER");
	mem.t[0].integer = MEM_LOADER;
	mem.len = 1;
	
	parseAmbsh("loader.ash");
}
