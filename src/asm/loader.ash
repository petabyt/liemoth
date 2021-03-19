# Inject assembly into cardmgr command
[writeBin "loader.o" MEM_LOADER]

touch log
writeb 0xc012d5ac 0x0
suspend 18
cardmgr >> log
writeb 0xc012d5ac 0x1
cardmgr
resume 18
