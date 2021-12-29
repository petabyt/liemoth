#include <stdint.h>
#include "../ahdk/modules.h"

#define _STR(X) #X
#defineS STR(X) _STR(X)

#define REQUIRE_FUNC(name) \
	__asm__(".global printf\n"
			"printf:\n"
			"bl 0x00000000\n");

void _start(struct ModuleInfo *info, uintptr_t addr) {
	// Out of date
	if (info->version != MODULES_VERSION) {
		return;
	}

	

	main();
}
