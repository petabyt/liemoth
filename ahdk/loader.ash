suspend {P_CTRLMAN}
[writeBin "loader.o" MEM_LOADER]
rm log
touch log
cardmgr > log
resume {P_CTRLMAN}
t app key mode
