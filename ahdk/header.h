// Default platform
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

// Screen weird, needs magic numbers
void drawPixel(int x, int y, unsigned char col);
void clearScreen();

int divmod(int a, int b, int o);
int __aeabi_idiv(int a, int b);
int __aeabi_idivmod(int a, int b);
