// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

#include "../ashp/main.h"

int main(int argc, char *argv[]) {
	init();

	// Send flags into preprocessor
	for (int i = 1; i < argc; i++) {
		defineInt(argv[i], 1);
	}
	
	defineInt("MEM_LOADER", MEM_LOADER);
	defineInt("P_CTRLMAN", P_CTRLMAN);
	
	parseAmbsh("loader.ash");
}
