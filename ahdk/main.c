// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

struct Font {
    char letter;
    char code[7][5];
};

// FONT.BIN will be loaded into this
struct Font font[100];

int line;

void ambsh_msleep();
void ambsh_printf();
void ambsh_sprintf();
int ambsh_fopen();
int ambsh_fread();
void ambsh_fclose();

// GPIO tests
int FUN_c02745f0() {
	__asm__("bl 0xc02745f0");
}

int FUN_c0276bea() {
	__asm__("bl FUN_c0276bea");
}

int getGPIO() {
	int iVar1;
	char local_24[4];
	unsigned int local_20;
	unsigned int local_1c;
	unsigned int local_18;
	//unsigned int uVar7;

	iVar1 = FUN_c02745f0("48", &local_18);
	if (iVar1 < 0) {
		return 50;
	}
	
	iVar1 = FUN_c0276bea(local_18 & 0xffff, &local_1c, &local_20, local_24);
	if ((int)(local_20 & 0xff)) {
		return 100;
	} else {
		return 200;
	}
}

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
	//fillRect(20, 20, SCREEN_WIDTH - 30, 40 + (sel * 10), 0x20);
}

void start(void *env) {
	char buffer[100];
	line = 0;
	unsigned char *param = (unsigned char*)MEM_PARAM;

	if (*param == 0) {
		ambsh_printf(env, "Loading FONT.BIN...\n");
		int file = ambsh_fopen("d:\\FONT.BIN", "r");
		ambsh_fread(font, 2737, 2737, file);
		ambsh_printf(env, "Loaded FONT.BIN result is %d\n", file);

		drawGUI();

		ambsh_sprintf(buffer, "AHDK Console. Model: %s", P_NAME);
		print(buffer);
		ambsh_sprintf(buffer, "Sprintf test = %d", 123456);
		print(buffer);
		ambsh_sprintf(buffer, "Parameter = %d", (int)(*param));
		print(buffer);
		ambsh_msleep(1000);
		drawImage(100, 70, 150, 150, "d:\\LOGO.BIN");

		//drawImage(120, 60, 150, 150);

		ambsh_msleep(10000);
	} else {
		clearScreen();
	}

	return;
}
