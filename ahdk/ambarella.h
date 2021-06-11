// Universal Ambarella functions
#ifndef __AMBARELLA
#define __AMBARELLA

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

typedef struct Env {
	// Unknown
}env;

// System
void msleep(int ms);
void printf(int *env, char *fmt, ...);
void sprintf(char *string, char *fmt, ...);

// I/O
FILE *fopen(char *filename, char *mode);
// Note: fread doesn't add a null terminator.
int fread(void *buffer, unsigned long size, unsigned long count, FILE *file);
int fclose(FILE *file);
int fwrite(char *buffer, int size, int count, FILE *file);
int gpio(int id, int *b, int *c, int *d);
int mkdir(char *folder);

// Hijack lu_util command
void lu(int *env, int count, char *hijack[]);

// Note: "*.*" wildcard works
int openDir(char *asd, char attr, struct DirReader *data);
int nextFile(struct DirReader *data);

void *malloc(int a, int size, void *addrBuffer);
void free(int *addr);

// This can be used to hijack all the "t *"
// commands, not just set exposure.
// TODO: Better name
void setExp();

#endif
