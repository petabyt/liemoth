// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

#include "../ashp/main.h"

int main() {
	defineInt("MEM_LOADER", MEM_LOADER);
	defineInt("P_CTRLMAN", P_CTRLMAN);
	//defineInt("FANCY", 0);
	
	parseAmbsh("loader.ash");
}
