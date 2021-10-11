ARMCC=arm-none-eabi
CFLAGS=-c -nostdlib -I../ -I../../ahdk/ -Wno-coverage-mismatch -fno-builtin

all:
	$(CC) ../gen.c -o gen
	./gen > head.c
	$(ARMCC)-gcc $(CFLAGS) head.c -o head.elf
	$(ARMCC)-gcc $(CFLAGS) test.c -o test.elf
	$(ARMCC)-ld -T ../link.ld test.elf head.elf -o main.o
	$(ARMCC)-objcopy -O binary main.o foo.lm

clean:
	rm -rf gen head.c *.elf *.o *.lm *.out
