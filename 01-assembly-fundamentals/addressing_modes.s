 ;
 ;  Programa para el estudio de los modos 
 ;  de direccionamiento en ensamblador

STACK_TOP 	EQU 0x10000200 
		AREA RESET, CODE 	; La directiva AREA indica al 
							; ensamblador crear una nueva seccion 
							; de codigo o de datos. 
							; Las secciones son independientes 
							; e indivisibles para el linker
		DCD STACK_TOP    	;	La directiva DCD asigna 
							; una o mas palabras de memoria,
							; alineados en grupos de cuatro bytes, 
							; y define el contenido inicial de la memoria.
		DCD inicio
	 
		SPACE (0x400-8)  	; Dejamos libre el primer Kbyte de memoria
							; El programa comenzara en la direccion 0x400
	 
		ENTRY 	 
inicio 	MOV r0,#10 	 	;  Inicio del programa principal
		ADD r1,#0xA
		MOV r2,#0x4
		LDR r5,=Lista  
		LDR r4,=0x10000000 
		ADD r4,r4,#12

		LDR r0,[r5]         
		STR r0,[r4]         
		MOV r1,0xAABB
		STRH r1,[r4,#4]!      
		STR r1,[r4],#4
		LDR r3,[r5,#4]

		STR r3,[r4,r2]      
			
		LDMIA r5,{r0-r2}
		
		LDR r0,=Lista2
		LDR r2,=Num
		LDR r1,[r2]
		LDR r2,=Suma
		MOV r3,#0x00
			
lazo	LDRB r4,[r0],#4
		ADD r3,r4
		SUBS r1,r1,#1
		BNE lazo
		STR r3,[r2]

Fin		B Fin
 
		AREA Constantes, DATA, READONLY
Lista	DCD 0x11121314,0x15161718,0x191A1B1C
Lista2	DCD 0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A 	
Num		DCB 10

		AREA Variables, DATA
Suma	SPACE 4
Espacio SPACE 24
		END  

 