sleep 1
suspend {P_CTRLMAN}
sleep 1
[writeBin "loader.o" MEM_LOADER]
cardmgr
resume {P_CTRLMAN}

# This runs another reference to a script
d:/ahdk/a.ash
