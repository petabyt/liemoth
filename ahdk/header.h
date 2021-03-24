// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

// Color chart: https://petabyte.heb12.com/filedump/public/ambacol.jpg
#define COL_BLACK 71
#define COL_WHITE 0
#define COL_GREY 48
#define COL_RED 176
#define COL_GREEN 208
#define COL_ORANGE 224
#define COL_PINK 252
#define COL_PURPLE 253
#define COL_TRANSPARENT 255
#define COL_BLUE 103

// Blue: also range 71-129
// Grey: also range 16-71

#define BTN_UP_COL 32
#define BTN_DOWN_COL 120
#define MENU_COL 93
#define TEXT_COL COL_WHITE

#define UI_WAIT 150

struct Font {
    char letter;
    char code[7][5];
};

void drawPixel(int x, int y, unsigned char col);
void clearScreen();
int printString(int x, int y, char *string, char color);
void drawImage(int x, int y, int width, int height, char image[]);
int printChar(int x, int y, char c, char color);
void fillRect(int x, int y, int x1, int y1, int col);

// Arm division functions, may or may not use
int divmod(int a, int b, int o);
int __aeabi_idiv(int a, int b);
int __aeabi_idivmod(int a, int b);
