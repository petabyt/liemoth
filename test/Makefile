# Default flags, if not set.
p ?= activeondx
d ?= /media/dan/8765-4321/
l ?= $(shell awk '/MEM_LOADER/{print $$3}' <../platform/${p}.h)

ASMFLAGS := -c -include "../platform/${p}.h"
CC := arm-none-linux-gnueabi-

all:
# Loader
	@${CC}gcc ${ASMFLAGS} ${INCLUDE} -o main.o main.S
	@${CC}ld -Bstatic main.o -Ttext ${l} -o main.elf
	@${CC}objcopy -O binary main.elf main.o

# Dump some things
	@hexdump -C main.o
	@ls -l main.o

# Write the binary
	@gcc ../ashp/ashp.c script.c ${INCLUDE} -o gen
	@./gen ${l} > ${d}autoexec.ash
	@rm gen *.o *.elf

help:
	@echo "make l=ADDRESS d=LOCATION p=PLATFORM"
