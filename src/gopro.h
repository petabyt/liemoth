#ifndef __GOPRO
#define __GOPRO

// Width is 7 pixels * 8 bits, so 56 pixels
// Height is 90 layers
#define SCREEN_WIDTH 7
#define SCREEN_HEIGHT 80

// fpstring("HELLO", 0, 1);
void fpstring(char *text, unsigned int a, int b);

void showBuffer(unsigned char *buffer);

#endif
