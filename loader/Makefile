p ?= hero3p
f ?= gopro2.ash

all:
	@${CC} ../ashp/main.c loader.c -include "../platform/${p}.h" -o loader.o
	@./loader.o ${f}
	@rm *.o

script:
	echo "t app fp_string 'script 1'" > scr_1.ash
	echo "t app fp_string 'script 2'" > scr_2.ash
	echo "t app fp_string 'script 3'" > scr_3.ash
