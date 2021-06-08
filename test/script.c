#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ashp/main.h"

int main(int argc, char *argv[]) {
	init();
	defineInt("MEM_LOADER", strtol(argv[1], NULL, 16));
	defineInt("P_CTRLMAN", P_CTRLMAN);
	parseAmbsh("loader.ash");
}
