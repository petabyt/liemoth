# All make build system is deprecated - 
# See https://github.com/petabyt/ahdk/blob/bdd506823b3da6a8c4889ca072c497e5189b12d3/ahdk/Makefile
# for final version

# These are default if not defined values
# platform, directory, ashp flag
p ?= activeondx
d ?= ~/temp
f ?= SUSPEND LOG

file := test.c

CFLAGS := -O0 -include "../platform/${p}.h" '-DFLAGS="${f}"' '-DPLATFORM="${p}"' '-DDIRECTORY="${d}"'

ifdef NOCLEAN
CFLAGS += -DNOCLEAN
endif

ifdef NOWRITE
CFLAGS += -DNOWRITE
endif

COMP := ${CC} ${CFLAGS} Build.c -o build.o

ahdk clean font:
	@${COMP}
	@./build.o $@

minimal:
	@${COMP}
	@./build.o $@ ${file}

minimalonly:
	@${COMP} -D STANDALONE
	@./build.o $@ ${file}

# Spit out log file
log:
	@cat ${d}/log

# Write initial files
init:
	@mkdir ${d}/ahdk
	@touch ${d}/ahdk/ahdk.bin
	@touch ${d}/ahdk/a.ash
	@touch ${d}/ahdk/font.bin
	@touch ${d}/autoexec.ash

help:
	@echo 'Examples:'
	@echo ' make p=activeondx d=/media/user/mycam       (Assumes files are set up)'
	@echo ' make setup p=activeondx d=/media/user/mycam (Setup and compile on new camera)'
	@echo ' make initial                                (Set up file structure)'
	@echo ' make font                                   (Set up the font on the camera)'
	@echo 'Send ashp script flags:'
	@echo ' make "f=LOG FANCY"'
	@echo 'GoPro test: make "f=SUSPEND LOG" p=hero3p file=gopro.c minimal'
