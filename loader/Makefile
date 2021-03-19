p ?= hero3p
all:
	@gcc ../ashp/cli.c ../ashp/main.c -include "../platform/${p}.h" -o ../ashp/cli
	@../ashp/cli start.ash
