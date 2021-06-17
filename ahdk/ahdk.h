#ifndef AHDK_H
#define AHDK_H

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

enum OptionType {
	SELECT, ACTION, RETURN
};

struct ItemInfo {
	int s;
	char *elements[];
};

struct MenuItem {
	char *text;
	int (*action)();
	int type;
	struct ItemInfo *info;
};

struct Font {
    char letter;
    char code[7][5];
};

int gpioStat(int id);

#ifndef NOGRAPHICS
// Graphics/UI functions
void drawPixel(int x, int y, unsigned char col);
void clearScreen();
int drawString(int x, int y, char *string, char color);
void drawImage(int x, int y, int width, int height, char image[]);
int printChar(int x, int y, char c, char color);
void fillRect(int x, int y, int x1, int y1, int col);
void drawBox(int x, int y, int x1, int y1, int col);

// Menu API functions
int runMenu(struct MenuItem menu[]);
int getButton();
int waitButton(int id);
void drawMenu(struct MenuItem menu[]);
void drawGUI();
void print(char *string);
void countdown(int sec);
void notify();
#endif

// Global environment var
extern int *envg;

// Current print() line
extern int line;

// Current menu selector
extern int sel;

// General purpose buffer
extern char buffer[100];

extern struct MenuItem mainMenu[];

// Standard functions
int strlen(char *buffer);
void memcpy(void* dest, const void* src, int count);
void *memset(void *dest, int val, int len);

// Custom math library functions
int divmod(int a, int b, int o);
int __aeabi_idiv(int a, int b);
int __aeabi_idivmod(int a, int b);

#endif
