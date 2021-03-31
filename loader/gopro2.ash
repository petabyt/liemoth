# This loader will use buttons

[define GPIO_HACK 0xc01505d4]

# Hijack the GPIO function to return 1/0 value
# ldrb r0, [sp, 0x10] (status var)
# add sp, #0x1c (pop stack)
[writeBin "gpioasm.bin" GPIO_HACK]

suspend 37
while true; do
	if (t gpio 140); then
		t app fp_string '1'
	else
		if (t gpio 139); then
			t app fp_string '2'
		else
			t app fp_string '3'
		fi
	fi
	sleep 1
done
