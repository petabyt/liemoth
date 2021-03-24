// Get FILE object to be compatible with emulator
#include <stdio.h>

#include "header.h"
#include "ambarella.h"

int line;
int sel;
struct Font font[100];
char buffer[100];

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

void print(char *string) {
	printString(20, 20 + (line * 14), string, TEXT_COL);
	line++;
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
int gpioStat(int id) {
	int b, c, d;
	ambsh_gpio(id, &b, &c, &d);
	return !(c & 0xff);
}

int waitButton(int id) {
	while (!gpioStat(id)) {
		ambsh_msleep(1);
	}

	while (gpioStat(id)) {
		ambsh_msleep(1);
	}
}

int getButton() {
	// Check for button
	int id;
	if (gpioStat(P_SELBTN)) {
		id = P_SELBTN;
	} else if (gpioStat(P_MODEBTN)) {
		id = P_MODEBTN;
	} else {
		return 0;
	}

	// Wait until button is up
	while (gpioStat(id)) {
		ambsh_msleep(1);
	}

	return id;
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
		print("Press select button to exit.");
		drawImage(140, 50, 150, 150, "d:\\ahdk\\logo.bin");
		waitButton(P_SELBTN);
		break;
	}

	drawGUI();
	drawMenu();
	return 0;
}

void start(int *env) {
	line = 0;
	sel = 0;
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
		int r = getButton();
		if (r == P_SELBTN) {
			if (menuClick()) {
				clearScreen();
				return;
			}
		} else if (r == P_MODEBTN) {
			if (sel == MENU_ITEMS - 1) {
				sel = 0;
			} else {
				sel++;
			}

			drawGUI();
			drawMenu();	
		}
		
		ambsh_msleep(10);
	}

	return;
}
