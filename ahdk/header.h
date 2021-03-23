// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

#define BTN_UP_COL 32
#define BTN_DOWN_COL 120
#define MENU_COL 93
#define TEXT_COL 1

#define UI_WAIT 150

// Screen weird, needs magic numbers
void drawPixel(int x, int y, unsigned char col);
void clearScreen();

// Arm division functions, may or may not use
int divmod(int a, int b, int o);
int __aeabi_idiv(int a, int b);
int __aeabi_idivmod(int a, int b);
