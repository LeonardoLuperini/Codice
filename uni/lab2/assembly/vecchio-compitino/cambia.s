	.text
	.global cambia
	.type cambia, %function

cambia:	//r0 = char, r1 = pnt from, r2 = pnt to, r3 = N
	push {r4, r5}
	mov r5, #0

loop:	cmp r3, #0
	beq exit

	ldrb r4, [r1, r5]
	cmp r0, r4
	ldreqb r0, [r2, r5]
	beq exit	
	
	add r5, r5, #1
	sub r3, r3, #1
	b loop

exit: 	pop {r4, r5}
	mov pc, lr
