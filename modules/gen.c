#include <stdio.h>

#define NO_ADDR
#include "../ahdk/modules.h"

// TODO: Use assembly solution
// TODO: Add strcmp

int main() {
	puts("#define NO_STRUCT");
	puts("#include <stdint.h>");
	puts("#include \"../ahdk/modules.h\"");

	puts("#define NOMALLOC");
	puts("#include \"../ahdk/lib.c\"");

	puts("int main();");

	// Write zeros
	for (int i = 0; moduleFuncs.funcs[i].name != 0; i++) {
		if (moduleFuncs.funcs[i].type != M_FUNC) {
			continue;
		}

		printf("typedef void _%s();\n", moduleFuncs.funcs[i].name);
		printf("_%s *%s = 0;\n", moduleFuncs.funcs[i].name, moduleFuncs.funcs[i].name);
	}

	// Main func loop
	puts(
		"void _start(struct ModuleInfo *info, uintptr_t addr) {"
		"	if (info->version != MODULES_VERSION) {"
		"		return;"
		"	}"
		""
		"for (int i = 0; info->funcs[i].name != 0; i++) {"
	);

	// If handlers to write function addr
	for (int i = 0; moduleFuncs.funcs[i].name != 0; i++) {
		if (moduleFuncs.funcs[i].type != M_FUNC) {
			continue;
		}

		printf("if (!strcmp(info->funcs[i].name, \"%s\"))\n", moduleFuncs.funcs[i].name);
		printf("	%s = (_%s*)info->funcs[i].addr;\n",
			moduleFuncs.funcs[i].name,
			moduleFuncs.funcs[i].name
		);
	}

	puts("} main(addr); }");
}
