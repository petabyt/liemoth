#include <stdio.h>
#include <string.h>
#include "../ashp/main.h"

int main() {
	defineInt("MEM_LOADER", MEM_LOADER);
	defineInt("P_CTRLMAN", P_CTRLMAN);
	defineInt("FANCY", 0);
	
	parseAmbsh("loader.ash");
}
