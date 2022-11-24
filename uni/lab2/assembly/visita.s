	.text
	.global visita
	.type visita, %function

//r0 = root
visita:	push {lr}
	cmp r0, #0
	bne notnull

	ldr r0, =nul
	bl printf
	pop {pc}

notnull: push {r4} 
	mov r4, r0
	
	ldr r0, [r4, #4]
	bl visita
	
	ldr r0, [r4, #8]
	bl visita

	ldr r1, [r4]
	ldr r0, =val
	bl printf

	pop {r4, pc}


	.data
val:	.string "%d\n"
nul:	.string "NULL\n"

