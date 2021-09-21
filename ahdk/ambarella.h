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

// For now just use `int *env`
// Pointer to where to route standard out, pipes,
// IDs, etc.
typedef struct Env {
	// Unknown
}env;

// addr contains the address to allocted memory
// "id" may mean where to allocate. 1 is default value.
int ambaMalloc(int id, int size, void *addr);
void ambaFree(int id, void *addr);

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
// commands, not just set exposure. (?)
// TODO: Better name - what does "t" stand for?
void setExp();

// Paramters are passed via the ambsh parser.
// Usage is exactly what you would expect.
//void start(int *env, int argc, char *argv[]);
#endif