/*
Activeon DX
	Firmware version 3.03
	Download: https://mega.nz/file/SzhRHQDD#pWM_ITpojXTpYEMiKPsm67UROwmpjCg-XZg7kvAiBwg (thanks goprawn admin)
	Activeon DX forum: https://www.goprawn.com/forum/ambarella-cams/363-isaw-extreme-actionpro-x7-activeon-dx-a7-imx117

CPU INFO:
	# head /proc/cpuinfo
	Processor       : ARMv6-compatible processor rev 5 (v6l)
	BogoMIPS        : 244.94
	Features        : swp half thumb fastmult edsp java 
	CPU implementer : 0x41
	CPU architecture: 6TEJ
	CPU variant     : 0x1
	CPU part        : 0xb36
	CPU revision    : 5

	Hardware        : (null)
*/


#define P_NAME "Activeon DX"

// Preferred Code
#define P_THUMB

// Main control manager process ID (should stay the same)
#define P_CTRLMAN 18

// Button GPIO codes
#define P_RECBTN 47
#define P_MODEBTN 48
#define P_SELBTN 49

#define SCREEN_HEIGHT 256
#define SCREEN_WIDTH 320

#define MEM_BASEADDR 0xc0000000

// Random unused spot in memory
#define MEM_PARAM 0xc012d5ac

// Top screen buffer (see notes.md)
#define MEM_BUFFER 0xc2413880

// Run on command "cardmgr", a bunch of prints
// including the strings, about 1.3k is free to use.
#define MEM_LOADER 0xc012d5d4

// Attempt payload location
// This is where the ntfl commmand is.
// I think around 18kb is free to use.
#define MEM_MAIN 0xc0138870

// From UI routine 0xc04199b6
#define MEM_TRIGGER 0xc0419a40

// Main required stubs
#define AMB_PRINTF 0xc0272996
#define AMB_MSLEEP 0xc026cc9c
#define AMB_ATOI 0xc01a23ac
#define AMB_SPRINTF 0xc02745c4
#define AMB_FOPEN 0xc02749a4
#define AMB_FCLOSE 0xc0274a92
#define AMB_FREAD 0xc0274c22
#define AMB_FWRITE 0xc0274bd8
#define AMB_ALLOC 0xc0181a08
#define AMB_HEAP 0xc03ac89c
#define AMB_FREE 0xc026e4b8
#define AMB_OPENDIR 0xc0274dd8
#define AMB_NEXTFILE 0xc0274cbe
#define AMB_GPIO 0xc0276bea
#define AMB_EXP 0xc02d0204
#define AMB_LU 0xc04b852c + 1 // Arm branch (blx)

// Experimental
#define AMB_MKDIR 0xc0275804
