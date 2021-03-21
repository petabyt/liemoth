# Inject assembly into cardmgr command
[writeBin "loader.o" MEM_LOADER]
# Patch for GPIO function (only works on Activeon DX)
writeb 0xc0108018 0x04
writeb 0xc0108019 0x98
writeb 0xc010801a 0x07
writeb 0xc010801b 0xb0
sleep 2
# GPIO patch
touch log
# suspend 18, main task.
suspend 18
# Main AHDK function.
writeb 0xc012d5ac 0x0
cardmgr
# Clear screen
writeb 0xc012d5ac 0x1
cardmgr
resume 18
