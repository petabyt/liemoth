// Problems:
// - global integers with preset values not working
// - Exposure app issue, see apps.c
// In other words, I have no idea how to write linker scripts. :)

SECTIONS {
	// GCC will preprocess MEM_MAIN into an address
	.text MEM_MAIN: {
		*(.text)
	}
}

