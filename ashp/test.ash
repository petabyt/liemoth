# This hacks text in a custom location
[define HACK_LOC 0xc156bea6]
[genUnicode "Hello World" HACK_LOC]

# Logic Test
# Should produce a, d, e
[ifeq "HACK_LOC" 0xc156bea6]
	[ifdef ASD]
		echo 'a'
	[end]
	echo 'a'
	[ifeq "HACK_LOC" 123]
		echo 'b'
	[end]
	[ifdef "HACK_LOC"]
		echo 'd'
	[end]
	[ifndef "HACK_LOC"]
		echo 'c'
	[end]
	echo 'e'
[end]
echo '{HACK_LOC}'

