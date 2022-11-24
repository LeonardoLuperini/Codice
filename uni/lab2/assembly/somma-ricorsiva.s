	.text
	.global main
	.global ricsum
	.type main, %function
	.type ricsum, %function

main:	push {r4, r5, lr}
	mov r4, r1
	ldr r0, [r4, #8]
	bl atoi
	mov r5, r0

	ldr r0, [r4, #4]
	bl atoi
	mov r1, r5
	
	bl ricsum
	
	mov r1, r0
	ldr r0, =fmt
	bl printf

	pop {r4, r5, pc}

ricsum:	push {lr}
	cmp r1, #0
	popeq {pc}

	add r0, #1
	sub r1, #1
	bl ricsum
	pop {pc}

	.data
fmt:	.string "%d\n"
