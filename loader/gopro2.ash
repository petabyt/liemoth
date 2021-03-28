# This loader will use buttons

# Hijack the GPIO function to return 1/0 value

# ldrb r0, [sp, 0x10] (status var)
writeb 0xc01505d4 0x10
writeb 0xc01505d5 0x0
writeb 0xc01505d6 0xdd
writeb 0xc01505d7 0xe5

# add sp, #0x1c (pop stack)
writeb 0xc01505d8 0x1c
writeb 0xc01505d9 0xd0
writeb 0xc01505da 0x8d
writeb 0xc01505db 0xe2

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
