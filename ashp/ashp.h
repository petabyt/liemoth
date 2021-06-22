#ifndef MAIN_H
#define MAIN_H

#define MAX_LINE 1024

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

extern struct Memory *mem;

#define ashp_parse parseAmbsh
#define ashp_defint defineInt
#define ashp_defstr defineStr

int parseAmbsh(char *file);
void init();

void genUnicode(char string[], long location);
void writeBytes(short opcode[], long location);
void writeBin(char file[], long location);
void writeFile(char file[]);

void defineInt(char name[], long value);
void defineStr(char name[], char value[]);

#endif
