	.text
	.global main
	.type main, %function
	
main:	push {r4-r7, lr}
	mov r5, r0		// argc in r5
	mov r4, r1		// argv in r4
	mov r7, #0

loops:	ldr r6, [r4]		// cicla le stringhe
	mov r2, #0

loopc:	ldrb r7, [r6], #1		
	cmp r7, #0
	addne r2, #1
	bne loopc

	ldr r1, [r4], #4
	ldr r0, =fmt
	bl printf		
	subs r5, #1		// r5-- e setto i flag
	bne loops
	

	pop {r4-r7, pc}

	.data
fmt:	.string "la stringa %s è lunga %d caratteri\n"
