/*
Gopro Hero 3+
	Firmware Version 3.03
	Firmware: https://device-firmware.gp-static.com/11/HD3.11/camera_fw/03.03/UPDATE.zip
*/

#define P_NAME "GoPro Hero 3+"
#define P_ARM
#define P_GOPRO

#define P_CTRLMAN 37
#define P_MODEBTN 139
#define P_SELBTN 140
#define P_AUTOEXECTASK 59
#define P_BUTTONTASKA 17
#define P_BUTTONTASKB 16

#define MEM_BASEADDR 0xC0000000

// Like Activeon DX, Also cardmgr command
#define MEM_LOADER 0xc02d16e0

#define AMB_PRINTF 0xc0244f9c
#define AMB_MSLEEP 0xc03700b0
#define AMB_FOPEN 0xc013f3ac
#define AMB_FREAD 0xc013f768
#define AMB_FCLOSE 0xc013f4f8
#define GP_FPSTRING 0xc03705c8

// ntfl command
#define MEM_MAIN 0xc02ded88

// Notes
#define FP_STRING 0xc010e514
#define MEM_GPIOHACK 0xc01505d4
#define MEM_PRINT 0xc0246a98
