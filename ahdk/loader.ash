# Regular onboot loader



[ifndef "FANCY"]
	[ifdef "LOG"]touch log[end]#

	[ifdef "WAIT"]
		sleep 1
		suspend {P_CTRLMAN}
		sleep 1
	[end]
	
	[writeBin "loader.o" MEM_LOADER]
	cardmgr [ifdef "LOG"]> log[end]#
	[ifdef "WAIT"]
		#resume {P_CTRLMAN}
	[end]

	# This runs copied reference to script
	d:/ahdk/a.ash
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

