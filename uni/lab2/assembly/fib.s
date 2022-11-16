.text
.global main

main:	PUSH {LR}
		MOV R0, #5
		
		BL fib
		
		POP {LR}
		MOV PC, LR


fib:	CMP	R0, #0 // Caso base 0
		MOVEQ PC, LR

		CMP	R0, #1 // Caso base 1
		MOVEQ PC, LR
		
		PUSH {LR}

		SUB R0, R0, #1
		PUSH {R0}
		BL fib
		PUSH {R0}

		POP{R1}
		SUB R0, R1, #1
		PUSH{LR}
		BL fib
		POP{R1}

		ADD R0, R0, R1

		POP {LR}		
		MOV PC, LR
