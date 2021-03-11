# 1. Power on camera
# 2. If you want to run the script, take out SD card.
# 3. Hopefully the custom message will appear, script will run
# 4. Put SD card back in, take pictures

[define MEM_NOCARD 0xc156bfaa]
loop 5; do
	if (cd d:\); then
		echo a
	else
		[genUnicode "AHDK HACK" MEM_NOCARD]
		
		# Max shutter speed (8 sec), ISO 6400
		t ia2 -warp 0
		t ia2 -ae exp 6400 1
	fi
	sleep 1
done

