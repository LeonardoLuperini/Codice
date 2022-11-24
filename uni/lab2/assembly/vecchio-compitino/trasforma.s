	.text
	.global trasforma
	.type trasforma, %function

trasforma: //r0 = pnt s, r1 = pnt from, r2 = pnt to, r3 = N 
	push {r4, lr}
	mov r4, r0

loop: 	ldrb r0, [r4]
	cmp r0, #0
	beq exit

	push {r1-r3}
	bl cambia
	pop {r1-r3}
	
	strb r0, [r4]
	add r4, #1
	b loop

exit:	pop {r4, pc}
