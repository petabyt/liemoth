# This script is preprocessed by ashp
# at compile time.

# See ashp/ for more information.

# Regular onboot loader
[ifndef "FANCY"]
	# Allow other processes to load in
	sleep 1

	# Setup
	[ifdef "LOG"]touch log[end] 
	echo a > d:/ahdk/a.ash

	[ifdef "SUSPEND"]
		suspend {P_CTRLMAN}
	[end]
	
	[writebin "loader.o" MEM_LOADER]

	# Write the GUI hijack code (if it exists)
	[ifdef "MEM_TRIGGER"]
		[writebin "button.o" MEM_TRIGGER]
	[end]
	
	[ifdef "MEM_PARAM"]
		writeb {MEM_PARAM} 0
	[end]
	
	cardmgr [ifdef "LOG"]> log[end] 

	[ifdef "SUSPEND"]
		resume {P_CTRLMAN}
	[end]

	[ifndef "MEM_TRIGGER"]
		cardmgr > log
	[end]

	# This runs copied reference to script
	d:/ahdk/a.ash
[end]

# Fancy SD card controlled loader
[ifdef "FANCY"]
	# This is experimental
	# Pull out SD, put in to run AHDK.
	[writebin "loader.o" MEM_LOADER]
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

