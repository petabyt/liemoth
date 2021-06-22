# This is a ashp preprocessed script.
# See ashp/

sleep 1
[writebin "main.o" MEM_LOADER]
touch log
cardmgr > log
#savebin d:\memdump.bin 0xC0000000 l 0x8000000