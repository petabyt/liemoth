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
	int a;
	int b;
}FILE;

typedef struct Env {
	// Unknown
}env;

// System
void msleep(int ms);
void printf(int *env, const char *fmt, ...);
void sprintf(char *string, const char *fmt, ...);

// I/O
FILE *fopen(char *filename, char *mode);
// Note: fread doesn't add a null terminator.
int fread(void *buffer, unsigned long size, unsigned long count, FILE *file);
int fclose(FILE *file);
int fwrite(char *buffer, int size, int count, FILE *file);
int gpio(int id, int *b, int *c, int *d);
int mkdir(char *folder);
void lu(int *env, int count, char *hijack[]);

// Note: "*.*" wildcard works
int openDir(char *asd, char attr, struct DirReader *data);
int nextFile(struct DirReader *data);

// Memory (TODO: parameters)
int malloc();
void free();

// Camera API
void setExp(int *env, char *hijack[]);

#endif
