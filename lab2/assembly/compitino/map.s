	.text
	.global map
	.type map, %function

map: 	push {r4, r5, r6, lr}
	mov r4, r0
	mov r5, r1
	mov r6, #0

loop: 	cmp r5, #0
	moveq r0, r6 
	popeq {r4, r5, r6, pc}
	
	ldr r0, [r4], #4
	bl myatoi
	
	cmp r0, #-1
	subeq r5, #1
	beq loop

	asr r0, r0, #2
	add r6, r6, r0
	b loop



	pop {r4, r5, r6, pc}
	
