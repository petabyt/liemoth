// This an Ambsh/Ambashell parser, with a sort of
// "preprocessor" built in. It can be used to generate
// ASH scripts.

#include <stdio.h>
#include <string.h>
#include "main.h"

// TODO: Actual error handling

struct Memory mem;
int skipping = 0;
int inStatement = 0;

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

void writeBin(char file[], long location) {
	FILE *reader = fopen(file, "r");
	if (reader == NULL) {
		printf("# FILE %s NOT FOUND!\n", file);
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

void writeFile(char file[]) {
	FILE *reader = fopen(file, "r");
	if (reader == NULL) {
		printf("# FILE %s NOT FOUND!\n", file);
		return;
	}
	
	int c = fgetc(reader);
	while (!feof(reader)) {
		putchar((char)c);
		c = fgetc(reader);
	}

	fclose(reader);
}

// Lexer Functions (copypasted from another project)
int isChar(char a) {
	return ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || a == '_');
}

int isDec(char a) {
	return (a >= '0' && a <= '9');
}

int isHex(char a) {
	return (a >= '0' && a <= '9') || (a >= 'a' && a <= 'f') || (a >= 'A' && a <= 'F');
}

// Find a token in memory structure
int findMem(char string[]) {
	for (int i = 0; i < mem.len; i++) {
		if (!strcmp(mem.t[i].name, string)) {
			return i;
		}
	}

	return -1;
}

void defineInt(char name[], long value) {
	strcpy(mem.t[mem.len].name, name);
	mem.t[mem.len].type = INTEGER;
	mem.t[mem.len].integer = value;
	mem.len++;
}

void parseStatement(char *buffer) {
	// A simple token parser. Overkill, but flexible
	// just in case I ever need to extend it
	int len = 0;
	for (int c = 0; buffer[c] != '\0';) {
		while (buffer[c] == ' ') {
			c++;
		}

		if (buffer[c] == '\0') {
			break;
		}
		
		tokens[len].len = 0;
		if (isChar(buffer[c])) {
			while (isChar(buffer[c])) {
				tokens[len].type = TEXT;
				tokens[len].text[tokens[len].len] = buffer[c];
				tokens[len].len++;
				c++;
			}

			// Once a text token is parsed, check to see if
			// it was define'd.
			for (int i = 0; i < mem.len; i++) {
				if (!strcmp(mem.t[i].name, tokens[len].text)) {
					strcpy(tokens[len].text, mem.t[i].value);
					tokens[len].value = mem.t[i].integer;

					len++;
					continue;
				}
			}
		}

		// Quick hex parser. Not the best, but works if
		// You don't try to break it.
		tokens[len].value = 0;
		if (buffer[c] == '0' || buffer[c + 1] == 'x') {
			c += 2;
			while (isHex(buffer[c])) {
				tokens[len].type = INTEGER;
				tokens[len].value *= 16;
				if (isDec(buffer[c])) {
					tokens[len].value += buffer[c] - '0';
				} else {
					tokens[len].value += buffer[c] - 'a' + 10;
				}
				
				c++;
			}
		}
		
		while (isDec(buffer[c])) {
			tokens[len].type = INTEGER;
			tokens[len].value *= 10;
			tokens[len].value += buffer[c] - '0';
			c++;
		}

		if (buffer[c] == '"') {
			c++;
			tokens[len].type = STRING;
			while (buffer[c] != '"') {
				tokens[len].text[tokens[len].len] = buffer[c];
				tokens[len].len++;
				c++;
			}
			
			c++;
		}

		tokens[len].text[tokens[len].len] = '\0';
		len++;
	}

	// Skip all ashp commands until end is defined
	if (!strcmp(tokens[0].text, "end")) {
		inStatement--;
		if (skipping) {
			skipping--;
		}
	}

	if (skipping) {
		return;
	}

	if (!strcmp(tokens[0].text, "define")) {
		strcpy(mem.t[mem.len].name, tokens[1].text);
		strcpy(mem.t[mem.len].value, tokens[2].text);
		mem.t[mem.len].integer = tokens[2].value;
		mem.t[mem.len].type = tokens[2].type;
		mem.len++;
	} else if (!strcmp(tokens[0].text, "genUnicode")) {
		genUnicode(tokens[1].text, tokens[2].value);
	} else if (!strcmp(tokens[0].text, "writeBin")) {
		writeBin(tokens[1].text, tokens[2].value);
	} else if (!strcmp(tokens[0].text, "writeFile")) {
		writeFile(tokens[1].text);
	} else if (!strcmp(tokens[0].text, "ifdef")) {
		inStatement++;
		if (findMem(tokens[1].text) == -1) {
			skipping++;
		}
	} else if (!strcmp(tokens[0].text, "ifndef")) {
		inStatement++;
		if (findMem(tokens[1].text) != -1) {
			skipping++;
		}
	} else if (!strcmp(tokens[0].text, "ifeq")) {
		inStatement++;
		int i = findMem(tokens[1].text);
		if (mem.t[i].type == INTEGER) {
			if (mem.t[i].integer != tokens[2].value) {
				skipping++;
			}
		} else if (mem.t[i].type == STRING) {
			if (strcmp(mem.t[i].value, tokens[2].text)) {
				skipping++;
			}
		}
	}
}

int parseAmbsh(char *file) {
	char buffer[500];
	char statement[500];

	FILE *reader = fopen(file, "r");

	while (fgets(buffer, 500, reader) != NULL) {
		int c = 0;
		while (buffer[c] == '\t' || buffer[c] == '\n' || buffer[c] == ' ') {
			c++;
		}

		if (buffer[c] == '#') {
			c++;
			while (buffer[c] != '\0') {
				c++;
			}
		}

		// If it made it this far, then it is a "nothing"
		// line, and will not be parsed
		if (buffer[c] == '\0') {
			continue;
		}

		for (; buffer[c] != '\0'; c++) {
			if (buffer[c] == '[') {
				c++;
				int len = 0;
				while (buffer[c] != ']') {
					statement[len] = buffer[c];
					c++;
					len++;
				}

				statement[len] = '\0';
				parseStatement(statement);

				// Skip if newline after
				if (buffer[c + 1] == '\n') {
					c += 1;
				}
			} else if (buffer[c] == '{') {
				c++;
				int len = 0;
				while (buffer[c] != '}') {
					statement[len] = buffer[c];
					c++;
					len++;
				}

				statement[len] = '\0';

				// Skip if newline after
				if (buffer[c + 1] == '\n') {
					c += 2;
				}
				
				int i = findMem(statement);
				if (mem.t[i].type == INTEGER) {
					printf("%li", mem.t[i].integer);
				} else if (mem.t[i].type == STRING) {
					printf("%s", mem.t[i].value);
				}
			} else if (!skipping) {
				putchar(buffer[c]);
			}
		}
	}

	return 0;
}
