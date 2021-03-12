#include <stdio.h>
#include <string.h>
#include "../main.h"

/*
1. Power on camera
2. If you want to run the script, take out SD card.
3. Hopefully the custom message will appear, script will run
4. Put SD card back in, take pictures
*/

int main() {
	// Define MEM_NOCARD from header
	strcpy(mem.t[0].name, "MEM_NOCARD");
	mem.t[0].integer = MEM_NOCARD;
	mem.len = 1;
	
	parseAmbsh("start.ash");
}
