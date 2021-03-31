# This loader will use buttons to load scripts.

# This is where the GPIO hack function return is located.
# Instead of:
#  add sp, #0x1c
#  mov r0, r6
# We inject:
#  ldrb r0, [sp, 0x10]
#  add sp, #0x1c
# With 0x10 being the outputle.

# Now write the preassembled 8 byte binary
[writeBin "gpioasm.bin" MEM_GPIOHACK]

[define P_MODEBTN 139]
[define P_SELBTN 140]

[define firstName "SCR 1"]
[define secondName "SCR 2"]
[define thirdName "SCR 3"]

# We sadly don't have GOTO or BREAK,
# but we can kill the autoexec.ash task
[define AUTOEXECTASK 59]

suspend {P_CTRLMAN}
suspend 17
suspend 16
while true; do
	t app fp_string 'AHDK    {firstName} {secondName}  {thirdName}  EXIT '
	# While mode button not up
	while (t gpio {P_MODEBTN}); do
		# If select button down
		if (t gpio {P_SELBTN}); then
			resume {P_CTRLMAN}
			sleep 5
			t app fp_string 'SCRIPT1'
			while true; do
				sleep 100
			done
		fi
	done
	# Wait until button is up
	until (t gpio {P_MODEBTN}); do
		# Just send an invalid command.
		# The script won't quit.
		a
	done
	t app fp_string 'AHDK   {firstName}   {secondName} {thirdName}  EXIT '
	while (t gpio {P_MODEBTN}); do
		if (t gpio {P_SELBTN}); then
			resume {P_CTRLMAN}
			sleep 5
			t app fp_string 'SCRIPT2'
			while true; do
				sleep 100
			done
		fi
	done
	until (t gpio {P_MODEBTN}); do
		a
	done
	t app fp_string 'AHDK   {firstName}  {secondName}   {thirdName} EXIT '
	while (t gpio {P_MODEBTN}); do
		if (t gpio {P_SELBTN}); then
			resume {P_CTRLMAN}
			sleep 5
			t app fp_string 'SCRIPT3'
			while true; do
				sleep 100
			done
		fi
	done
	until (t gpio {P_MODEBTN}); do
		a
	done
	t app fp_string 'AHDK   {firstName}  {secondName}  {thirdName}   EXIT'
	while (t gpio {P_MODEBTN}); do
		if (t gpio {P_SELBTN}); then

			# Two button tasks. After closing, all of the previously
			# pressed button requests are opened to control manager task.
			# These are two button related tasks? Fixed it I think?
			resume 17
			resume 16
			
			resume {P_CTRLMAN}
			kill {AUTOEXECTASK}
		fi
	done
	until (t gpio {P_MODEBTN}); do
		a
	done
done
