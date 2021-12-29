#ifndef STDLIB_H
#define STDLIB_H

// Ambarella FILE may be non-POSIX
typedef struct Ambarella_FILE {
	// Unknown
}FILE;

void *malloc(unsigned int size);
void free(void *addr);
void msleep(int ms);

FILE *fopen(char *filename, char *mode);
int fread(void *buffer, unsigned long size, unsigned long count, FILE *file);
int fclose(FILE *file);
int fwrite(void *buffer, int size, int count, FILE *file);

// Technically not POSIX but close enough
void printf(int *env, char *fmt, ...);
void sprintf(char *string, char *fmt, ...);

#endif
