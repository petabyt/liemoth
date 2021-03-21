// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

#include "header.h"
#include "ambarella.h"

struct Font {
    char letter;
    char code[7][5];
};

struct Font font[100];
char buffer[100];
int line;
int sel;

// Screen weird, needs magic numbers
void drawPixel(int x, int y, unsigned char col) {
	unsigned char *screen = (unsigned char*)MEM_BUFFER;
	y += 20;
	x += 5;
	screen[x * SCREEN_HEIGHT - y] = col;
}

void fillRect(int x, int y, int x1, int y1, int col) {
	for (int tx = x; tx < x1; tx++) {
		for (int ty = y; ty < y1; ty++) {
			drawPixel(tx, ty, col);
		}
	}
}

void clearScreen() {
	unsigned char *screen = (unsigned char*)MEM_BUFFER;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		screen[i] = 0xff;
	}
}

// From https://github.com/petabyt/font/
int printChar(int x, int y, char c, char color) {
	int match = 0;
	for (int l = 0; l < (int)(sizeof(font) / sizeof(font[0])); l++) {
		if (font[l].letter == c) {
			match = l;
			break;
		}
	}

	// Loop through 7 high 5 wide monochrome font
	int maxLength = 0;
	for (int py = 0; py < 7; py++) {
		for (int px = 0; px < 5; px++) {
			if (font[match].code[py][px] == '#') {
				drawPixel(x + px, y + py, color);

				// Dynamix width character spacing
				if (px > maxLength) {
					maxLength = px;
				}
			}
		}
	}

	return maxLength;
}

int printString(int x, int y, char *string, char color) {
	int cx = x;
	int cy = y;

	for (int c = 0; string[c] != '\0'; c++) {
		// Text wrap after space
		if (cx + 50 > SCREEN_WIDTH && string[c] == ' ') {
			cx = x;
			cy += 5 + 4;
			c++;
		}

		int length = printChar(cx, cy, string[c], color);

		if (string[c] == ' ') {
			length = 5;
		}

		cx += length + 3;
	}

	return cy;
}

void print(char *string) {
	printString(20, 20 + (line * 14), string, 0x1);
	line++;
}

// Use https://codepen.io/Pufflegamerz/pen/abBgLeG?editors=1010
// To convert typical images to AHDK image.
void drawImage(int x, int y, int width, int height, char image[]) {
	width += x;
	height += y;
	
	char c;
	int file = ambsh_fopen(image, "r");
	int i = 0;

	for (;y < height; y++) {
		for (int tx = x; tx < width; tx++) {
			if (!ambsh_fread(&c, 1, 1, file)) {
				return;
			}
			
			drawPixel(tx, y, c);
			i++;
		}
	}
}

void drawGUI() {
	// Draw main box
	fillRect(10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 40, 0x5d);
		
	// Horizontal lines
	for (int i = 10; i < SCREEN_WIDTH - 20; i++) {
		drawPixel(i, 10, 0x1);
		drawPixel(i, 215, 0x1);
	}

	// Vertical lines
	for (int i = 10; i < SCREEN_HEIGHT - 40; i++) {
		drawPixel(10, i, 0x1);
		drawPixel(300, i, 0x1);
	}

	// Draw selector box
	fillRect(20, 20 + (sel * 22), SCREEN_WIDTH - 30, 40 + (sel * 22), 0x20);
}

// GPIO tests
int ambsh_gpio();

int keyget(int *env, char key[]) {
	char *arg[] = {"gpio", key};
	int a = ambsh_gpio(env, 2, arg);
	if (a == 0) {
		return 1;
	} else {
		return 0;
	}
}


void start(int *env) {
	unsigned char *param = (unsigned char*)MEM_PARAM;

	//struct Ambsh_cardstat status;
	//int r = gpiofoo('d' - 'a', &status);
	//int r = foo(0, 1);

	line = 0;
	sel = 0;
	if (*param == 0) {
		int file = ambsh_fopen("d:\\FONT.BIN", "r");
		ambsh_fread(font, 2737, 2737, file);

		drawGUI();
		ambsh_msleep(1000);
		
		while (1) {
			if (keyget(env, "48")) {
				if (sel == 7) {
					sel = 0;
				} else {
					sel++;
				}
				
				drawGUI();
			}
			
			ambsh_msleep(100);
		}

		//ambsh_msleep(20000);
		
	} else {
		clearScreen();
	}

	return;
}
