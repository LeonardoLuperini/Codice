	.text
	.global myatoi
	.type myatoi, %function

myatoi: 
	mov r3, r0
	mov r0, #0
	
loop:	ldrb r1, [r3], #1
	
	cmp r1, #0
	moveq pc, lr

	cmp r1, #48
	movlt r0, #-1
	movlt pc, lr
	
	cmp r1, #57
	movgt r0, #-1
	movgt pc, lr
	
	mov r12, #10
	mul r0, r0, r12
	add r0, r0, r1
	b loop

	


