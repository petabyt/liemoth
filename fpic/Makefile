# Allocate memory, and load binary into it
p ?= activeondx
d ?= /media/daniel/8765-4321/
l ?= $(shell awk '/MEM_LOADER/{print $$3}' <../platform/${p}.h)

ASMFLAGS := -c -include "../platform/${p}.h"
CC := arm-none-eabi-

all:
# Loader
	@${CC}gcc ${ASMFLAGS} ${INCLUDE} -o main.o main.S
	@${CC}ld -Bstatic main.o -Ttext ${l} -o main.elf
	@${CC}objcopy -O binary main.elf main.o

	@${CC}gcc -mthumb-interwork -fpic $(ASMFLAGS) -marm ${INCLUDE} -o ahdk.o ahdk.c
	@${CC}ld -Bstatic ahdk.o -o ahdk.elf
	@${CC}objcopy -O binary ahdk.elf /media/daniel/8765-4321/ahdk/ahdk.bin

# Dump some things
	@hexdump -C main.o
	@ls -l main.o

# Write the binary
	@gcc ../ashp/ashp.c script.c ${INCLUDE} -o gen
	@./gen ${l} > ${d}autoexec.ash
	@rm gen *.o *.elf

help:
	@echo "make l=ADDRESS d=LOCATION p=PLATFORM"
