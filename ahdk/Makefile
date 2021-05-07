# These are default if not defined values
# platform, directory, flag
p ?= activeondx
d ?= /media/dan/8765-4321/
f ?= SUSPEND LOG

INCLUDE := -include "../platform/${p}.h"

# Using a "Preprocessed Makefile" would be alternative, but this is spiffier
MEM_LOADER := $(shell awk '/MEM_LOADER/{print $$3}' <../platform/${p}.h)
MEM_MAIN := $(shell awk '/MEM_MAIN/{print $$3}' <../platform/${p}.h)
P_THUMB := $(shell awk '/P_THUMB/{print $$2}' <../platform/${p}.h)

# Try to get font binary size for C (error is fine)
FONTSIZE := $(shell ls -l $(d)ahdk/font.bin | awk '{print $$5}')

CFLAGS := -std=c99 -c -ffreestanding -DFONTSIZE=$(FONTSIZE)
ifeq ($(P_THUMB),)
	# This needs -O2 for proper ldr instructions
	CFLAGS += -marm -O2
else
	CFLAGS += -mthumb -O2
endif

ASMFLAGS := -c

HOSTCC := cc

# arm-none-linux-gnueabi- wil also work
CC := arm-none-eabi-

default: loader ahdk write info clean
setup: init font loader ahdk write clean
demo: loader testC write info clean

help:
	@echo 'Examples:'
	@echo ' make p=activeondx d=/media/user/mycam		(Assumes files are set up)'
	@echo ' make setup p=activeondx d=/media/user/mycam	(Setup on new camera)'
	@echo 'Send script flags:'
	@echo ' make "f=LOG FANCY"'
	@echo 'GoPro test: make f=LOG p=hero3p demo'
	@echo 'Also try HOSTCC=tcc for faster compilation'

# Compile with test.c, not main gui
testC:
	@${CC}gcc ${ASMFLAGS} ${INCLUDE} main.S -o mains.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} test.c -o main.o
	@${CC}ld -Bstatic mains.o main.o -T link.ld -o main.elf
	@${CC}objcopy -O binary main.elf main.o

# Write initial files
init:
	@touch ${d}ahdk/ahdk.bin
	@touch ${d}ahdk/a.ash
	@touch ${d}ahdk/font.bin
	@touch ${d}autoexec.ash

loader:
# Preprocess linker script
	@${HOSTCC} -include "../platform/${p}.h" -P -E link.c -o link.ld
	
# Binary loader
	@${CC}gcc ${ASMFLAGS} ${INCLUDE} -o loader.o loader.S
	@${CC}ld -Bstatic loader.o -Ttext ${MEM_LOADER} -o loader.elf
	@${CC}objcopy -O binary loader.elf loader.o

# Compile Main AHDK
ahdk:
	@${CC}gcc ${ASMFLAGS} ${INCLUDE} main.S -o mains.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} screen.c  -o screen.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} mainmenu.c  -o mainmenu.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} lib.c -o lib.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} main.c -o main.o
	@${CC}ld -Bstatic mains.o main.o screen.o mainmenu.o lib.o -T link.ld -o main.elf
	@${CC}objcopy -O binary main.elf main.o

# Dump some helpful info
info:
	-@echo "Loader:"
	-@hexdump -C loader.o
	-@echo "Main:"
	-@hexdump -C main.o | head
	-@ls -l main.o

# Write AHDK
write:
	-@cp main.o ${d}ahdk/ahdk.bin
	@${HOSTCC} ../ashp/main.c script.c ${INCLUDE} -o gen.o
	@./gen.o $(f) > ${d}autoexec.ash

# Build font
font:
	@curl https://raw.githubusercontent.com/petabyt/font/master/font.h > font.c
	@${CC}gcc ${CFLAGS} font.c -o font.o
	@${CC}objcopy -O binary font.o ${d}ahdk/font.bin
	@rm font.o font.c

clean:
	@rm -f *.o *.elf link.ld
