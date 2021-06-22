#include <stdio.h>
#include <string.h>
#include "ashp.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		puts("No file.");
		return -1;
	}

	init();
	int r = parseAmbsh(argv[1]);
	if (r < 0) {
		puts("Error parsing.");
	}
}
