#include <stdio.h>
#include <string.h>

// Default platform
#ifndef P_NAME
	#include "../platform/hero3p.h"
#endif

#include "../ashp/main.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {return -1;}
	init();
	defineInt("MEM_GPIOHACK", MEM_GPIOHACK);
	defineInt("P_CTRLMAN", P_CTRLMAN);
	defineInt("P_AUTOEXECTASK", P_AUTOEXECTASK);
	defineInt("P_BUTTONTASKA", P_BUTTONTASKA);
	defineInt("P_BUTTONTASKB", P_BUTTONTASKB);
	defineInt("P_SELBTN", P_SELBTN);
	defineInt("P_MODEBTN", P_MODEBTN);

	//defineStr("TEST", "hello, world");
	
	parseAmbsh(argv[1]);
}
