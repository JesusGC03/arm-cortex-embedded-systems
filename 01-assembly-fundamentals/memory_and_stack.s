 ; Programa_2.s
STACK_TOP 	EQU 0x10002000 
		AREA RESET, CODE
		DCD STACK_TOP    
		DCD inicio
		SPACE (0x400-8) 
		ENTRY 	 
	  
inicio	MOV r0,#0
		MOV r1,#32

uno		LSL r0, r0, #1			; Metemos un 0 por izquierda
		ORR r0, r0, #1			; Lo cambiamos por un 1
		SUBS r1, r1, #1 		; Restamos 1 a R1 actualizando flag
		BNE uno					; Si no es igual a 0, salta al inicio

cero	LSR r0, r0, #1
		SUBS r1, r1, #32
		BNE cero
		
Fin		B Fin
 
		ALIGN 4
		AREA Variables, DATA

		END
