/*
Xiaomi Yi
Ambarella A7
*/

#define P_NAME "Xiaomi Yi"

// Preferred Code
#define P_THUMB

// Main control manager process ID (should stay the same)
#define P_CTRLMAN x

// Button GPIO codes
#define P_RECBTN x
#define P_MODEBTN x
#define P_SELBTN x

#define SCREEN_HEIGHT 256
#define SCREEN_WIDTH 320

#define MEM_BASEADDR 0xc000000

// Top screen buffer (see notes.md)
#define MEM_BUFFER x

// Run on command "cardmgr", a bunch of prints
// including the strings, about 1.3k is free to use.
#define MEM_LOADER 0xc0171810

// Attempt payload location
// (Somewhere in memory that isn't
// important)
#define MEM_MAIN x

// Main required stubs
#define AMB_PRINTF 0xc02b693c
#define AMB_MSLEEP 0xc02ad028
#define AMB_SPRINTF x
#define AMB_FOPEN 0xc02b8a88
#define AMB_FCLOSE x
#define AMB_FREAD x
#define AMB_GPIO x
#define AMB_FWRITE x
#define AMB_ALLOC 0xc01d7d58
#define AMB_FREE 0xc02aeaec

// Optional
#define AMB_OPENDIR x
#define AMB_NEXTFILE x
#define AMB_ATOI x
#define AMB_EXP x
