/*
Info goes here
...

*/


#define P_NAME "Camera"

// Preferred Code
#define P_THUMB

// Main control manager process ID (should stay the same)
#define P_CTRLMAN x

// Button GPIO codes
#define P_RECBTN x
#define P_MODEBTN x
#define P_SELBTN x

#define SCREEN_HEIGHT x
#define SCREEN_WIDTH x

#define MEM_BASEADDR x

// Top screen buffer (see notes.md)
#define MEM_BUFFER x

// Run on command "cardmgr", a bunch of prints
// including the strings, about 1.3k is free to use.
#define MEM_LOADER x

// Attempt payload location
// (Somewhere in memory that isn't
// important)
#define MEM_MAIN x

// Main required stubs
#define AMB_PRINTF x
#define AMB_MSLEEP x
#define AMB_SPRINTF x
#define AMB_FOPEN x
#define AMB_FCLOSE x
#define AMB_FREAD x
#define AMB_GPIO x
#define AMB_FWRITE x
#define AMB_ALLOC x
#define AMB_HEAP x
#define AMB_FREE x

// Optional
#define AMB_OPENDIR x
#define AMB_NEXTFILE x
#define AMB_ATOI x
#define AMB_EXP x
