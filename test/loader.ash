#[writeBin "main.o" MEM_LOADER]
#sleep 2
#suspend {P_CTRLMAN}
[writeBin "arm.o" MEM_LOADER]
touch logs
cardmgr > logs
#sleep 1
#resume {P_CTRLMAN}
