	.text
	.global main
	.type main, %function

main:	push {r4, r5, r6, lr}
	sub r0, #1
	add r1, #4
	
	mov r4, #0
	mov r5, r1
	mov r6, r0

loop:	cmp r6, #0
	beq exit
	ldr r0, [r5], #4
	bl atoi
	add r4, r0
	sub r6, #1
	b loop

exit: 	mov r1, r4
	ldr r0, =fmt
	bl printf

	mov r0, #0
	pop {r4, r5, r6, pc}

	.data
fmt: 	.string "la somma è %d\n"
