	.text
	.global fib
	.type fib, %function

fib:	push {lr}

	cmp r0, #1	// Caso base
	pople {pc}

	sub r0, r0, #1	// r0 = n-1
	push {r0}	// Salvo n-1
	bl fib		// Caso ricorsivo n-1
	pop {r1}	// Riprendo n-1
	push {r0} 	// Salvo fib(n-1)
	sub r0, r1, #1 	// r0 = n-2
	bl fib		// Caso ricorsivo n-2
	pop {r1}	// Riprendo fib(n-1)
	add r0, r0, r1	// r0 = fib(n-2) + fib(n-1)

	pop {pc}

	.data
str:	.string "il fib di %d è:%d\n"

