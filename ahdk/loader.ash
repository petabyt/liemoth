sleep 1
suspend {P_CTRLMAN}
sleep 1
[writeBin "loader.o" MEM_LOADER]
cardmgr
resume {P_CTRLMAN}
