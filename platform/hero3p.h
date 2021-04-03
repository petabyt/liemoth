/*
Gopro Hero 3+
	Firmware Version 3.03
	Firmware: https://device-firmware.gp-static.com/11/HD3.11/camera_fw/03.03/UPDATE.zip
*/

#define P_NAME "GoPro Hero 3+"
#define P_ARM
#define P_NOSCREEN


#define P_CTRLMAN 37
#define P_MODEBTN 139
#define P_SELBTN 140

#define MEM_BASEADDR 0xC0000000

// Triggered on invalid command
#define MEM_PRINT 0xc0246a98

#define MEM_GPIOHACK 0xc01505d4

// Like Activeon DX, Also cardmgr command
#define MEM_LOADER 0xc02d16dc

// Notes
#define SLEEP 0xc03700b0
#define FP_STRING 0xc010e514
