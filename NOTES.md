# SRE (Software Reverse Engineering)
I would recommend using Ghirda. Here are some tips:
- To get a RAM dump: `savebin d:\memdump.bin 0xC0000000 l 0x8000000`  
- In Ghirda, remember to set base address to `0xC0000000`.  
- For Ambarella A12, use `0xA0000000`
- For A7, set architecture to Arm v6 little

# Porting guide and notes:
- Strings are often stored under functions.  
- msleep: Search "Usage: %s [sec]\n"
- fread, fopen, fclose: Search "%s: '%s' %s!\n" and "Usage: %s [file]\n"
- sprintf: Search "cannot load file '%s'!"
- card info: "slot '%c' info\n" and "memory + I/O combo"
- screen buffer:
```
# Get system debug startup log
touch foo
echo '' > foo
t disp >> foo
t disp info >> foo
t disp csc_info >> foo
dmesg dsp_debug -100 >> foo
dmesg dsp -100 >> foo
dmesg rtos -100 >> foo
```
Search "0xc" in foo.
- cardmgr: Search "\tinfo - information of card\n"
- printf: In cardmgr function.
- GPIO Button Codes:
```
# Press desired button a bunch of times
# This is a very bad method
touch foo
while true; do
	t gpio dump >> foo
	sleep 1
done
```
- GPIO function: "gpio%d:\t %s %d %s\n" (it should accept 4 parameters?)
- Dir Openers: "start time = %d ms\n"

# Gopro
- fpstring: Search "fp_string"

# TODO:
- Understand the screen buffer system and make a new  
buffer, not writing to some random one
- Real time code execution (no restart)
- Power saving options
