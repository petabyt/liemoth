# Pull out SD, put in to run AHDK.
[writeBin "loader.o" MEM_LOADER]
while true; do
	# Wait until card out
	sleep 1
	while (cd d:\); do
		sleep 1
	done
	# Wait until card in
	until (cd d:\); do
		sleep 1
	done
	# Start AHDK
	suspend {P_CTRLMAN}
	cardmgr
	resume {P_CTRLMAN}
done
