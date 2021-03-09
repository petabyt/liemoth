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

// Text flashed when card removed
#define MEM_NOCARD 0xc156bfaa

// Text shown on viewer mode menu
#define MEM_MENU 0xc156bea6

// Code triggered on invalid command
#define MEM_PRINT 0xc0273a00

// Run on command "cardmgr", a bunch of prints
#define MEM_LOADER 0xc012d5d4

// Attempt payload location?
#define MEM_MAIN 0xc0273860

#define AMBSH_PRINTF 0xc0272996

// Untested
#define FOPEN 0xc02749a4

#define STRCMP 0xc012de02

// Main cardmgr command. Very big
#define CARDMGR 0xc012db92
