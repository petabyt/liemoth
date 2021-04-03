#include "header.h"
#include "ambarella.h"

int *envg;
int line;
int sel;
struct Font font[100];
char buffer[100];
char shutterCode[][4] = {"1", "24", "85", "126", "178", "252", "378"};

void notify() {
	drawBox(10, 10, 200, 40, MENU_COL);
	printString(20, 20, buffer, TEXT_COL);
}

void countdown(int sec) {
	for (; sec != 0; sec--) {
		amb_sprintf(buffer, "Waiting %d...", sec);
		notify();
		amb_msleep(1000);
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
	amb_gpio(id, &b, &c, &d);
	return !(c & 0xff);
}

// Wait until a button is pressed
int waitButton(int id) {
	while (!gpioStat(id)) {
		amb_msleep(1);
	}

	while (gpioStat(id)) {
		amb_msleep(1);
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
		amb_msleep(1);
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
					sel = 0;
					line = 0;
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
					
					amb_msleep(1);
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
		
		amb_msleep(10);
	}
}

int ahdkInfo() {
	line = 0;
	amb_sprintf(buffer, "AHDK Menu: Model: %s", P_NAME);
	print(buffer);
	print("Press select button to exit.");
	drawImage(140, 50, 150, 150, "d:/ahdk/logo.bin");
	waitButton(P_SELBTN);
	return 0;
}

void writeAmbsh(char *buffer) {
	FILE *file = amb_fopen("d:/ahdk/a.ash", "w");
	amb_fwrite(buffer, 1, strlen(buffer), file);
	amb_fclose(file);
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

char *hijackExp[] = {"ia2", "-ae", "exp", 0, 0};

int expTake() {
	hijackExp[3] = selectISO.elements[selectISO.s];
	hijackExp[4] = shutterCode[selectExp.s];
	amb_exp(envg, hijackExp);
	return 0;
}

struct MenuItem expMenu[] = {
	{"ISO", 0, SELECT, &selectISO},
	{"Exp", 0, SELECT, &selectExp},
	{"Apply", expTake, ACTION, 0},
	{"Exit", exitMenu, ACTION, 0},
	{0}
};

int expSetting() {
	runMenu(expMenu);
	return 0;
}

int allocTest() {
	line = 0;
	int test, r;
	print("Alloc 1m");
	r = amb_alloc(1, 102400, &test);
	amb_sprintf(buffer, "R: %d Addr: %x", r, test);
	print(buffer);
	amb_free(&test);
	print("1m Freed??");
	waitButton(P_SELBTN);
}

int graphicTest() {
	int a = 1;
	int t = 1;
	while (1) {
		clearScreen();
		fillRect(a, 10, a + 10, 20, COL_RED);
		amb_msleep(30);
		if (t) {
			a++;
		} else {
			a--;
		}

		if (a == 100 || a == 0) {
			t = !t;
		}
	}
}

// Stolen from:
// https://github.com/kgabis/business-card-brainfuck
// MIT License
int bfExec() {
	int x = 0;
	int y = 0;
	int r = 0;
	int c = 0;
	int t = 0;
	int e = 0;
	int p[65536];
	int d[1024];
	
	FILE *f = amb_fopen("d:/autoexec.bf", "r");
	if (!f) {
		return 0;
	}
	
	while (amb_fread(&c, 1, 1, f)) {
		p[r] = c;
		r++;
	}
	
	r = 0;
	while((c = p[r])) {
		e = 0;
		if (c == '>') {
			t++;
		} else if (c == '<') {
			t--;
		} else if (c == '+') {
			d[t]++;
		} else if (c == '-') {
			d[t]--;
		} else if (c == '.') {
			if (d[t] == 10) {
				y++;
				x = 0;
			} else {
				drawPixel(x, y, d[t] * 2);
				x++;
			}
		}
		
		while (c == '[' && !d[t]) {
			if (p[r] == '[') {
				e++;
			}
			
			if (p[r] == ']' && e-- == 1) {
				break;
			}
			
			r++;
		}
		
		while (c == ']' && d[t]) {
			if (p[r] == ']') {
				e++;
			}
			
			if (p[r] == '[' && e-- == 1) {
				break;
			}
			
			r--;
		}
		
		r++;
	}

	amb_msleep(10000);
}

struct MenuItem mainMenu[] = {
	{"Exit", exitMenu, ACTION, 0},
	{"Manual", expSetting, ACTION, 0},
	{"About AHDK", ahdkInfo, ACTION, 0},
	{"Alloc test", allocTest, ACTION, 0},
	{"Graphics", graphicTest, ACTION, 0},
	{"BF Exec", bfExec, ACTION, 0},
	{0}
};

void start(int *env) {
	envg = env;
	amb_printf(env, "AHDK Started");
	line = 0;
	sel = 0;

	// Copy font into memory
	FILE *file = amb_fopen("d:/ahdk/font.bin", "r");
	if (!file) {amb_printf(env, "No font"); return;}
	amb_fread(font, 2737, 2737, file);
	amb_fclose(file);

	runMenu(mainMenu);
	clearScreen();
	countdown(3);
	clearScreen();
}
