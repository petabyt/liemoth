p ?= activeondx
d ?= /media/dan/8765-4321/

# Using a C makefile would be alternative, but this is spiffier
MEM_LOADER := $(shell awk '/MEM_LOADER/{print $$3}' <../platform/${p}.h)
MEM_MAIN := $(shell awk '/MEM_MAIN/{print $$3}' <../platform/${p}.h)
INCLUDE := -include "../platform/${p}.h"

CFLAGS := -std=c99 -march=armv6 -c -mthumb -nostartfiles -nostdlib -ffunction-sections
ASMFLAGS := -c -Wa,-mthumb

CC := arm-none-eabi-

default: all clean

all:
# Write initial files
	@touch ${d}ahdk/ahdk.bin
	@touch ${d}ahdk/a.ash
	@touch ${d}ahdk/font.bin
	@touch ${d}autoexec.ash

# Convert linker script
	@${CC}gcc -include "../platform/${p}.h" -P -E link.c -o link.ld
	
# Loader
	@${CC}gcc ${ASMFLAGS} ${INCLUDE} -o loader.o loader.S
	@${CC}ld -Bstatic loader.o -Ttext ${MEM_LOADER} -o loader.elf
	@${CC}objcopy -O binary loader.elf loader.o

# Main AHDK
	@${CC}gcc ${ASMFLAGS} ${INCLUDE} main.S -o mains.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} screen.c  -o screen.o
	@${CC}gcc ${CFLAGS} -O1 ${INCLUDE} lib.c -o lib.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} -fdata-sections main.c -o main.o
	@${CC}ld -Bstatic --gc-sections mains.o main.o screen.o -T link.ld -o main.elf
	@${CC}objcopy -O binary main.elf main.o

# Dump some things
	@echo "Loader:"
	@hexdump -C loader.o
	@echo "Main:"
	@hexdump -C main.o | head
	@ls -l main.o

# Write AHDK
	@cat main.o > ${d}ahdk/ahdk.bin
	@cc ../ashp/main.c script.c ${INCLUDE} -o gen.o
	@./gen.o > ${d}autoexec.ash

# Build font
font:
	@${CC}gcc ${CFLAGS} font.c -o font.o
	@${CC}objcopy -O binary font.o ${d}ahdk/font.bin
	@rm font.o

clean:
	@rm -f *.o *.elf link.ld
