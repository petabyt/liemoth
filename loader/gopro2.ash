# This loader will use buttons to load
# scripts.

# This is where the GPIO hack function return is located.
# Instead of:
#  add sp, #0x1c
#  mov r0, r6
# We inject:
#  ldrb r0, [sp, 0x10]
#  add sp, #0x1c
# With 0x10 being the value variable.

# Now write the preassembled 8 byte binary
[writeBin "gpioasm.bin" MEM_GPIOHACK]

[define P_MODEBTN 139]
[define P_SELBTN 140]

suspend {P_CTRLMAN}
while true; do
	if (t gpio {P_SELBTN}); then
		t app fp_string '1'
	else
		if (t gpio {P_MODEBTN}); then
			t app fp_string '2'
		else
			t app fp_string '3'
		fi
	fi
	sleep 1
done
