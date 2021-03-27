#include "header.h"
#include "ambarella.h"

int line;
int sel;
struct Font font[100];
char buffer[100];

int shutterCode[] = {1, 24, 85, 126, 178, 252, 378};

void notify() {
	drawBox(10, 10, 200, 40, MENU_COL);
	printString(20, 20, buffer, TEXT_COL);
}

void countdown(int sec) {
	for (; sec != 0; sec--) {
		ambsh_sprintf(buffer, "Waiting %d...", sec);
		notify();
		ambsh_msleep(1000);
	}
}

void print(char *string) {
	printString(20, 20 + (line * 14), string, TEXT_COL);
	line++;
}

// Draw main UI box
void drawGUI() {
	drawBox(10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 40, MENU_COL);
}

void drawMenu(struct MenuItem menu[]) {
	// Menu selector
	int y = 0;
	for (int i = 0; menu[i].text != 0; i++) {
		int col;
		if (sel == i) {
			col = BTN_DOWN_COL;
		} else {
			col = BTN_UP_COL;
		}

		fillRect(20, 20 + y, SCREEN_WIDTH - 30, 40 + y, col);
		printString(26, 26 + y, menu[i].text, TEXT_COL);

		// Print
		if (menu[i].type == SELECT) {
			printString(SCREEN_WIDTH - 120, 26 + y, menu[i].info->elements[menu[i].info->s], TEXT_COL);
		}

		y += 22;
	}
}

// Return GPIO status
int gpioStat(int id) {
	int b, c, d;
	ambsh_gpio(id, &b, &c, &d);
	return !(c & 0xff);
}

// Wait until a button is pressed
int waitButton(int id) {
	while (!gpioStat(id)) {
		ambsh_msleep(1);
	}

	while (gpioStat(id)) {
		ambsh_msleep(1);
	}
}

// Check for button
int getButton() {
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

// This interprets and runs a menu from the structure.
int runMenu(struct MenuItem menu[]) {
	drawGUI();
	drawMenu(menu);
	while (1) {
		int r = getButton();
		if (r == P_SELBTN) {
			if (menu[sel].type == ACTION) {
				drawGUI();
				if (menu[sel].action() != 0) {
					return 1;
				}
			// NOTE: This is for SELECT
			} else {
				while (1) {
					r = getButton();
					if (r == P_MODEBTN) {
						menu[sel].info->s++;
						if (menu[sel].info->elements[menu[sel].info->s] == 0) {
							menu[sel].info->s = 0;
						}

						drawGUI();
						drawMenu(menu);
					} else if (r == P_SELBTN) {
						break;
					}
					
					ambsh_msleep(1);
				}
			}
		} else if (r == P_MODEBTN) {
			if (menu[sel + 1].text == 0) {
				sel = 0;
			} else {
				sel++;
			}
		} else {
			continue;
		}

		drawGUI();
		drawMenu(menu);
		
		ambsh_msleep(10);
	}
}

int ahdkInfo() {
	line = 0;
	ambsh_sprintf(buffer, "AHDK Menu: Model: %s", P_NAME);
	print(buffer);
	print("Press select button to exit.");
	drawImage(140, 50, 150, 150, "d:/ahdk/logo.bin");
	waitButton(P_SELBTN);
	return 0;
}

void writeAmbsh(char *buffer) {
	FILE *file = ambsh_fopen("d:/ahdk/a.ash", "w");
	ambsh_fwrite(buffer, 1, strlen(buffer), file);
	ambsh_fclose(file);
}

int exitMenu() {
	return 1;
}

struct ItemInfo selectISO = {
	0, {"200", "800", "1600", "3200", "6400", 0}
};

struct ItemInfo selectExp = {
	0, {"8", "7", "6", "5", "4", "3", "2", "1", 0}
};

struct MenuItem expMenu[] = {
	{"ISO", 0, SELECT, &selectISO},
	{"Exp", 0, SELECT, &selectExp},
	{"Exit", exitMenu, ACTION, 0},
	{0}
};

int expSetting() {
	runMenu(expMenu);
	return 0;
}

struct MenuItem mainMenu[] = {
	{"Exit", exitMenu, ACTION, 0},
	{"Manual", expSetting, ACTION, 0},
	{"About AHDK", ahdkInfo, ACTION, 0},
	{0}
};

void start(int *env) {
	ambsh_printf(env, "AHDK Started");
	line = 0;
	sel = 0;

	// Copy font into memory
	FILE *file = ambsh_fopen("d:/ahdk/font.bin", "r");
	if (!file) {ambsh_printf(env, "No font"); return;}
	ambsh_fread(font, 2737, 2737, file);
	ambsh_fclose(file);

	runMenu(mainMenu);
	clearScreen();
	countdown(3);
}
