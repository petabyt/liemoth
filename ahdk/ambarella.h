// Universal Ambarella functions
#ifndef AMBARELLA_H
#define AMBARELLA_H

#ifndef P_NAME
	#include "../platform/activeondx.h"
#endif

// This seems to be mostly empty space
struct DirReader {
	unsigned char unknown[3268];
	char name[50];
	unsigned char unknown2[3834];
};

// Regular "ls" mode (?)
#define NORMALDIR 0x7f

typedef struct Ambarella_FILE {
	// Unknown
}FILE;

// For now just use `int *env`
// Pointer to where to route standard out, pipes,
// IDs, etc.
typedef struct Env {
	// Unknown
}env;

// # System
void msleep(int ms);
void printf(int *env, char *fmt, ...);
void sprintf(char *string, char *fmt, ...);

// addr contains the address to allocted memory
// Not sure what "id" is, just put 1
// These functions aren't POSIX so an underscore
// is used.
int _malloc(int id, int size, void *addr);
void _free(int id, int *addr);

// # I/O
FILE *fopen(char *filename, char *mode);

// Note: fread doesn't add a null terminator.
int fread(void *buffer, unsigned long size, unsigned long count, FILE *file);
int fclose(FILE *file);
int fwrite(void *buffer, int size, int count, FILE *file);
int gpio(int id, int *b, int *c, int *d);

// mkdir: Not used anywhere in the code yet, but useful when writing asm.
int mkdir(char *folder);

// Hijack lu_util command
void lu(int *env, int count, char *hijack[]);

// Note: "*.*" wildcard works
// See apps.c for usage
int openDir(char *directory, char attribute, struct DirReader *data);
int nextFile(struct DirReader *data);

// This can be used to hijack all the "t *"
// commands, not just set exposure.
// TODO: Better name - what does "t" stand for?
void setExp();

// Paramters are passed via the ambsh parser.
// Usage is exactly what you would expect.
//void start(int *env, int argc, char *argv[]);
#endif