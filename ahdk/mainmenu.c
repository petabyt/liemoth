// Main menu related functions
// (don't clog up the main file)

// Also, some apps are left blank by default.

#include "header.h"
#include "ambarella.h"

#define SHOWSCRIPTS

// Graphical BrainF*ck Interpreter
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
		
		FILE *f = amb_fopen("d:/ahdk/autoexec.bf", "r");
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

		waitButton(P_SELBTN);
	#endif
	return 0;
}

int runCins() {
	line = 0;
		
	// Allocate 1 megabyte of memory
	char *input;
	int r = amb_alloc(1, 102400, &input);

	// Read file into memory
	FILE *file = amb_fopen("d:/ahdk/autoexec.cins", "r");
	char c;
	r = 0;
	while (amb_fread(&c, 1, 1, file)) {
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

int ahdkInfo() {
	line = 0;
	amb_sprintf(buffer, "AHDK: Model: %s", P_NAME);
	print(buffer);
	amb_sprintf(buffer, "Built on: %s", __DATE__);
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
		
		struct Ambarella_dirReader dirReader;
		if (amb_openDir("d:/ahdk/scripts/*", NORMALDIR, &dirReader)) {
			waitButton(P_SELBTN);
			return 0;
		}

		// Generate a menu based on the scripts folder
		while (!amb_nextFile(&dirReader)) {
			amb_sprintf(names, dirReader.name);
			scriptMenu[i].text = names;
			scriptMenu[i].action = 0;
			scriptMenu[i].type = RETURN;
			scriptMenu[i].info = 0;

			names += strlen(dirReader.name) + 1;
			i++;
		}

		scriptMenu[i].text = 0;

		int r = runMenu(scriptMenu);

		// Copy it to a.ash, which is run after AHDK
		char buffer2[128];
		amb_sprintf(buffer2, "d:/ahdk/scripts/%s\n\n", scriptMenu[r].text);
		FILE *file = amb_fopen("d:/ahdk/a.ash", "w");
		amb_fwrite(buffer2, 1, strlen(buffer2), file);
		amb_fclose(file);
	#endif
	return 0;
}
