// This attemps to hijack GUI code in order
// to launch AHDK on a UI button press.
// This is a WIP.

.thumb
.global _start
_start:
	// Default parameter
	mov r0, #0
	bl MEM_MAIN
