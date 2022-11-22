	.text
	.global main
	.type main, %function 

main:	push {r4, r5, lr}
	mov r5, r0		// argc in r5
	mov r4, r1		// argv in r4

loop:	ldr r1, [r4], #4	// r1 = *r4, r4 += 4
	ldr r0, =fmt		
	bl printf		
		
	subs r5, #1		// r5-- e setto i flag
	bne loop

	pop {r4, r5, pc}

	.data
fmt:	.string	"(printf) %s\n"
