// Get FILE object to be compatible with emulator
#include <stdio.h>

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

char *menu[] = {
	"Resume to OS",
	"AHDK Info",
	"Set Exposure",
	"Set ISO"
};

#define MENU_ITEMS (int)(sizeof(menu) / sizeof(menu[0]))

// struct Menu {
	// char *text;
	// void (*action)(int *env);
// };

void fillRect(int x, int y, int x1, int y1, int col) {
	for (int tx = x; tx < x1; tx++) {
		for (int ty = y; ty < y1; ty++) {
			drawPixel(tx, ty, col);
		}
	}
}

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

void print(char *string) {
	printString(20, 20 + (line * 14), string, TEXT_COL);
	line++;
}

// Use https://codepen.io/Pufflegamerz/pen/abBgLeG?editors=1010
// To convert typical images to AHDK image.
void drawImage(int x, int y, int width, int height, char image[]) {
	width += x;
	height += y;

	FILE *file = ambsh_fopen(image, "r");
	if (!file) {
		return;
	}

	char c;
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

// Draw main UI box
void drawGUI() {
	fillRect(10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 40, MENU_COL);
		
	// Horizontal lines
	for (int i = 10; i < SCREEN_WIDTH - 20; i++) {
		drawPixel(i, 10, 1);
		drawPixel(i, 215, 1);
	}

	// Vertical lines
	for (int i = 10; i < SCREEN_HEIGHT - 40; i++) {
		drawPixel(10, i, 1);
		drawPixel(300, i, 1);
	}
}

void drawMenu() {
	// Menu selector
	int y = 0;
	for (int i = 0; i < MENU_ITEMS; i++) {
		int col;
		if (sel == i) {
			col = BTN_DOWN_COL;
		} else {
			col = BTN_UP_COL;
		}

		fillRect(20, 20 + y, SCREEN_WIDTH - 30, 40 + y, col);
		printString(26, 26 + y, menu[i], TEXT_COL);
		y += 22;
	}
}

// Return GPIO status
int getButton(int id) {
	int b, c, d;
	ambsh_gpio(id, &b, &c, &d);
	return !(c & 0xff);
}

int menuClick() {
	line = 0;
	drawGUI();
	switch (sel) {
	case 0:
		return 1;
	case 1:
		ambsh_sprintf(buffer, "AHDK Console. Model: %s", P_NAME);
		print(buffer);
		drawImage(140, 50, 150, 150, "d:\\ahdk\\logo.bin");
		print("Press select button to exit.");
		while (!getButton(P_SELBTN)) {
			ambsh_msleep(UI_WAIT);
		}

		break;
	}

	drawGUI();
	drawMenu();
	return 0;
}

void start(int *env, int param) {
	line = 0;
	sel = 0;
	if (param == 0) {
		FILE *file = ambsh_fopen("d:/ahdk/font.bin", "r");
		if (!file) {
			ambsh_printf(env, "Bad File");
			return;
		}
		
		ambsh_fread(font, 2737, 2737, file);
		ambsh_fclose(file);

		drawGUI();
		drawMenu();

		while (1) {
			if (getButton(P_SELBTN)) {
				ambsh_msleep(UI_WAIT);		
				if (menuClick()) {
					return;
				}
			} else if (getButton(P_MODEBTN)) {
				if (sel == MENU_ITEMS - 1) {
					sel = 0;
				} else {
					sel++;
					ambsh_msleep(UI_WAIT);
				}

				drawGUI();
				drawMenu();
			}
			
			ambsh_msleep(100);
		}

		//ambsh_msleep(20000);
		
	} else {
		clearScreen();
	}

	return;
}
