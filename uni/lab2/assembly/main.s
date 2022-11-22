	.text
	.global main
	.type main, %function
	
main:	push {lr}
	
	ldr r0, [r1, #4]
	bl atoi
	push {r0}
	bl fib
	
	mov r2, r0
	pop {r1}
	ldr r0, =fmt
	bl printf

	pop {pc}

	.data
fmt:	.string "fib di %d è %d\n"
