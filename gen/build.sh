@ Assemble at start address "0xc012d5d4", MEM_CARDMGR

arm-none-linux-gnueabi-gcc -c -o test.o test.s
arm-none-linux-gnueabi-ld -Bstatic test.o -Ttext 0xc012d5d4 -o test.elf
arm-none-linux-gnueabi-objcopy -O binary test.elf test.o

hexdump -C test.o
tcc -run main.c > /media/dan/8765-4321/autoexec.ash
rm test.o
rm test.elf
