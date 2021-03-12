# Tested on Activeon DX
loop 5; do
	if (cd d:\); then
		echo a
	else
		[genUnicode "AHDK HACK" MEM_NOCARD]
		
		# Max shutter speed (8 sec), ISO 6400
		t ia2 -warp 0
		t ia2 -ae exp 6400 1
		sleep 10000
	fi
	sleep 1
done
