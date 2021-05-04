#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ashp/main.h"

int main(int argc, char *argv[]) {
	init();
	defineInt("MEM_LOADER", MEM_LOADER);
	defineInt("P_CTRLMAN", P_CTRLMAN);
	parseAmbsh("loader.ash");
}
