// Ambashell preprocessor. It can be used to generate
// ASH scripts.
// I could use a general purpose preprocessor, but this
// is spiffier.
// `cc *.c; ./a.out test.ash`

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ashp.h"

struct Memory *mem;
struct Token tokens[6];
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

// Find a token in mem->ry structure
int findMem(char string[]) {
	for (int i = 0; i < mem->len; i++) {
		if (!strcmp(mem->t[i].name, string)) {
			return i;
		}
	}

	return -1;
}

void defineInt(char name[], long value) {
	strcpy(mem->t[mem->len].name, name);
	mem->t[mem->len].type = INTEGER;
	mem->t[mem->len].integer = value;
	mem->len++;
}

void defineStr(char name[], char value[]) {
	strcpy(mem->t[mem->len].name, name);
	strcpy(mem->t[mem->len].value, value);
	mem->t[mem->len].type = STRING;
	mem->len++;
}

void parseStatement(char *buffer) {
	// Skip all ashp commands until end is defined
	if (!strcmp(buffer, "end")) {
		inStatement--;
		if (skipping) {
			skipping--;
		}
	}

	if (skipping) {
		return;
	}

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
		tokens[len].value = 0;
		
		if (isChar(buffer[c])) {
			while (isChar(buffer[c])) {
				tokens[len].type = TEXT;
				tokens[len].text[tokens[len].len] = buffer[c];
				tokens[len].len++;
				c++;
			}

			tokens[len].text[tokens[len].len] = '\0';

			// Once a text token is parsed, check to see if
			// it was define'd.
			for (int i = 0; i < mem->len; i++) {
				if (!strcmp(mem->t[i].name, tokens[len].text)) {
					//strcpy(tokens[len].text, mem->t[i].value);
					tokens[len].value = mem->t[i].integer;
					tokens[len].type = INTEGER;
					continue;
				}
			}
		}

		// Quick hex parser. Not the best, but works if
		// You don't try to break it.
		if (buffer[c] == '0' && buffer[c + 1] == 'x') {
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
				if (buffer[c] == '\\' && buffer[c + 1] == 'n') {
					tokens[len].text[tokens[len].len] = '\n';
					tokens[len].len++;
					c += 2;
					continue;
				}
				
				tokens[len].text[tokens[len].len] = buffer[c];
				tokens[len].len++;
				c++;
			}
			
			c++;
			tokens[len].text[tokens[len].len] = '\0';
		}

		len++;
	}

	if (!strcmp(tokens[0].text, "define")) {
		strcpy(mem->t[mem->len].name, tokens[1].text);
		strcpy(mem->t[mem->len].value, tokens[2].text);
		mem->t[mem->len].integer = tokens[2].value;
		mem->t[mem->len].type = tokens[2].type;
		mem->len++;
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
		if (mem->t[i].type == INTEGER) {
			if (mem->t[i].integer != tokens[2].value) {
				skipping++;
			}
		} else if (mem->t[i].type == STRING) {
			if (strcmp(mem->t[i].value, tokens[2].text)) {
				skipping++;
			}
		}
	}
}

void init() {
	mem = malloc(sizeof(struct Memory));
}

int parseAmbsh(char *file) {

	char buffer[MAX_LINE];
	char statement[MAX_LINE];
	
	FILE *reader = fopen(file, "r");
	while (fgets(buffer, MAX_LINE, reader) != NULL) {
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

				if (skipping) {
					break;
				}

				statement[len] = '\0';

				int i = findMem(statement);
				if (i == -1) {
					puts("# NO DEFINITION FOUND");
					break;
				}
				
				if (mem->t[i].type == INTEGER) {
					printf("%li", mem->t[i].integer);
				} else if (mem->t[i].type == STRING) {
					printf("%s", mem->t[i].value);
				}
			} else if (!skipping) {
				putchar(buffer[c]);
			}
		}
	}

	// Sometimes Ambsh parser
	// needs extra newlines
	puts("\n");

	return 0;
}
