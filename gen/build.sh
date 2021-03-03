arm-none-linux-gnueabi-gcc -c -mno-thumb-interwork test.s
arm-none-linux-gnueabi-objcopy -O binary -j .text test.o test.o
hexdump -C test.o
tcc -run main.c > /media/dan/8765-4321/autoexec.ash
rm test.o
