// Sensor research: a huge, unfinished mess
// `make minimal file=rawtest.c d=... m=...`

#include "ambarella.h"
#include "ahdk.h"

#include "ambarella.h"
#include "ahdk.h"

// Save a live (compressed, small) buffer from memory.
void savebuf() {
	#define BSIZE 1920 * 1080

	FILE *f = fopen("d:/myvideo.raw", "w");

	unsigned char *frame;
	int r = _malloc(1, BSIZE, &frame);

	// Compressed live buffer (Activeon DX)
	unsigned char *b = (unsigned char*)0xc45a2a80;
	for (int i = 0; i < BSIZE; i++) {
		frame[i] = b[i];
	}

	fwrite(frame, 1, BSIZE, f);
	fclose(f);

	//_free(1, addr);
}

// logger
// 0xc026cf60
// c03c3748				raw function?
// int c04efde4()		sensor function

int sensor();
int sensortramp();
void syslog();
void syslog2();
void preview(); // ??

int rawinfo();
int raw();

// Does not do anything in view photo/video mode
// void preview(0xc, 0);

// sensor() commands
#define SENSOR3 0xB6001010 // sensor preview info

// Disables preview, gives info in syslog2
// param1: &ret = 0-20
// param2: 0
#define SENSOR_MODE 0xB6001011

// doesn't do anything
#define SENSOR5 0xB6001064
#define SENSOR6 0xB6001066
#define SENSOR7 0xB6001090

// Something with RAW, get raw info???
// long a = sensor(SENSOR8, "d:\\asd", &ret2);
// idsp dump address is 0x17309c0, sec_id:0
// save sec 0 dump:d:\asd size = -1054550048
#define SENSOR8 0xB6001027

// param1: 0-10
// param2: 
#define SENSOR_SPATIAL_FILTER 0xB6001130

// &id     0      &ret
#define GET_WARP_CALIB 0xB600108D

#define MAX_COMMAND_ID 0xB6001130

void start(int *env, int argc, char *argv[]) {
	//int *param = (int*)MEM_PARAM;
	//*param = (long int)env;

	char stack[1500];

	int a = rawinfo(stack);
	printf(env, "Return: %x\n", a);
	if (a != 0) {
		raw(stack, 0, 0);
	}

	//*param = 0;
}

/*
Sensor modes, not sure what it does.

Select Video Source: 0x0
[IMX117][WRN] [IMX117] sensor mode 0x0 not ready yet !
[IMX117][WRN] [IMX117] sensor mode 0x0 not ready yet !
Return: 0
Ret1: 0
Select Video Source: 0x1
================== Sensor mode info ==================
 Sensor mode: 0x1,	Downsample: (H)  2:3240420872 (V) 3223819084:1
 [sensor window]	W: 2124, H: 1098
 [capture window]	W: 1920, H: 1080
 frame_length_lines:  2275,	line_length_pck:  2816
 row_time: -684804.4760 us, VB: -700624.3753 us, HB: 14.6660 us
======================================================
Return: 0
Ret1: 1
Select Video Source: 0x2
================== Sensor mode info ==================
 Sensor mode: 0x2,	Downsample: (H)  2:3240420872 (V) 3223819084:2
 [sensor window]	W: 2084, H: 1524
 [capture window]	W: 1920, H: 1440
 frame_length_lines:  3080,	line_length_pck:  3120
 row_time: -684804.4880 us, VB: -700624.3753 us, HB: 10.8330 us
======================================================
Return: 0
Ret1: 2
Select Video Source: 0x3
================== Sensor mode info ==================
 Sensor mode: 0x3,	Downsample: (H)  2:3240420872 (V) 3223819084:3
 [sensor window]	W: 2124, H: 1098
 [capture window]	W: 1920, H: 1080
 frame_length_lines:  1363,	line_length_pck:  2816
 row_time: -684804.2280 us, VB: -700624.3753 us, HB: 14.6730 us
======================================================
Return: 0
Ret1: 3
Select Video Source: 0x4
================== Sensor mode info ==================
 Sensor mode: 0x4,	Downsample: (H)  2:3240420872 (V) 3223819084:4
 [sensor window]	W: 2124, H: 1098
 [capture window]	W: 1920, H: 1080
 frame_length_lines:  2726,	line_length_pck:  2816
 row_time: -684804.2280 us, VB: -700624.3753 us, HB: 14.6730 us
======================================================
Return: 0
Ret1: 4
Select Video Source: 0x5
================== Sensor mode info ==================
 Sensor mode: 0x5,	Downsample: (H)  2:3240420872 (V) 3223819084:5
 [sensor window]	W: 2084, H: 1524
 [capture window]	W: 1920, H: 1440
 frame_length_lines:  3600,	line_length_pck:  3200
 row_time: -684804.4960 us, VB: -700624.3753 us, HB: 11.1110 us
======================================================
Return: 0
Ret1: 5
Select Video Source: 0x6
================== Sensor mode info ==================
 Sensor mode: 0x6,	Downsample: (H)  3:3240420872 (V) 3223819084:6
 [sensor window]	W: 1388, H: 1020
 [capture window]	W: 1312, H:  738
 frame_length_lines:  1050,	line_length_pck:  1525
 row_time: -684804.3240 us, VB: -700624.3753 us, HB: 7.9420 us
======================================================
Return: 0
Ret1: 6
Select Video Source: 0x7
================== Sensor mode info ==================
 Sensor mode: 0x7,	Downsample: (H)  3:3240420872 (V) 3223819084:7
 [sensor window]	W: 1388, H: 1020
 [capture window]	W: 1312, H:  738
 frame_length_lines:  1125,	line_length_pck:  1706
 row_time: -684804.3600 us, VB: -700624.3753 us, HB: 8.8850 us
======================================================
Return: 0
Ret1: 7
Select Video Source: 0x8
================== Sensor mode info ==================
 Sensor mode: 0x8,	Downsample: (H)  2:3240420872 (V) 3223819084:8
 [sensor window]	W: 2084, H:  770
 [capture window]	W: 1952, H:  730
 frame_length_lines:   825,	line_length_pck:  2329
 row_time: -684804.3880 us, VB: -700624.3753 us, HB: 5.0540 us
======================================================
Return: 0
Ret1: 8
Select Video Source: 0x9
================== Sensor mode info ==================
 Sensor mode: 0x9,	Downsample: (H)  2:3240420872 (V) 3223819084:9
 [sensor window]	W: 2084, H:  770
 [capture window]	W: 1984, H:  558
 frame_length_lines:   900,	line_length_pck:  2560
 row_time: -684804.4600 us, VB: -700624.3753 us, HB: 5.5550 us
======================================================
Return: 0
Ret1: 9
Select Video Source: 0xA
================== Sensor mode info ==================
 Sensor mode: 0xA,	Downsample: (H)  1:3240420872 (V) 3223819084:10
 [sensor window]	W: 4168, H: 3062
 [capture window]	W: 4000, H: 3000
 frame_length_lines:  3120,	line_length_pck:  4400
 row_time: -684804.4880 us, VB: -700624.3753 us, HB: 11.4580 us
======================================================
Return: 0
Ret1: a
Select Video Source: 0xB
================== Sensor mode info ==================
 Sensor mode: 0xB,	Downsample: (H)  1:3240420872 (V) 3223819084:11
 [sensor window]	W: 4168, H: 3062
 [capture window]	W: 4000, H: 2666
 frame_length_lines:  3120,	line_length_pck:  4400
 row_time: -684804.4880 us, VB: -700624.3753 us, HB: 11.4580 us
======================================================
Return: 0
Ret1: b
Select Video Source: 0xC
================== Sensor mode info ==================
 Sensor mode: 0xC,	Downsample: (H)  1:3240420872 (V) 3223819084:12
 [sensor window]	W: 4168, H: 3062
 [capture window]	W: 4000, H: 2250
 frame_length_lines:  3120,	line_length_pck:  4400
 row_time: -684804.4880 us, VB: -700624.3753 us, HB: 11.4580 us
======================================================
Return: 0
Ret1: c
Select Video Source: 0xD
================== Sensor mode info ==================
 Sensor mode: 0xD,	Downsample: (H)  1:3240420872 (V) 3223819084:13
 [sensor window]	W: 4248, H: 2182
 [capture window]	W: 3840, H: 2160
 frame_length_lines:  2200,	line_length_pck:  5824
 row_time: -684804.4760 us, VB: -700624.3753 us, HB: 15.1660 us
======================================================
Return: 0
Ret1: d
Select Video Source: 0xE
================== Sensor mode info ==================
 Sensor mode: 0xE,	Downsample: (H)  2:3240420872 (V) 3223819084:14
 [sensor window]	W: 2084, H: 1524
 [capture window]	W: 1920, H: 1440
 frame_length_lines:  1716,	line_length_pck:  2800
 row_time: -684804.4920 us, VB: -700624.3753 us, HB: 9.7220 us
======================================================
Return: 0
Ret1: e
Select Video Source: 0xF
================== Sensor mode info ==================
 Sensor mode: 0xF,	Downsample: (H)  3:3240420872 (V) 3223819084:15
 [sensor window]	W: 1388, H: 1020
 [capture window]	W: 1312, H:  984
 frame_length_lines:  1050,	line_length_pck:  1525
 row_time: -684804.3240 us, VB: -700624.3753 us, HB: 7.9420 us
======================================================
Return: 0
Ret1: f
Select Video Source: 0x10
================== Sensor mode info ==================
 Sensor mode: 0x10,	Downsample: (H)  2:3240420872 (V) 3223819084:16
 [sensor window]	W: 2084, H:  770
 [capture window]	W: 1984, H:  744
 frame_length_lines:   825,	line_length_pck:  2329
 row_time: -684804.3880 us, VB: -700624.3753 us, HB: 5.0540 us
======================================================
Return: 0
Ret1: 10
Select Video Source: 0x11
================== Sensor mode info ==================
 Sensor mode: 0x11,	Downsample: (H)  2:3240420872 (V) 3223819084:17
 [sensor window]	W: 2084, H: 1524
 [capture window]	W: 1920, H: 1440
 frame_length_lines:  1800,	line_length_pck:  3200
 row_time: -684804.4960 us, VB: -700624.3753 us, HB: 11.1110 us
======================================================
Return: 0
Ret1: 11
Select Video Source: 0x12
================== Sensor mode info ==================
 Sensor mode: 0x12,	Downsample: (H)  3:3240420872 (V) 3223819084:18
 [sensor window]	W: 1388, H: 1020
 [capture window]	W: 1312, H:  984
 frame_length_lines:  1125,	line_length_pck:  1706
 row_time: -684804.3600 us, VB: -700624.3753 us, HB: 8.8850 us
======================================================
Return: 0
Ret1: 12
Select Video Source: 0x13
================== Sensor mode info ==================
 Sensor mode: 0x13,	Downsample: (H)  2:3240420872 (V) 3223819084:19
 [sensor window]	W: 2084, H:  770
 [capture window]	W: 1984, H:  744
 frame_length_lines:   900,	line_length_pck:  2560
 row_time: -684804.4600 us, VB: -700624.3753 us, HB: 5.5550 us
======================================================
Return: 0
Ret1: 13
*/