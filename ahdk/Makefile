# These are default if not defined values
# platform, directory, ashp flag
p ?= activeondx
d ?= /media/dan/8765-4321/
f ?= SUSPEND LOG

ifeq ($(wildcard $(d)),)
$(error SD card not inserted)
endif

INCLUDE := -include "../platform/${p}.h"

# Using a "Preprocessed Makefile" would be alternative, but this is spiffier
MEM_LOADER := $(shell awk '/MEM_LOADER/{print $$3}' <../platform/${p}.h)
MEM_MAIN := $(shell awk '/MEM_MAIN/{print $$3}' <../platform/${p}.h)
P_THUMB := $(shell awk '/P_THUMB/{print $$2}' <../platform/${p}.h)

# Try to get font binary size for C
FONTSIZE := $(shell ls -l $(d)ahdk/font.bin | awk '{print $$5}')

CFLAGS := -std=c99 -c -ffreestanding -DFONTSIZE=$(FONTSIZE)
ifdef REMOVEUNUSED
CFLAGS += -fdata-sections -ffunction-sections
endif

# ARM needs -O2 for proper ldr instructions
ifeq ($(P_THUMB),)
CFLAGS += -marm -O2
else
CFLAGS += -mthumb -O2
endif

LDFLAGS := -Bstatic
ifdef REMOVEUNUSED
LDFLAGS += --gc-sections
endif

ASMFLAGS := -c

# Try to use TCC, faster
HOSTCC := tcc
ifeq (, $(shell which $(HOSTCC)))
CC = gcc
endif

# Arm C compilers
CC := arm-none-eabi-
ifeq (, $(shell which $(CC)gcc))
CC = arm-none-linux-gnueabi-
endif

MAIN ?= test.c

default: loader ahdk write info clean
setup: init font loader ahdk write clean
minimal: loader minimalC write info clean

help:
	@echo 'Examples:'
	@echo ' make p=activeondx d=/media/user/mycam		(Assumes files are set up)'
	@echo ' make setup p=activeondx d=/media/user/mycam	(Setup on new camera)'
	@echo 'Send script flags:'
	@echo ' make "f=LOG FANCY"'
	@echo 'GoPro test: make "f=SUSPEND LOG" p=hero3p MAIN=test.c minimal'

# Compile with custom minimal file, not main gui
minimalC:
	@${CC}gcc ${ASMFLAGS} ${INCLUDE} main.S -o mains.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} $(MAIN) -o main.o
	@${CC}ld $(LDFLAGS) mains.o main.o -T link.ld -o main.elf
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
	@${CC}ld $(LDFLAGS) loader.o -Ttext ${MEM_LOADER} -o loader.elf
	@${CC}objcopy -O binary loader.elf loader.o

# Compile Main AHDK
ahdk:
	@${CC}gcc ${ASMFLAGS} ${INCLUDE} main.S -o mains.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} screen.c  -o screen.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} apps.c  -o apps.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} lib.c -o lib.o
	@${CC}gcc ${CFLAGS} ${INCLUDE} main.c -o main.o
	@${CC}ld $(LDFLAGS) mains.o main.o screen.o apps.o lib.o -T link.ld -o main.elf
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
