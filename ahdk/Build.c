// C "script" to compile AHDK and minimal tests
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
// an allocated position in memory. (-fpic)
//#define STANDALONE

// Default platform for text editor warnings
// or something
#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

char include[512];
char cflags[4096];
char asmflags[1024];
char buffer[10240];
char ldflags[1024];

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
		buffer, // -	-T link.ld
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
	system("rm -f *.o *.elf link.ld");
}

// Write files into the device SD card
void write() {
	printf("Ashp script flags: %s\n", FLAGS);

	sprintf(
		buffer,
		"cp main.o %s/ahdk/ahdk.bin",
		DIRECTORY
	); system(buffer);

	// Compile ashp script generator
	sprintf(
		buffer,
		"%s %s ../ashp/ashp.c Script.c -o gen.o",
		hostcc, include
	); system(buffer);

	sprintf(
		buffer,
		"./gen.o %s > %s/autoexec.ash",
		FLAGS, DIRECTORY
	); system(buffer);

	puts("Wrote files to output directory.");
	system("ls -l main.o");
	system("ls -l loader.o");

	sprintf(
		buffer,
		"%s-size --target=binary main.o",
		cc
	); system(buffer);
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		puts("No target");
		return 1;
	}

	// Test output directory
	sprintf(buffer, "ls %s >nul 2>&1", DIRECTORY);
	if (system(buffer)) {
		puts("ERROR: Output directory doesn't exist.");
		return 1;
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
		puts(
			"Telling GCC to generate address independent code\n" \
			"Don't expect it to work..."
		);
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
		"-std=c99 -c -O0 -ffreestanding %s",
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
		"-c %s",
		include
	);

	// FIXME: pointer initialization issues
	// with linker script. Stack variables are
	// put at MEM_MAIN, any they probably shouldn't.
	// Also, pointers are very broken or something.

	// https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
	// https://community.arm.com/developer/tools-software/tools/f/arm-compilers-forum/7195/global-variable-not-initialized-by-__main-function
	// https://stackoverflow.com/questions/53263275/arm-none-eabi-global-initialized-variable-incorrect-value
	// https://developer.arm.com/documentation/dui0493/g/linker-command-line-options/--fpic

	// &mainMenu[0].text	0xc0139b84
	// Actual				0xc0139b24

	/*
	# Generate position independent code.
	-fPIC

	# Access bss via the GOT.
	-mno-pic-data-is-text-relative

	# GOT is not PC-relative; store GOT location in a register.
	-msingle-pic-base

	# Store GOT location in r9.
	-mpic-register=r9
	*/

	// Flags common to Asm and C
	char allflags[512] = " -march=armv6 -c -mthumb-interwork";
	strcat(asmflags, allflags);
	strcat(cflags, allflags);

	#ifdef STANDALONE
		strcat(cflags, " -D STANDALONE -fpic -mthumb-interwork");
		strcat(asmflags, " -D STANDALONE -fpic ");
	#endif

	if (!strcmp(argv[1], "minimal")) {
		file = argv[2];		
		loader();
		minimal();
		write();
		clean();
	} else if (!strcmp(argv[1], "ahdk")) {
		loader();
		ahdk();
		write();
		clean();
	}
}