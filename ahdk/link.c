// This file is preprocessed by GCC
// into a linker script.

// Problems:
// - global integers with preset values not working
// - Exposure app issue, see apps.c

SECTIONS {
	.text MEM_MAIN: {
		*(.text)
	}
}

