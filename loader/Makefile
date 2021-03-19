p ?= hero3p
f ?= gopro.ash
all:
	@gcc ../ashp/cli.c ../ashp/main.c -include "../platform/${p}.h" -o ../ashp/cli
	@../ashp/cli ${f}

script:
	echo "t app fp_string 'script 1'" > scr_1.ash
	echo "t app fp_string 'script 2'" > scr_2.ash
	echo "t app fp_string 'script 3'" > scr_3.ash
