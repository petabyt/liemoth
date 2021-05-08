#ifndef __GOPRO
#define __GOPRO

// Actual size is 56x80
// Screen is a bit field
#define SCREEN_WIDTH 7
#define SCREEN_HEIGHT 10

// fpstring("HELLO", 0, 1);
void fpstring(char *text, unsigned int a, int b);

void showBuffer(unsigned char *buffer);

#endif
