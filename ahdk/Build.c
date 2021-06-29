// Main AHDK Build system
// Like a Makefile, but done through
// sprintf() and system() calls
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defaults
#ifndef PLATFORM
	#define PLATFORM "activeondx"
#endif
#ifndef DIRECTORY
	#define DIRECTORY "/media/daniel/8765-4321"
#endif
#ifndef FLAGS
	#define FLAGS "SUSPEND LOG"
#endif

char *cc = "arm-none-eabi";
char *hostcc = "cc";

// `make minimal` test file
char *file = "test.c";

// Tell assembler, compiler, linker, to generate
// address independent code, and load the code into
// an allocated position in memory. (-fpie)
#define STANDALONE

// Don't clean the output files
//#define NOCLEAN

// Don't write AHDK to any device/folder
//#define NOWRITE

// Removed unused sections and functions. Can
// scrape off a few kilobytes. (currently broken)
//#define REMOVEUNUSED

// Default platform for text editor warnings
// or something
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

// Flag buffers
char include[512];
char cflags[4096];
char asmflags[1024];
char ldflags[1024];

// For sprintf-ing into
char buffer[10240];

// Make build proccess a little bit
// more colorful
#ifdef __linux__
	#define RED printf("\033[31m");
	#define GREEN printf("\033[32m");
	#define WHITE printf("\x1B[0m");
	#define YELLOW printf("\033[33m");
#else
	#define RED
	#define GREEN
	#define WHITE
	#define YELLOW
#endif

void enableapp(char app[]) {
	GREEN
	printf("Compiling app: %s\n", app);
	WHITE

	char buffer[64] = {" -D APP_"};
	int i;
	
	for (i = 0; app[i] != 0; i++) {
		buffer[i + 8] = toupper(app[i]);
	}
	
	buffer[i + 8] = '\0';
	strcat(cflags, buffer);
}

void loader() {
	sprintf(
		buffer,
		"%s-gcc %s loader.S -o loader.o",
		cc, asmflags
	); system(buffer);

	sprintf(
		buffer,
		"%s-ld %s loader.o -Ttext 0x%x -o loader.elf",
		cc, ldflags, MEM_LOADER
	); system(buffer);

	sprintf(
		buffer,
		"%s-objcopy -O binary loader.elf loader.o",
		cc
	); system(buffer);

	// Preprocess linker file from Link.c
	sprintf(
		buffer,
		"%s-gcc %s %s -P -E Link.c -o link.ld",
		cc, cflags, include
	); system(buffer);
}

int hijackLocation = 0;
void hijack(char name[], int hijack) {
	// Set for Script.c
	hijackLocation = hijack;

	sprintf(
		buffer,
		"%s-gcc %s -D%s hijack.S -o hijack.o",
		cc, asmflags, name
	); system(buffer);

	sprintf(
		buffer,
		"%s-ld %s hijack.o -Ttext 0x%x -o hijack.elf",
		cc, ldflags, hijack
	); system(buffer);

	sprintf(
		buffer,
		"%s-objcopy -O binary hijack.elf hijack.o",
		cc
	); system(buffer);
}

void minimal() {
	printf("Minimal file to compile: %s\n", file);

	// Assemble main.S
	sprintf(
		buffer,
		"%s-gcc %s main.S -o mains.o",
		cc, asmflags
	); system(buffer);

	// Compile C file
	sprintf(
		buffer,
		"%s-gcc %s %s -o main.o",
		cc, cflags, file
	); system(buffer);

	sprintf(
		buffer,
		"%s-ld %s mains.o main.o -T link.ld -o main.elf",
		cc, ldflags
	); system(buffer);

	sprintf(
		buffer,
		"%s-objcopy -O binary main.elf main.o",
		cc
	); system(buffer);
}

// Compile main AHDK
void ahdk() {
	// Assemble main file
	sprintf(
		buffer,
		"%s-gcc %s main.S -o mains.o",
		cc, asmflags
	); system(buffer);

	char *cfiles[] = {
		"main",
		"screen",
		"apps",
		"lib"
	};

	#define CFILESLEN (int)(sizeof(cfiles) / sizeof(cfiles[0]))

	// Compile each file
	for (int i = 0; i < CFILESLEN; i++) {
		sprintf(
			buffer,
			"%s-gcc %s %s.c -o %s.o",
			cc, cflags, cfiles[i], cfiles[i]
		); system(buffer);
	}

	// Link all files together
	// Make sure mains.o is first
	sprintf(
		buffer,
		"%s-ld %s mains.o",
		cc, ldflags
	);

	// Copy in each object file
	for (int i = 0; i < CFILESLEN; i++) {
		strcat(buffer, " ");
		strcat(buffer, cfiles[i]);
		strcat(buffer, ".o");
	}

	strcat(buffer, " -T link.ld -o main.elf");
	system(buffer);

	sprintf(
		buffer,
		"%s-objcopy -O binary main.elf main.o",
		cc
	); system(buffer);
}

void clean() {
	#ifndef NOCLEAN
		system("rm -f *.o *.elf link.ld nul");
	#endif
}

// Write files into the device SD card
void write() {
	printf("Ashp script flags: %s\n", FLAGS);

	// Compile ashp script generator
	sprintf(
		buffer,
		"%s %s ../ashp/ashp.c Script.c -D HIJACK=0x%x -o gen.o",
		hostcc, include, hijackLocation
	); system(buffer);

	#ifndef NOWRITE
		sprintf(
			buffer,
			"./gen.o %s > %s/autoexec.ash",
			FLAGS, DIRECTORY
		); system(buffer);

		sprintf(
			buffer,
			"cp main.o %s/ahdk/ahdk.bin",
			DIRECTORY
		); system(buffer);

		GREEN
		puts("Wrote files to output directory.");
		WHITE
	#endif

	sprintf(
		buffer,
		"%s-size --format=berkeley --target=binary loader.o",
		cc
	); system(buffer);

	sprintf(
		buffer,
		"%s-size --format=berkeley --target=binary main.o",
		cc
	); system(buffer);
}

void font() {
	system("curl https://raw.githubusercontent.com/petabyt/font/master/font.h > font.c");
	sprintf(
		buffer, 
		"%s-gcc -c font.c -o font.o",
		cc
	); system(buffer);

	sprintf(buffer,
		"%s-objcopy -O binary font.o %s/ahdk/font.bin",
		cc,
		DIRECTORY
	); system(buffer);

	system("rm font.o font.c");
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		puts("No target");
		return 1;
	}

	if (!strcmp(argv[1], "clean")) {
		clean();
		GREEN
		puts("Cleaned files");
		WHITE
		return 0;
	}

	// Test output directory, probably only works on Linux
	#ifndef NOWRITE
		sprintf(buffer, "test -d %s", DIRECTORY);
		if (system(buffer)) {
			RED
			puts("ERROR: Output directory doesn't exist.");
			WHITE
			return 1;
		}
	#endif

	if (!strcmp(argv[1], "font")) {
		font();
		GREEN
		puts("Installed font.");
		WHITE
		return 0;
	}

	// Select usable ARM GCC
	if (!system("which arm-none-eabi-gcc > nul")) {
		cc = "arm-none-eabi";
	} else if (!system("which arm-none-linux-gnueabi-gcc > nul")) {
		cc = "arm-none-linux-gnueabi";
	}

	// test newer cc (works fine)
	// cc = "/home/daniel/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi";

	system("rm nul");

	printf("Using ARM Compiler: %s\n", cc);
	printf("Compiling target: %s\n", argv[1]);

	#ifdef STANDALONE
		YELLOW
		puts(
			"Telling GCC to generate address independent code\n" \
			"Don't expect it to work..."
		);
		WHITE
	#endif

	puts("---------------");

	// In assembly and C files, include the model header file
	// so it knows the camera's values and settings.
	sprintf(
		include,
		"-include \"../platform/%s.h\"",
		PLATFORM
	);

	// CFLAGS
	sprintf(
		cflags,
		"-std=c99 -c -O0 -ffreestanding -march=armv6 -mthumb-interwork %s",
		include
	);
	
	// Set up bytecode for C (asm does it in file)
	// And switch to ARM if standalone requested
	#if !defined(STANDALONE) && defined(P_THUMB)
		strcat(cflags, " -mthumb");
	#else
		strcat(cflags, " -marm");
	#endif

	strcpy(ldflags, "-Bstatic");

	#ifdef REMOVEUNUSED
		strcat(ldflags, " --gc-sections");
		strcat(cflags, " -fdata-sections -ffunction-sections");
	#endif

	// ASMFLAGS
	sprintf(
		asmflags,
		"-c %s -march=armv6 -mthumb-interwork",
		include
	);

	/*
	# FIXME: pointer initialization issues
	with linker script. Stack variables are
	put at MEM_MAIN, any they probably shouldn't.
	Also, pointers are very broken or something.

	https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
	https://community.arm.com/developer/tools-software/tools/f/arm-compilers-forum/7195/global-variable-not-initialized-by-__main-function
	https://stackoverflow.com/questions/53263275/arm-none-eabi-global-initialized-variable-incorrect-value
	https://developer.arm.com/documentation/dui0493/g/linker-command-line-options/--fpic
	# Generate position independent code.
	-fPIC

	# Access bss via the GOT.
	-mno-pic-data-is-text-relative

	# GOT is not PC-relative; store GOT location in a register.
	-msingle-pic-base

	# Store GOT location in r9.
	-mpic-register=r9
	*/

	#ifdef STANDALONE
		strcat(cflags, " -D STANDALONE -fpie");
		strcat(asmflags, " -D STANDALONE -fpie");
	#endif

	// Hijack syslog() to AMB_PRINTF
	//hijack("SYSLOG", 0xc026e0d4);

	// Hijack syslog2 to AMB_PRINTF
	hijack("SYSLOG2", 0xc026cf60);

	if (!strcmp(argv[1], "minimal")) {
		file = argv[2];

		loader();
		minimal();
		write();
		clean();
	} else if (!strcmp(argv[1], "ahdk")) {
		enableapp("tetris");
		enableapp("linux");

		loader();
		ahdk();
		write();
		clean();
	}
}