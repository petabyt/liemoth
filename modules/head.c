#define NO_STRUCT
#include <stdint.h>
#include "../ahdk/modules.h"
#define NOMALLOC
#include "../ahdk/lib.c"
int main();
typedef void _printf();
_printf *printf = 0;
typedef void _msleep();
_msleep *msleep = 0;
typedef void _sprintf();
_sprintf *sprintf = 0;
typedef void _fopen();
_fopen *fopen = 0;
typedef void _fclose();
_fclose *fclose = 0;
typedef void _fread();
_fread *fread = 0;
typedef void _fwrite();
_fwrite *fwrite = 0;
typedef void _gpio();
_gpio *gpio = 0;
typedef void _waitButton();
_waitButton *waitButton = 0;
typedef void _getButton();
_getButton *getButton = 0;
typedef void _drawString();
_drawString *drawString = 0;
typedef void _drawPixel();
_drawPixel *drawPixel = 0;
typedef void _malloc();
_malloc *malloc = 0;
typedef void _free();
_free *free = 0;
void _start(struct ModuleInfo *info, uintptr_t addr) {	if (info->version != MODULES_VERSION) {		return;	}for (int i = 0; info->funcs[i].name != 0; i++) {
if (!strcmp(info->funcs[i].name, "printf"))
	printf = (_printf*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "msleep"))
	msleep = (_msleep*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "sprintf"))
	sprintf = (_sprintf*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "fopen"))
	fopen = (_fopen*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "fclose"))
	fclose = (_fclose*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "fread"))
	fread = (_fread*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "fwrite"))
	fwrite = (_fwrite*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "gpio"))
	gpio = (_gpio*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "waitButton"))
	waitButton = (_waitButton*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "getButton"))
	getButton = (_getButton*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "drawString"))
	drawString = (_drawString*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "drawPixel"))
	drawPixel = (_drawPixel*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "malloc"))
	malloc = (_malloc*)info->funcs[i].addr;
if (!strcmp(info->funcs[i].name, "free"))
	free = (_free*)info->funcs[i].addr;
} main(addr); }
