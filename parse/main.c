#include <stdio.h>

int isChar(char a) {
	return ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || a == '_');
}

int isDec(char a) {
	return (a >= '0' && a <= '9');
}

int isHex(char a) {
	return (a >= '0' && a <= '9') || (a >= 'a' && a <= 'f') || (a >= 'A' && a <= 'F');
}

enum TokType {
	TEXT = 0,
	INTEGER = 1
};

struct Token {
	char text[500];
	int length;
	int type;
}token;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		puts("No arg");
		return -1;
	}
	
	FILE *reader = fopen(argv[1], "r");
	char buffer[500];
	while (fgets(buffer, 500, reader) != NULL) {
		for (int c = 0; buffer[c] != '\0'; c++) {
			token.length = 0;
			if (buffer[c] == '#') {
				while (buffer[c] != '\0') {
					c++;
				}
				
				continue;
			}
			
			while (buffer[c] == '\n' || buffer[c] == '\t') {
				c++;
			}

			if (isChar(buffer[c])) {
				token.type = TEXT;
				while (isChar(buffer[c])) {
					token.text[token.length] = buffer[c];
					token.length++;
					c++;
				}
			} else {
				token.type = buffer[c];
				c++;
			}

			token.text[token.length] = '\0';

			puts(token.text);
		}
	}
}
