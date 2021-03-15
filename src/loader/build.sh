# ./build.sh activeondx
cd ..
gcc cli.c main.c -include "../platform/$1.h" -o cli
cd loader

../cli start.ash
