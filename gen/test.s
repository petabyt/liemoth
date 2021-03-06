.thumb
.global _start

_start:
	
	adr r1, foo
	bl 0xc0272996 @ printf

	@ Hack an early return.
	pop {r4, pc}

foo: .string "Hey Vsauce, Michael here"
