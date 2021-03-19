# Porting notes:
Strings are stored under functions.  
I personally used Ghirda (free open-source)
- msleep: Search "Usage: %s [sec]\n"
- fread, fopen, fclose: Search "%s: '%s' %s!\n" and "Usage: %s [file]\n"
- sprintf: Search "cannot load file '%s'!"
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
