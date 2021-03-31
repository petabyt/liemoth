// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

enum Types {
	TEXT,
	INTEGER,
	STRING,
};

struct Token {
	char text[500];
	int len;
	int type;
	long value;
}tokens[5];

struct Memory {
	int len;
	struct T {
		char name[100];
		char value[100];
		long integer;
		int type;
	}t[100];
};

struct Memory mem;

void genUnicode(char string[], long location);
void writeBytes(short opcode[], long location);
void writeBin(char file[], long location);
void writeFile(char file[]);
int parseAmbsh(char *file);
void defineInt(char name[], long value);
