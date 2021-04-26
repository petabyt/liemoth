#ifndef __MAIN
#define __MAIN

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
};

struct Memory {
	int len;
	struct T {
		char name[100];
		char value[1024];
		long integer;
		int type;
	}t[100];
};

extern struct Memory mem;

void genUnicode(char string[], long location);
void writeBytes(short opcode[], long location);
void writeBin(char file[], long location);
void writeFile(char file[]);
int parseAmbsh(char *file);
void defineInt(char name[], long value);
void defineStr(char name[], char value[]);

#endif
