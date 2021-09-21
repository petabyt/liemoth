#ifndef MODULES_H
#define MODULES_H

#include <stdint.h>

#define MODULES_VERSION 1

enum ModuleType {
	M_FUNC, M_VAR
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

#endif
