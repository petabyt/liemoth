#include <stdio.h>
#include "../platform/activeondx.h"

// Generate a unicode string at address.
// (seperated by spaces)
void genUnicode(char string[], long location) {
	for (int c = 0; string[c] != '\0'; c++) {
		printf("writeb 0x%lx 0x%x\n", location, string[c]);
		location++;
		printf("writeb 0x%lx 0x0\n", location);
		location++;
	}

	printf("writeb 0x%lx 0x0\n", location);
	printf("writeb 0x%lx 0x0\n", location + 1);
}

void writeBytes(short opcode[], long location) {
	for (int c = 0; opcode[c] != -1; c++) {
		printf("writeb 0x%lx 0x%x\n", location, opcode[c]);
		location++;
	}
}

void writeBin(char file[], long location) {
	FILE *reader = fopen(file, "r");
	if (reader == NULL) {
		return;
	}
	
	int c = fgetc(reader);
	while (!feof(reader)) {
		printf("writeb 0x%lx 0x%x\n", location, (unsigned char)c);
		location++;
		c = fgetc(reader);
	}

	fclose(reader);
}

int main() {
	// Inject assembly into cardmgr command
	writeBin("test.o", MEM_CARDMGR);
	printf("cardmgr\n");
}
