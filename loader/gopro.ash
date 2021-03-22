# Early Gopro models script chooser
# Needs 7x7 front panel and commands.
# If files aren't found, it's okay,
# comments will be left in the output.

# Suspend main task. Ambsh will be fine.
suspend {P_CTRLMAN}
t app fp_string 'AHDK'
loop 5; do
	# Wait if SD in
	if (cd d:\); then
		sleep 1
	else
		# Else, SD out, and user wants to run script.
		t app fp_string 'AHDK   0SCR 1 SCR 2  SCR 3  '
		sleep 3
		if (cd d:\); then
			resume {P_CTRLMAN}
			sleep 2
			[writeFile "scr_1.ash"]
			while true; do
				sleep 100
			done
		fi
		t app fp_string 'AHDK   SCR 1  0SCR 2 SCR 3  '
		sleep 3
		if (cd d:\); then
			resume {P_CTRLMAN}
			sleep 2
			[writeFile "scr_2.ash"]
			while true; do
				sleep 100
			done
		fi
		t app fp_string 'AHDK   SCR 1  SCR 2  0SCR 3 '
		sleep 3
		if (cd d:\); then
			resume {P_CTRLMAN}
			sleep 2
			[writeFile "scr_3.ash"]
			while true; do
				sleep 100
			done
		fi
		sleep 1
		t app fp_string 'NO     SCRIPT                      '
		sleep 2
	fi
done
resume {P_CTRLMAN}
# No changes made.
