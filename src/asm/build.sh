# Main building script. Use as
# `bash build.sh activeondx`

# Assemble at start address "0xc012d5d4", MEM_CARDMGR

# Grab desired loader location from header file
MEM_LOADER=`awk '/MEM_LOADER/{print $3}' <../../platform/$1.h`
MEM_MAIN=`awk '/MEM_MAIN/{print $3}' <../../platform/$1.h`

# Assemble the loader
arm-none-linux-gnueabi-gcc -c -Wa,-mthumb -include "../../platform/$1.h" -o loader.o loader.S
arm-none-linux-gnueabi-ld -Bstatic loader.o -Ttext $MEM_LOADER -o loader.elf
arm-none-linux-gnueabi-objcopy -O binary loader.elf loader.o

# -mthumb -nostartfiles -nostdlib
arm-none-linux-gnueabi-gcc -c -Wa,-mthumb -include "../../platform/$1.h" -o main.o main.S
arm-none-linux-gnueabi-ld -Bstatic main.o -Ttext $MEM_MAIN -o main.elf
arm-none-linux-gnueabi-objcopy -O binary main.elf main.o

# Run the ambsh generator.
echo "Loader:"
hexdump -C loader.o
echo "Main:"
hexdump -C main.o

gcc ../main.c script.c -include "../../platform/$1.h" -o gen
./gen > /media/dan/8765-4321/autoexec.ash
rm gen loader.o loader.elf main.o main.elf
