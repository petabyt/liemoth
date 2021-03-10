// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

void genUnicode(char string[], long location);
void writeBytes(short opcode[], long location);
void writeBin(char file[], long location);
void writeFile(char file[]);
