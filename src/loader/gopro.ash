# Early Gopro models script chooser
# 7x7 screen
t app fp_string 'AHDK   Loading'
sleep 4
t app fp_string 'AHDK   0SCR 1 SCR 2  SCR 3  '
sleep 3
if (cd d:\); then
	echo a
else
	sleep 1
	t app fp_string 'script 1'
	while true; do
		sleep 100
	done
fi
t app fp_string 'AHDK   SCR 1  0SCR 2 SCR 3  '
sleep 3
if (cd d:\); then
	echo a
else
	sleep 1
	t app fp_string 'script 2'
	while true; do
		sleep 100
	done
fi
t app fp_string 'AHDK   SCR 1  SCR 2  0SCR 3 '
sleep 3
if (cd d:\); then
	echo a
else
	sleep 1
	t app fp_string 'script 3'
	while true; do
		sleep 100
	done
fi
sleep 1
t app fp_string '                                   '
t app fp_string 'No AHDKClick to clear'
sleep 2
