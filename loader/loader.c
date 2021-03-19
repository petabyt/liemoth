#include <stdio.h>
#include <string.h>
#include "../ashp/main.h"

int main() {
	// Define MEM_NOCARD from header
	strcpy(mem.t[0].name, "MEM_NOCARD");
	mem.t[0].integer = MEM_NOCARD;
	mem.len = 1;
	
	parseAmbsh("start.ash");
}
