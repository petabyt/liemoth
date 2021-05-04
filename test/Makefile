p ?= activeondx
d ?= /media/dan/8765-4321/
l ?= $(shell awk '/MEM_LOADER/{print $$3}' <../platform/${p}.h)

INCLUDE := -include "../platform/${p}.h"
ASMFLAGS := -mthumb-interwork -c -Wa,-mthumb
CC := arm-none-linux-gnueabi-

all:
# Loader
#@${CC}gcc ${ASMFLAGS} ${INCLUDE} -o main.o main.S
#@${CC}ld -Bstatic main.o -Ttext ${l} -o main.elf
#@${CC}objcopy -O binary main.elf main.o
	
	@${CC}gcc -c ${INCLUDE} -o arm.o arm.S
	@${CC}ld -Bstatic -Ttext ${l} arm.o -o arm.elf
	@${CC}objcopy -O binary arm.elf arm.o

# Dump some things
#@hexdump -C main.o
	@hexdump -C arm.o
#@ls -l main.o
	@ls -l arm.o

# Write AHDK
	@gcc ../ashp/main.c script.c ${INCLUDE} -o gen
	@./gen ${l} > ${d}autoexec.ash
	@rm gen *.o *.elf
