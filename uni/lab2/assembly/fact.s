.text
.global main

main:	PUSH {LR}
		MOV R0, #5
		
		BL fact
		
		POP {LR}
		MOV PC, LR


fact:	CMP	R0, #1
		MOVEQ PC, LR
		PUSH {R0, LR}
		SUB R0, R0, #1
		BL fact
		POP {R1, LR}
		MUL R0, R0, R1
		MOV PC, LR
