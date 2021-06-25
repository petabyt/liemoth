// Problems:
// - global integers with preset values not working
// - Exposure app issue, see apps.c
// In other words, I have no idea how to write linker scripts. :)

#ifdef STANDALONE
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(start)
SECTIONS {
	// GCC will preprocess MEM_MAIN into an address
	//. = MEM_MAIN;
#if 0
	. = ALIGN(4);
	.data : {
		DATA_START = .;
		*(.data)
		DATA_END = .;
	}
#endif
}
#else
ENTRY(_start)
SECTIONS {
	// GCC will preprocess MEM_MAIN into an address
	.text MEM_MAIN: {
		*(.text)
	}
}
#endif