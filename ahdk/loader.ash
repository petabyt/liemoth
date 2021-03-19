# Inject assembly into cardmgr command
[writeBin "loader.o" MEM_LOADER]

sleep 2
rm log
touch log
# suspend 18, main task.
suspend 18
# Main AHDK function.
writeb 0xc012d5ac 0x0
cardmgr >> log
# Clear screen
writeb 0xc012d5ac 0x1
cardmgr
resume 18
