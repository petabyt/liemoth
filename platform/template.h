/*
Info goes here
...

*/


#define P_NAME "Camera"

// Preferred code
// (Bytecode of MEM_LOADER)
#define P_THUMB

// Main control manager process ID
// (should stay the same)
#define P_CTRLMAN 0x0

// Button GPIO codes
#define P_RECBTN 0x0
#define P_MODEBTN 0x0
#define P_SELBTN 0x0

#define SCREEN_HEIGHT 0x0
#define SCREEN_WIDTH 0x0

// Base memory address
#define MEM_BASEADDR 0x0

// Main screen buffer (see notes.md)
#define MEM_BUFFER 0x0

// Run on command "cardmgr", a bunch of printfs
#define MEM_LOADER 0x0

// Attempt payload location
// (Somewhere in memory that isn't
// important)
#define MEM_MAIN 0x0

// A byte reserved to pass info to ahdk,
// when called via "cardmgr" (optional)
#define MEM_PARAM 0x0

// Main required stubs
#define AMB_PRINTF 0x0
#define AMB_MSLEEP 0x0
#define AMB_SPRINTF 0x0
#define AMB_FOPEN 0x0
#define AMB_FCLOSE 0x0
#define AMB_FREAD 0x0
#define AMB_GPIO 0x0
#define AMB_FWRITE 0x0
#define AMB_ALLOC 0x0
#define AMB_HEAP 0x0
#define AMB_FREE 0x0

// Optional
#define AMB_OPENDIR 0x0
#define AMB_NEXTFILE 0x0
#define AMB_ATOI 0x0
#define AMB_EXP 0x0
