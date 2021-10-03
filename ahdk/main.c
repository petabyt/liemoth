#include "stdlib.h"
#include "ambarella.h"
#include "ahdk.h"
#include "apps.h"

// Copy the screen before writing, and copy
// it back after. Allocs 80k memory.
#define COPYSCREEN

// Global env
int *envg;

// For some reason, global ints with preset values aren't working.
// I don't care, so these are set to zero in main().
int line;
int sel;

struct Font font[100];

// General purpose buffer
char buffer[100];

// Run a command on linux
void runLinux(char command[]) {
	char *hijackLu[] = {"lu_util", "exec", command};
	lu(envg, 3, hijackLu);
}

// Return GPIO status
// May be platform specific.
int gpioStat(int id) {
	int b, c, d;
	gpio(id, &b, &c, &d);
	b = (c & 0xff);

	// On Activeon DX, Rec btn is opposite?
	// 1 for up, 0 for down.
	if (id == P_RECBTN) {
		return b;
	}
	
	return !b;
}

void notify() {
	drawBox(10, 10, 200, 40, MENU_COL);
	drawString(20, 20, buffer, TEXT_COL);
}

void countdown(int sec) {
	for (; sec != 0; sec--) {
		sprintf(buffer, "Waiting %d...", sec);
		notify();
		msleep(1000);
	}
}

void print(char *string) {
	drawString(20, 20 + (line * 14), string, TEXT_COL);
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
		drawString(26, 26 + y, menu[i].text, TEXT_COL);

		if (menu[i].type == SELECT) {
			drawString(SCREEN_WIDTH - 120, 26 + y, menu[i].info->elements[menu[i].info->s], TEXT_COL);
		}

		y += 22;
	}
}

// Wait until a button is pressed
int waitButton(int id) {
	while (!gpioStat(id)) {
		msleep(1);
	}

	while (gpioStat(id)) {
		msleep(1);
	}
}

// Check for button status
int getButton() {
	int id;
	if (gpioStat(P_SELBTN)) {
		id = P_SELBTN;
	} else if (gpioStat(P_MODEBTN)) {
		id = P_MODEBTN;
	} else if (gpioStat(P_RECBTN)) {
		id = P_RECBTN;
	} else {
		return 0;
	}

	// Wait until button is up
	while (gpioStat(id)) {
		msleep(1);
	}

	return id;
}

// This interprets and runs a menu from the structure.
int runMenu(struct MenuItem menu[]) {
	int temp;
	
	drawGUI();
	drawMenu(menu);
	while (1) {
		int r = getButton();
		if (r == P_SELBTN) {
			if (menu[sel].type == ACTION) {
				drawGUI();
				temp = sel;
				sel = 0;
				line = 0;
				if (menu[temp].action(temp) != 0) {
					return 0;
				}
			} else if (menu[sel].type == SELECT) {
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
					
					msleep(1);
				}
			} else if (menu[sel].type == RETURN) {
				temp = sel;
				sel = 0;
				return temp;
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
		
		msleep(10);
	}
}

struct MenuItem mainMenu[] = {
	{"Exit", 0, RETURN, 0},
	{"About AHDK", app_info, ACTION, 0},
	{"Manual", app_exposure, ACTION, 0},
	{"Run Script", app_scripts, ACTION, 0},
	//{"BrainF", app_bf, ACTION, 0},
	//{"CrypticOS", app_cins, ACTION, 0},
	{"Tetris", app_tetris, ACTION, 0},
	{"Linux", app_linux, ACTION, 0},
	{0}
};

void start(int *env, int argc, char *argv[]) {
	if (argc != 1) {
		for (int i = 0; i < argc; i++) {
			printf(env, "%s\n", argv[i]);
		}
	}

	#ifdef COPYSCREEN
		int *oldScreen = malloc(SCREEN_WIDTH * SCREEN_HEIGHT);
		char *screen = (char*)MEM_BUFFER;
		memcpy(oldScreen, screen, SCREEN_WIDTH * SCREEN_HEIGHT);
	#endif
	
	envg = env;
	line = 0;
	sel = 0;

	// Copy font into memory
	FILE *file = fopen("d:/ahdk/font.bin", "r");
	if (!file) {
		printf(env, "No font.\n");
		return;
	} else {
		printf(env, "Loaded font\n");
	}
	
	fread(font, 1, 5000, file);
	fclose(file);

	runMenu(mainMenu);

	#ifdef COPYSCREEN
		memcpy(screen, oldScreen, SCREEN_WIDTH * SCREEN_HEIGHT);
		free(oldScreen);
	#endif
}