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

// Byte in memory dedicated to serving
// as a parameter for AHDK (preset to zero)
#define MEM_PARAM 0xc1745db0

// Main display buffer shown on camera preview
#define MEM_BUFFER 0xc2413880 + (SCREEN_HEIGHT * SCREEN_WIDTH)

// Secondary buffer shown in view photo/video menu
#define MEM_BUFFER2 0xc2413880

// Run on command "cardmgr", a bunch of prints
// including the strings, about 1.3k is free to use.
#define MEM_LOADER 0xc012d5cc

// Location of string "cardmgr"
// Can change to "ahdk"
#define MEM_CARDMGR 0xc064b700

// Attempt payload location
// This is where the ntfl commmand is.
// I think around 18kb is free to use.
#define MEM_MAIN 0xc0138880

// Attempt to hijack menu buttons
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
#define AMB_GPIO 0xc0276bea

// Experimental/porting notes
#define AMB_MKDIR 0xc0275804
#define AMB_OPENDIR 0xc0274dd8
#define AMB_NEXTFILE 0xc0274cbe
#define AMB_EXP 0xc02d0204
#define AMB_LU 0xc04b852c + 1 // Arm branch (blx)
#define AMB_REMOVE 0xc0274b0a

/*

hls file test, interesting..  c0224500

1920x720 buffer 0x045a2a80

*/
