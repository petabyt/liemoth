p ?= activeondx
d ?= /media/dan/8765-4321/

# Using a C makefile would be alternative, but this is spiffier
MEM_LOADER := $(shell awk '/MEM_LOADER/{print $$3}' <../platform/${p}.h)
MEM_MAIN := $(shell awk '/MEM_MAIN/{print $$3}' <../platform/${p}.h)
INCLUDE := -include "../platform/${p}.h"

CFLAGS := -std=c99 -march=armv6 -c -mthumb -nostartfiles -nostdlib
ASMFLAGS := -c -Wa,-mthumb

CC := arm-none-linux-gnueabi-

all:
# Loader
	@${CC}gcc ${ASMFLAGS} ${INCLUDE} -o loader.o loader.S
	@${CC}ld -Bstatic loader.o -Ttext ${MEM_LOADER} -o loader.elf
	@${CC}objcopy -O binary loader.elf loader.o

# Entry function
	@${CC}gcc ${ASMFLAGS} ${INCLUDE} main.S -o mains.o

# Main AHDK
	@${CC}gcc ${CFLAGS} -O1 ${INCLUDE} lib.c -o lib.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} main.c -o main.o
	@${CC}ld -Bstatic mains.o main.o -Ttext ${MEM_MAIN} -o main.elf
	@${CC}objcopy -O binary main.elf main.o

# Dump some things
	@echo "Loader:"
	@hexdump -C loader.o
	@echo "Main:"
	@hexdump -C main.o | head
	@ls -l main.o

# Write AHDK
	@cat main.o > ${d}AHDK.BIN
	@gcc ../ashp/main.c script.c ${INCLUDE} -o gen
	@./gen > ${d}autoexec.ash
	@rm gen *.o *.elf

# Build font
font:
	@${CC}gcc ${CFLAGS} font.c -o font.o
	@${CC}objcopy -O binary font.o ${d}FONT.BIN
	@rm font.o
