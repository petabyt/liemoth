// This an Ambsh/Ambashell parser, with a sort of
// "preprocessor" built in. It can be used to generate
// ASH scripts.

#include <stdio.h>
#include <string.h>
#include "main.h"

// TODO: Actual error handling

struct Memory mem;

int writeLong(char buffer[], int length, int location) {
	long a;
	int i = 0;

	while (!((length - i) % 4)) {
		printf("writeb 0x%x 0x%x\n", location, buffer[i]);
		location++;
		i++;
	}
	
	while (i < length) {
		a = buffer[i];
		i++;
		a |= buffer[i] << 8;
		i++;
		a |= buffer[i] << 16;
		i++;
		a |= buffer[i] << 24;
		printf("writel 0x%x 0x%lx\n", location, a);
		i++;
		location += 4;
	}
}

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

// Lexer Functions
int isChar(char a) {
	return ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || a == '_');
}

int isDec(char a) {
	return (a >= '0' && a <= '9');
}

int isHex(char a) {
	return (a >= '0' && a <= '9') || (a >= 'a' && a <= 'f') || (a >= 'A' && a <= 'F');
}

void parseStatement(char *buffer) {
	// A simple token parser. Overkill, but flexible
	// just in case I ever add some other crap
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

	if (!strcmp(tokens[0].text, "define")) {
		strcpy(mem.t[mem.len].name, tokens[1].text);
		strcpy(mem.t[mem.len].value, tokens[2].text);
		mem.t[mem.len].integer = tokens[2].value;
		mem.len++;
	} else if (!strcmp(tokens[0].text, "genUnicode")) {
		genUnicode(tokens[1].text, tokens[2].value);
	} else if (!strcmp(tokens[0].text, "writeBin")) {
		writeBin(tokens[1].text, tokens[2].value);
	} else if (!strcmp(tokens[0].text, "writeFile")) {
		writeFile(tokens[1].text);
	}
}

int parseAmbsh(char *file) {
	char buffer[500];
	int len;
	
	FILE *reader = fopen(file, "r");
	int c;
	while (1)  {
		c = fgetc(reader);
		if (c == EOF) {
			break;
		}

		if (c == '#') {
			while ((char)c != '\n') {
				c = fgetc(reader);
			}
			
			continue;
		} if (c == '\t') {
			continue;
		} else if (c == '[') {
			c = fgetc(reader);
			len = 0;
			while (c != ']') {
				buffer[len] = (char)c;
				len++;
				c = fgetc(reader);

				// No end
				if (c == EOF) {
					return -1;
				}
			}

			buffer[len] = '\0';
			parseStatement(buffer);

			// Newline required after statement
			c = fgetc(reader);
			if (c != '\n') {
				return -1;
			}
		} else if (c == '{') {
			c = fgetc(reader);
			len = 0;
			while (c != '}') {
				buffer[len] = (char)c;
				len++;
				c = fgetc(reader);

				// No end
				if (c == EOF) {
					return -1;
				}
			}

			buffer[len] = '\0';
			for (int i = 0; i < mem.len; i++) {
				if (!strcmp(mem.t[i].name, buffer)) {
					printf(mem.t[i].value);
					break;
				}
			}
		} else {
			putchar((char)c);
		}
	}

	return 0;
}

// int main(int argc, char *argv[]) {
	// return parseAmbsh(argv[1]);
	// return 0;
// }
