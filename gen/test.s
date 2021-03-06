# Load address of menu text
ldr r0, =0xc156bea6
mov r1, #'A'

# Store r1 into address in r0
strb r1, [r0]

# Hack an early return.
pop {r4, pc}
