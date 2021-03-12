# ./build.sh activeondx
gcc loader.c ../main.c -include "../../platform/$1.h" -o loader
./loader
rm loader
