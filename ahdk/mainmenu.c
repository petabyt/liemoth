// Main menu related functions
// (don't clog up the main file)

#include "ahdk.h"
#include "ambarella.h"

#define TETRIS

// Graphical BrainF*ck Interpreter, Test it with mandelbrot.bf
// Stolen from: https://github.com/kgabis/business-card-brainfuck
// MIT License
int bfExec() {
	#ifdef BF
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
	#endif
	return 0;
}

int runCins() {
	#ifdef RUNCINS
	line = 0;
		
	// Allocate 1 megabyte of memory
	char *input;
	int r = malloc(1, 102400, &input);

	// Read file into memory
	FILE *file = fopen("d:/ahdk/autoexec.cins", "r");
	char c;
	r = 0;
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
	#endif
	return 0;
}

int ahdkInfo() {
	line = 0;
	sprintf(buffer, "AHDK: Model: %s", P_NAME);
	print(buffer);
	sprintf(buffer, "Built on: %s", __DATE__);
	print(buffer);
	print("Press select button to exit.");
	drawImage(140, 70, 150, 150, "d:/ahdk/logo.bin");
	waitButton(P_SELBTN);
	return 0;
}

int showScripts() {
	#ifdef SHOWSCRIPTS
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
	#endif
	return 0;
}

#ifdef TETRIS

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
#endif

//Main routine
int tetris() {
	#ifdef TETRIS
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

	#endif
	return 0;
}
