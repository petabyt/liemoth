.global printf
printf:
	push    {r11, lr}
	ldr     r11, =(AMB_PRINTF + 1)
	mov     lr, pc
	bx      r11
	pop     {r11, lr}
	bx      lr