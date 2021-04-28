// Screen/graphics related functions
#include "header.h"
#include "ambarella.h"

extern struct Font font[100];

// Needs magic numbers...
void drawPixel(int x, int y, unsigned char col) {
	unsigned char *screen = (unsigned char*)MEM_BUFFER;
	x += 5; // 1?
	y += 20; // 17?
	screen[x * SCREEN_HEIGHT - y] = col;
}

void clearScreen() {
	unsigned char *screen = (unsigned char*)MEM_BUFFER;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		screen[i] = 111;
	}
}


void fillRect(int x, int y, int x1, int y1, int col) {
	for (int tx = x; tx < x1; tx++) {
		for (int ty = y; ty < y1; ty++) {
			drawPixel(tx, ty, col);
		}
	}
}

void drawBox(int x, int y, int x1, int y1, int col) {
	fillRect(x, y, x1, y1, col);
	
	// Horizontal lines
	for (int i = 10; i < x1; i++) {
		drawPixel(i, y, 1);
		drawPixel(i, y1, 1);
	}

	// Vertical lines
	for (int i = 10; i < y1; i++) {
		drawPixel(x, i, 1);
		drawPixel(x1, i, 1);
	}
}

// https://github.com/petabyt/font/
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

				// Dynamic width character spacing
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
		int length = printChar(cx, cy, string[c], color);
		if (string[c] == ' ') {
			length = 5;
		}

		cx += length + 3;
	}

	return cy;
}

// Use https://codepen.io/Pufflegamerz/pen/abBgLeG?editors=1010
// To convert typical images to AHDK image.
void drawImage(int x, int y, int width, int height, char image[]) {
	width += x;
	height += y;

	FILE *file = fopen(image, "r");
	if (!file) {
		return;
	}

	char c;
	int i = 0;
	for (; y < height; y++) {
		for (int tx = x; tx < width; tx++) {
			if (!fread(&c, 1, 1, file)) {
				return;
			}
			
			drawPixel(tx, y, c);
			i++;
		}
	}

	fclose(file);
}
