/*
Activeon DX
Firmware version 3.03
Download: https://mega.nz/file/SzhRHQDD#pWM_ITpojXTpYEMiKPsm67UROwmpjCg-XZg7kvAiBwg (thanks goprawn admin)
Activeon DX forum: https://www.goprawn.com/forum/ambarella-cams/363-isaw-extreme-actionpro-x7-activeon-dx-a7-imx117
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
