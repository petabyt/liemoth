// C "script" to compile AHDK and minimal tests
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char *file = "test.c";

// Tell assembler, compiler, linker, to generate
// address independent code, and load the code into
// an allocated position in memory. (-fpic)
#define STANDALONE

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
		"%s-gcc %s -P -E Link.c -o link.ld",
		cc,
		include
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

	#define cfileslen (int)(sizeof(cfiles) / sizeof(cfiles[0]))

	// Compile each file
	for (int i = 0; i < cfileslen; i++) {
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
	for (int i = 0; i < cfileslen; i++) {
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
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		return 1;
	}

	sprintf(buffer, "ls %s > nul", DIRECTORY);
	if (system(buffer)) {
		puts("Output directory does not exist.");
	}

	// Select usable ARM GCC
	if (!system("which arm-none-eabi-gcc > nul")) {
		cc = "arm-none-eabi";
	} else if (!system("which arm-none-linux-gnueabi-gcc > nul")) {
		cc = "arm-none-linux-gnueabi";
	}

	system("rm nul");

	printf("ARM Compiler: %s\n", cc);

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
		"-std=c99 -c -O2 -ffreestanding %s",
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

	#ifdef STANDALONE
		strcat(cflags, " -D STANDALONE -fpic -mthumb-interwork");
		strcat(asmflags, " -D STANDALONE -fpic");
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