#ifndef MODULES_H
#define MODULES_H

#include <stdint.h>

// Allow includer to specify whether
// addresses are needed
#ifndef NO_ADDR
	#define ADDR(addr) addr
#endif

#ifdef NO_ADDR
	#define ADDR(addr) 0
#endif

#define MODULES_VERSION 1

enum ModuleType {
	M_FUNC = 1,
	M_VAR = 2
};

struct ModuleInfo {
	// This will never change
	unsigned int version;

	// Use {0, 0, 0} as the function list
	// null-terminator
	struct Function {
		int type;
		char *name;
		uintptr_t addr;
	}funcs[];
};

#ifndef NO_STRUCT
static static struct ModuleInfo moduleFuncs = {
	MODULES_VERSION,
	{
		// Std funcs
		{M_FUNC, "printf", ADDR(AMB_PRINTF)},
		{M_FUNC, "msleep", ADDR(AMB_PRINTF)},
		{M_FUNC, "sprintf", ADDR(AMB_SPRINTF)},
		{M_FUNC, "fopen", ADDR(AMB_FOPEN)},
		{M_FUNC, "fclose", ADDR(AMB_FCLOSE)},
		{M_FUNC, "fread", ADDR(AMB_FREAD)},
		{M_FUNC, "fwrite", ADDR(AMB_FWRITE)},
		{M_FUNC, "gpio", ADDR(AMB_GPIO)},

		// AHDK provided functions
		{M_FUNC, "waitButton", ADDR((uintptr_t)&waitButton)},
		{M_FUNC, "getButton", ADDR((uintptr_t)&waitButton)},
		{M_FUNC, "drawString", ADDR((uintptr_t)&drawString)},
		{M_FUNC, "drawPixel", ADDR((uintptr_t)&drawPixel)},
		{M_FUNC, "malloc", ADDR((uintptr_t)&malloc)},
		{M_FUNC, "free", ADDR((uintptr_t)&free)},

		// Button defs
		{M_VAR, "P_RECBTN", ADDR(P_RECBTN)},
		{M_VAR, "P_MODEBTN", ADDR(P_RECBTN)},
		{M_VAR, "P_SELBTN", ADDR(P_SELBTN)},
		{0, 0, 0}
	}
};
#endif

#endif
