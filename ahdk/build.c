// Alternative build system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLATFORM "activeondx"
#define DIRECTORY "/media/daniel/8765-4321"
#define FLAGS "SUSPEND LOG"

#define CC "arm-none-eabi"
#define HOSTCC "tcc"

#define MINIMALFILE "test.c"

char include[512];
char cflags[4096];
char asmflags[1024];
char buffer[10240];
char ldflags[1024];

void loader() {
	sprintf(
		buffer,
		"%s-gcc %s loader.S -o loader.o",
		CC, asmflags
	); system(buffer);

	sprintf(
		buffer,
		"%s-ld %s loader.o -Ttext 0x%x -o loader.elf",
		CC, ldflags, MEM_LOADER
	); system(buffer);

	sprintf(
		buffer,
		"%s-objcopy -O binary loader.elf loader.o",
		CC
	); system(buffer);

	// Preprocess linker file from link.c
	sprintf(
		buffer,
		"%s-gcc %s -P -E link.c -o link.ld",
		CC,
		include
	); system(buffer);
}

void minimal() {
	printf("Minimal file to compile: %s\n", MINIMALFILE);

	// Assemble main.S
	sprintf(
		buffer,
		"%s-gcc %s main.S -o mains.o",
		CC, asmflags
	); system(buffer);

	// Compile C file
	sprintf(
		buffer,
		"%s-gcc %s %s -o main.o",
		CC, cflags, MINIMALFILE
	); system(buffer);

	sprintf(
		buffer,
		"%s-ld %s mains.o main.o -T link.ld -o main.elf",
		CC, ldflags
	); system(buffer);

	sprintf(
		buffer,
		"%s-objcopy -O binary main.elf main.o",
		CC
	); system(buffer);
}

// Compile main AHDK
void ahdk() {
	
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
		"%s ../ashp/ashp.c script.c -o gen.o",
		HOSTCC
	); system(buffer);

	sprintf(
		buffer,
		"./gen.o %s > %s/autoexec.ash",
		FLAGS, DIRECTORY
	); system(buffer);
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		return 1;
	}

	// INCLUDE
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

	// Set up bytecode for C
	#ifdef P_THUMB
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

	loader();
	minimal();
	write();
	clean();
}