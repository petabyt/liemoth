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
#define MEM_BUFFER2 0xc2413880 + (SCREEN_HEIGHT * SCREEN_WIDTH)

// Secondary buffer shown in view photo/video menu
#define MEM_BUFFER 0xc2413880

// low resolution live sensor buffer. Can be used for
// motion detection, and other experiments
#define MEM_SENSOR_BUFFER 0xc45a1a00

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

#ifdef STUBS
	NSTUB(amb_printf, 0xc0272996)
	NSTUB(amb_msleep, 0xc026cc9c)
	NSTUB(amb_atoi, 0xc01a23ac)
	NSTUB(amb_sprintf, 0xc02745c4)
	NSTUB(amb_fopen, 0xc02749a4)
	NSTUB(amb_fclose, 0xc0274a92)
	NSTUB(amb_fread, 0xc0274c22)
	NSTUB(amb_fwrite, 0xc0274bd8)
	NSTUB(amb_alloc, 0xc0181a08)
	NSTUB(amb_heap, 0xc03ac89c)
	NSTUB(amb_free, 0xc026e4b8)
	NSTUB(amb_gpio, 0xc0276bea)

	// Experimental/porting notes
	NSTUB(amb_mkdir, 0xc0275804)
	NSTUB(amb_opendir, 0xc0274dd8)
	NSTUB(amb_nextfile, 0xc0274cbe)
	NSTUB(amb_exp, 0xc02d0204)
	NSTUB(amd_lu, 0xc04b852c + 1)
	NSTUB(amb_remove, 0xc0274b0a)
#endif

/*

hls file test, interesting..  c0224500

1920x720 buffer 0x045a2a80

*/
