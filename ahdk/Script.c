// This file compiles the ashp loader
// script and sends it into stdout, which
// is routed into the final autoexec.ash.

#include "../ashp/ashp.h"

int main(int argc, char *argv[]) {
	init();

	// Send argv flags into preprocessor
	for (int i = 1; i < argc; i++) {
		defineInt(argv[i], 1);
	}

	#ifdef MEM_PARAM
		defineInt("MEM_PARAM", MEM_PARAM);
	#endif

	#ifdef MEM_TRIGGER
		defineInt("MEM_TRIGGER", MEM_TRIGGER);
	#endif

	defineInt("MEM_LOADER", MEM_LOADER);
	defineInt("P_CTRLMAN", P_CTRLMAN);
	
	parseAmbsh("Loader.ash");
}
