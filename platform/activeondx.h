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
Display Info:
	[0;32m[00002938] DISP: ====<< DISPLAY INFO >>=====[0m
	[0;32m[00002938] DISP: vout->w	= 176[0m
	[0;32m[00002938] DISP: vout->h	= 320[0m
	[0;32m[00002938] DISP: vout->offx	= 32[0m
	[0;32m[00002938] DISP: vout->offy	= 0[0m
	[0;32m[00002938] DISP: vout->fps(field_rate)	= 1[0m
	[0;32m[00002938] DISP: vout->fmt	= 2[0m
	[0;32m[00002938] DISP: vout->enable	= 3[0m
	[0;32m[00002938] DISP: vout->state	= 1[0m
	[0;32m[00002938] DISP: [0m
	[0;32m[00002938] DISP: scene->vid = (0, 0, 240, 320)[0m
	[0;32m[00002938] DISP: scene->pip = (160, 170, 120, 80)[0m
	[0;32m[00002938] DISP: scene->osd = (0, 0, 240, 320)[0m
	[0;32m[00002938] DISP: [0m
	[0;32m[00002940] DISP: ======> disp_ch: 0 [0m
	[0;32m[00002941] DISP: [0m
	[0;32m[00002941] DISP: ====<< CSC INFO >>=====[0m
	[0;32m[00002941] DISP: csc_in	(0 :CSC_YCBCR, 1 :CSC_RGB)	= 0[0m
	[0;32m[00002941] DISP: csc_out	(0 :CSC_YCBCR, 1 :CSC_RGB)	= 1[0m
	[0;32m[00002941] DISP: csc_dev	(0 :Dchan, 1 :Fchan)		= 0[0m
	[0;32m[00002941] DISP: csc_sdhd	= 0[0m
	[0;32m[00002941] DISP: csc_idx	= 2[0m
	[0;32m[00002941] DISP: [0m
	[0;32m[00002941] DISP: csc table[0m
	[0;32m[00002941] DISP: 0x1ea70400 0x04001d35 0x000006ed[0m
	[0;32m[00002941] DISP: 0x00000400 0x0084057b 0x7f507f22[0m
	[0;32m[00002941] DISP: 0x00ff0000 0x00ff0000 0x00ff0000[0m
	[0;32m[00002941] DISP: =======================[0m
*/


#define P_NAME "Activeon DX"

// Preferred Code
#define P_THUMB

// Main control manager process ID (should stay the same)
#define P_CTRLMAN 18

// Button GPIO codes
#define P_MODEBTN 48
#define P_SELBTN 49

#define SCREEN_HEIGHT 256
#define SCREEN_WIDTH 320

// Top screen buffer (see notes.md)
#define MEM_BUFFER 0xc2413880

// Random spot in memory
#define MEM_PARAM 0xc012d5ac

// Run on command "cardmgr", a bunch of prints
// including the strings, about 1.3k is free to use.
#define MEM_LOADER 0xc012d5d4

// Attempt payload location
// This is where the ntfl commmand is.
// I think around 18kb is free to use.
#define MEM_MAIN 0xc0138870

#define AMB_PRINTF 0xc0272996
#define AMB_MSLEEP 0xc026cc9c
#define AMB_ATOI 0xc01a23ac
#define AMB_SPRINTF 0xc02745c4
#define AMB_FOPEN 0xc02749a4
#define AMB_FCLOSE 0xc0274a92
#define AMB_FREAD 0xc0274c22
#define AMB_GPIO 0xc0276bea
#define AMB_FWRITE 0xc0274bd8
#define AMB_EXP 0xc02d0204
#define AMB_ALLOC 0xc0181a08
#define AMB_HEAP 0xc03ac89c
#define AMB_FREE 0xc026e4b8

// Experiments

// Text flashed when card removed
#define MEM_NOCARD 0xc156bfaa

// Text shown on viewer mode menu
#define MEM_MENU 0xc156bea6

// int result = MKDIR(char *folder)
#define MKDIR 0xc0275804

#define STRCMP 0xc012de02

// Main cardmgr command. Very big
#define CARDMGR 0xc012db92

#define GPIO 0xc0107f64
