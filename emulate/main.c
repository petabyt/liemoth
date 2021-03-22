#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "../ahdk/ambarella.h"
#include "../platform/activeondx.h"
#include "gfx/gfx.h"
#include "ahdk.h"

int env = 123;
struct gfx_window window;

void setColor(unsigned int color) {
	switch (color) {
	case 255:
		gfx_setColor(&window, 255, 0, 0);
		break;
	case 1:
		gfx_setColor(&window, 255, 255, 255);
		break;
	case 93:
		gfx_setColor(&window, 70, 23, 227);
		break;
	case 32:
		gfx_setColor(&window, 171, 171, 171);
		break;
	default:
		gfx_setColor(&window, 0, 255, 0);
	}
}

void ambsh_sprintf(char *string, const char *fmt, ...) {
	va_list arg;
	va_start(arg, fmt);
	vsprintf(string, fmt, arg);
	va_end(arg);
}

void ambsh_printf(int *env, const char *fmt, ...) {
	env = env;
	
	va_list arg;
	va_start(arg, fmt);
	vprintf(fmt, arg);
	va_end(arg);
}

FILE *ambsh_fopen(char *file, char *mode) {
	// Convert Ambsh file to local Linux file
	char newFile[64] = "temp/";
	strcat(newFile, file + 3);
	
	return fopen(newFile, mode);
}

// just function routers, ignore warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

int ambsh_fread(void *buffer, unsigned long size, unsigned long count, FILE *file) {
	return fread(buffer, size, 1, file);
}

int ambsh_fclose(FILE *file) {
	return fclose(file);
}

void ambsh_msleep(int ms) {
	usleep(ms);
}

int ambsh_gpio(int *env, int count, char *arg[]) {
	struct gfx_interaction ia = gfx_event();
	if (ia.type == KEY) {
		if (ia.value == 'a') {
			return 0;
		} else if (ia.value == 'q') {
			exit(0);
		} else {
			return 1;
		}
	}
}

#pragma GCC diagnostic pop

// Screen weird, needs magic numbers
void drawPixel(int x, int y, unsigned char col) {
	setColor(col);
	gfx_pixel(&window, x, y);
}

void clearScreen() {
	
}

int main() {
	window = gfx_open(SCREEN_WIDTH, SCREEN_HEIGHT, "AHDK Emulator");
	start(&env, 0);
	return 0;
}
