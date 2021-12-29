# This script is preprocessed by ashp
# at compile time.

# See ashp/ for more information.

# Regular onboot loader
[ifndef "FANCY"]
	# Write a memory hijack, if specified
	[ifdef "HIJACK"]
		[writebin "hijack.o" HIJACK]
	[end]
		
	# Be nice, allow other processes to load in
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

	# Default parameter
	[ifdef "MEM_PARAM"]
		writel {MEM_PARAM} 0
	[end]

	[ifndef "NOSTARTUP"]
		cardmgr [ifdef "LOG"]> log[end] 
	[end]

	[ifdef "SUSPEND"]
		resume {P_CTRLMAN}
	[end]

	# Log A drive contents
	#ls a:/ > log

	# This runs copied reference to script
	#d:/ahdk/a.ash

	#savebin d:\memdump.bin 0xC0000000 l 0x8000000
[end]

# Fancy SD card controlled loader
# This is experimental
# Pull out SD, put in to run AHDK.
[ifdef "FANCY"]
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

