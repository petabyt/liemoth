ARMCC=arm-none-eabi
CFLAGS=-c -nostdlib

all:
	$(CC) gen.c -o gen
	./gen > head.c
	$(ARMCC)-gcc $(CFLAGS) head.c -o head.elf
	$(ARMCC)-gcc $(CFLAGS) test.c -o test.elf
	$(ARMCC)-ld -T link.ld test.elf head.elf
