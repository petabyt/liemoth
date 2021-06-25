// Main menu related functions
// (don't clog up the main file)

#include "ambarella.h"
#include "ahdk.h"

// AHDK can be compiled without
// some apps.

//#define APP_LINUX
//#define APP_TETRIS
//#define APP_CINS
//#define APP_BF
//#define APP_EXPOSURE

#ifdef APP_LINUX
char *hijackLu[] = {"lu_util", "exec", buffer};

int app_linux() {
	print("Making sure Linux booted...");
	msleep(20000);
	
	sprintf(buffer, "busybox telnetd -l /bin/sh -p 80");
	lu(envg, 3, hijackLu);

	// The camera must be sent into a waiting
	// loop. This allows other tasks (like WiFi)
	// to work properly
	while (1) {
		msleep(2000);

		// fread doesn't null terminate, so clear buffer
		memset(buffer, '\0', sizeof(buffer));
		
		FILE *f = fopen("d:/asd", "r");
		fread(buffer, 1, 128, f);
		fclose(f);

		drawGUI();
		line = 0;
		print("Telnet IP: 192.168.42.1");
		print(buffer);
	}

	return 0;
}
#else
int app_linux() {return 0;}
#endif

#ifdef APP_EXPOSURE
struct ItemInfo selectISO = {
	0, {"200", "800", "1600", "3200", "6400", 0}
};

struct ItemInfo selectExp = {
	0, {"8", "7", "6", "5", "4", "3", "2", "1", 0}
};

char *shutterCode[] = {"1", "24", "85", "126", "178", "252", "378"};

int expTake() {
	// FIXME: linker messes this up when inserted beside shutterCode.
	// I haven't done any investigation to figure out why.
	char *hijackExp[5] = {"ia2", "-ae", "exp"};
	
	hijackExp[3] = selectISO.elements[selectISO.s];
	hijackExp[4] = shutterCode[selectExp.s];
	setExp(envg, hijackExp);
	return 0;
}

struct MenuItem expMenu[] = {
	{"ISO", 0, SELECT, &selectISO},
	{"Exp", 0, SELECT, &selectExp},
	{"Apply", expTake, ACTION, 0},
	{"Exit", 0, RETURN, 0},
	{0}
};


int app_exposure() {
	runMenu(expMenu);
	return 0;
}
#else
int app_exposure() {return 0;}
#endif

#ifdef APP_BF
// Graphical BrainF*ck Interpreter, Test it with mandelbrot.bf
// Stolen from: https://github.com/kgabis/business-card-brainfuck
// MIT License
int app_bf() {
	int x = 0;
	int y = 0;
	int r = 0;
	int c = 0;
	int t = 0;
	int e = 0;
	int p[65536];
	int d[1024];
	
	FILE *f = fopen("d:/ahdk/autoexec.bf", "r");
	if (!f) {
		return 0;
	}
	
	while (fread(&c, 1, 1, f)) {
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

	waitButton(P_SELBTN);
	return 0;
}
#else
int app_bf() {return 0;}
#endif

#ifdef APP_CINS
int app_cins() {
	line = 0;
		
	char input[1024];

	// Read file into memory
	FILE *file = fopen("d:/ahdk/autoexec.cins", "r");
	char c;
	int r = 0;
	while (fread(&c, 1, 1, file)) {
		input[r] = c;
		r++;
	}

	input[r] = '\0';
	
	int memtop[50];
	int membottom[1000];
	int topp = 0;
	int bottomp = 0;
	
	// Map the labels in an array.
	int labels[50];
	int l = 0;
	for (int c = 0; input[c] != '\0'; c++) {
		if (input[c] == '|') {
			labels[l] = c;
			l++;
		}
	}

	int bufC = 0;
	for (int c = 0; input[c] != '\0'; c++) {
		switch (input[c]) {
		case '!':
			membottom[bottomp] = 0;
			break;
		case '%':
			membottom[bottomp] += 50;
			break;
		case '*':
			membottom[bottomp] += 5;
			break;
		case '+':
			membottom[bottomp]++;
			break;
		case '-':
			membottom[bottomp]--;
			break;
		case '.':
			if (membottom[bottomp] == '\n') {
				buffer[bufC] = '\0';
				bufC = 0;
				print(buffer);
			}
			
			buffer[bufC] = membottom[bottomp];
			bufC++;
			break;
		case '>':
			bottomp++;
			break;
		case '<':
			bottomp--;
			break;
		case 'd':
			topp++;
			break;
		case 'a':
			topp--;
			break;
		case '^':
			memtop[topp] = membottom[bottomp];
			break;
		case 'v':
			membottom[bottomp] = memtop[topp];
			break;
		case '$':
			c = labels[memtop[topp]];
			break;
		case '?':
			if (memtop[topp + 1] == memtop[topp + 2]) {
				c = labels[memtop[topp]];
			}

			break;
		}
	}

	waitButton(P_SELBTN);
	return 0;
}
#else
int app_cins() {return 0;}
#endif

int app_info() {
	line = 0;
	sprintf(buffer, "AHDK: Model: %s", P_NAME);
	print(buffer);
	sprintf(buffer, "Built on: %s", __DATE__);
	print(buffer);
	print("Press select button to exit.");

	// Note: logo.bin isn't actually required.
	// drawImage will quit if it isn't found.
	drawImage(140, 70, 150, 150, "d:/ahdk/logo.bin");
	waitButton(P_SELBTN);
	return 0;
}

#ifdef APP_SCRIPTS
int app_scripts() {
	drawGUI();

	struct MenuItem scriptMenu[10];
	char *names = buffer;
	int i = 0;
	
	struct DirReader dirReader;
	if (openDir("d:/ahdk/scripts/*", NORMALDIR, &dirReader)) {
		waitButton(P_SELBTN);
		return 0;
	}

	// Generate a menu based on the scripts folder
	while (!nextFile(&dirReader)) {
		sprintf(names, dirReader.name);
		scriptMenu[i].text = names;
		scriptMenu[i].action = 0;
		scriptMenu[i].type = RETURN;
		scriptMenu[i].info = 0;

		names += strlen(dirReader.name) + 1;
		i++;
	}

	scriptMenu[i].text = 0;

	int r = runMenu(scriptMenu);

	// Copy reference to a.ash, which is run after AHDK
	char buffer2[128];
	sprintf(buffer2, "d:/ahdk/scripts/%s\n\n", scriptMenu[r].text);
	FILE *file = fopen("d:/ahdk/a.ash", "w");
	fwrite(buffer2, 1, strlen(buffer2), file);
	fclose(file);
	return 0;
}
#else
int app_scripts() {return 0;}
#endif

#ifdef APP_TETRIS

/*
*The following tetris code is licensed under GPL3 and not the AHDK License.

Tetris for Zx3
(C) 2010 Jeroen Domburg (jeroen AT spritesmods.com)

This program is free software: you can redistribute it and/or modify
t under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
			    
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
Modified to work with AHDK/Ambarella A7
Find the full original source here: http://spritesmods.com/zx3hack/zx3-hack_src.tgz

TODO: Fix RNG
*/

#define BLOCK_HEIGHT 10
#define BLOCK_WIDTH 10
#define SPEED 70

typedef struct {
	unsigned char field[10][20];
	unsigned char currBlock[4][4];
	int currBlockX, currBlockY;
}playfield_t;

unsigned int palette[8] = {
	COL_GREY, COL_RED, COL_GREEN, COL_ORANGE, COL_PINK,
	COL_PURPLE, COL_ORANGE + 5, COL_WHITE
};

int score;
int a;

unsigned char availBlocks[7][4][4] = {
	{
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 1, 1, 1},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 0, 0},
		{2, 2, 2, 0},
		{0, 0, 2, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 0, 0},
		{0, 3, 3, 3},
		{0, 3, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 0, 0},
		{0, 4, 4, 0},
		{0, 4, 4, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 0, 0},
		{0, 5, 5, 0},
		{5, 5, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 0, 0},
		{0, 6, 6, 0},
		{0, 0, 6, 6},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 0, 0},
		{0, 7, 7, 7},
		{0, 0, 7, 0},
		{0, 0, 0, 0},
	}
};

void fieldClear(playfield_t* field) {
	int x, y;
	for (x = 0; x < 10; x++) {
		for (y = 0; y < 20; y++) {
			field->field[x][y] = 0;
		}
	}
	
	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			field->currBlock[x][y] = 0;
		}
	}
}

int fieldIsPossible(playfield_t* field) {
	int px, py;
	int x, y;
	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			if (field->currBlock[x][y] != 0) {
				px = x + field->currBlockX;
				py = y + field->currBlockY;
				if (px < 0 || px >= 10 || py >= 20) {
					return 0;
				}
				
				if (py >= 0 && field->field[px][py] != 0) {
					return 0;
				}
			}
		}
	}
	
	return 1;
}

void fieldDup(playfield_t *dest, playfield_t *src) {
	memcpy(dest, src, sizeof(playfield_t));
}

void fieldRotateBlk(playfield_t *field, int dir) {
	unsigned char buff[4][4];
	int x, y;
	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			buff[x][y] = field->currBlock[x][y];
		}
	}
	
	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			if (dir > 0) {
				field->currBlock[x][y] = buff[3 - y][x];
			}
			
			else {
				field->currBlock[x][y] = buff[y][3 - x];
			}
		}
	}
}

void fieldSelectBlk(playfield_t *field, int blkNo) {
	int x, y;
	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			field->currBlock[x][y] = availBlocks[blkNo][x][y];
		}
	}

	field->currBlockX = 3;
	field->currBlockY = -2;
}

static int checkAndKillALine(playfield_t* field) {
	int x, y, ry;
	int found;
	for (y = 0; y < 20; y++) {
		found = 1;
		for (x = 0; x < 10; x++) {
			if (field->field[x][y] == 0)
				found = 0;
		}
		
		if (found) {
			// Remove line
			for (ry = y; ry >= 0; ry--) {
				for (x = 0; x < 10; x++) {
					if (ry != 0) {
						field->field[x][ry] = field->field[x][ry - 1];
					} else {
						field->field[x][ry] = 0;
					}
				}
			}
			return 1;
		}
	}
	return 0;
}

int fieldFixBlock(playfield_t *field) {
	int px, py;
	int x, y;
	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			px = x + field->currBlockX;
			py = y + field->currBlockY;
			if (field->currBlock[x][y] != 0) {
				field->field[px][py] = field->currBlock[x][y];
			}
		}
	}
	
	while (checkAndKillALine(field)) {
		score++;

		// Clear so score can update
		clearScreen();
	}

	return 1;
}

static void placeBlock(int col, int bx, int by) {	
	int x,y;
	for (x = 0; x < BLOCK_WIDTH; x++) {
		for (y = 0; y < BLOCK_HEIGHT; y++) {
			drawPixel((bx * BLOCK_WIDTH + x), (by * BLOCK_HEIGHT + y), palette[col & 7]);
		}
	}
}

// Display the game
void display(playfield_t *field) {
	int x, y;
	int px, py;
	for (x = 0; x < 10; x++) {
		for (y = 0; y < 20; y++) {
			placeBlock(field->field[x][y], x, y);
		}
	}

	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			px = x + field->currBlockX;
			py = y + field->currBlockY;
			if (field->currBlock[x][y] != 0) {
				if (px >= 0 && py >= 0 && px < 10 && py < 20) {
					placeBlock(field->currBlock[x][y], px, py);
				}
			}
		}
	}

	sprintf(buffer, "Score: %d", score);
	drawString(200, 10, buffer, COL_WHITE);
}

playfield_t field;
playfield_t testfield;

char randInts[] = {1, 4, 3, 5, 0, 5, 1, 3, 0, 2, 4, 3};

// Dumb "random" routine
int rand() {
	if (a == sizeof(randInts) - 1) {
		a = 0;
	} else {
		a++;
	}
	
	return randInts[a];
}

// Main routine
int app_tetris() {
	a = 0;
	score = 0;
	
	int ev;
	int dead = 0;
	int mustFixBlk;

	fieldClear(&field);
	fieldSelectBlk(&field, 2);

	clearScreen();

	int i = 0;
	while (1) {
		ev = getButton();
		fieldDup(&testfield, &field);
		mustFixBlk = 0;

		// Accept input while running game loop
		if (ev == 0) {
			if (i < SPEED) {
				msleep(1);
				i++;

				continue;
			} else {
				testfield.currBlockY++;
				if (fieldIsPossible(&testfield)) {
					fieldDup(&field, &testfield);
				} else {
					mustFixBlk = 1;
				}

				i = 0;
			}
		}
		
		if (ev == P_MODEBTN) {
			testfield.currBlockX--;
			if (fieldIsPossible(&testfield)) {
				fieldDup(&field, &testfield);
			}
		} else if (ev == P_SELBTN) {
			testfield.currBlockX++;
			if (fieldIsPossible(&testfield)) {
				fieldDup(&field, &testfield);
			}
		} else if (ev == P_RECBTN) {
			fieldRotateBlk(&testfield, 1);
			if (fieldIsPossible(&testfield)) {
				fieldDup(&field, &testfield);
			}
		}
			
		if (mustFixBlk && dead == 0) {
			fieldFixBlock(&field);
			fieldSelectBlk(&field, rand());
			if (!fieldIsPossible(&field)) {
				return 0;
			}
		}

		display(&field);
	}

	return 0;
}
#else
int app_tetris() {return 0;}
#endif