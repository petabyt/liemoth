# Regular onboot loader

[ifndef "FANCY"]
	[ifdef "LOG"]touch log[end]#
	#sleep 1
	#suspend {P_CTRLMAN}
	#sleep 1
	[writeBin "loader.o" MEM_LOADER]
	cardmgr [ifdef "LOG"]> log[end]#
	#resume {P_CTRLMAN}

	# This runs copied reference to script
	#d:/ahdk/a.ash
[end]

# Fancy SD card controlled loader
[ifdef "FANCY"]
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

