# This loader will use buttons to load scripts.
# This is currently configured to work on GoPro Hero 3+

# This is where the GPIO hack function return is located.
# Instead of:
#  add sp, #0x1c
#  mov r0, r6
# We inject:
#  ldrb r0, [sp, 0x10]
#  add sp, #0x1c
# With 0x10 being the output var.

[define HALT "while true; do; sleep 100; done"]

# Now write the preassembled 8 byte binary
[writeBin "gpioasm.bin" MEM_GPIOHACK]

# Predefined script names. Max 5 chars
[define firstName "SCR 1"]
[define secondName "SCR 2"]
[define thirdName "SCR 3"]

suspend {P_CTRLMAN}
suspend {P_BUTTONTASKA}
suspend {P_BUTTONTASKB}
while true; do
	t app fp_string 'AHDK    {firstName} {secondName}  {thirdName}  EXIT '
	# While mode button not up
	while (t gpio {P_MODEBTN}); do
		# If select button down
		if (t gpio {P_SELBTN}); then
			t app fp_string 'HELLO  WORLD'
			sleep 5
			t app fp_string 'AHDK    SCR 1 SCR 2  SCR 3  EXIT '
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
			{HALT}
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
			suspend {P_BUTTONTASKA}
			suspend {P_BUTTONTASKB}

			resume {P_CTRLMAN}
			
			# We sadly don't have GOTO or BREAK,
			# but we can kill the autoexec.ash task
			kill {P_AUTOEXECTASK}
		fi
	done
	until (t gpio {P_MODEBTN}); do
		a
	done
done
