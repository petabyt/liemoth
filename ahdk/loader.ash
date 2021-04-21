# Regular onboot loader
[ifeq "FANCY" 0]
	sleep 1
	suspend {P_CTRLMAN}
	sleep 1
	[writeBin "loader.o" MEM_LOADER]
	cardmgr
	resume {P_CTRLMAN}

	# This runs another reference to a script
	d:/ahdk/a.ash
[end]

# Fancy SD card controlled loader
[ifeq "FANCY" 1]
	# This is experimental
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
[end]
