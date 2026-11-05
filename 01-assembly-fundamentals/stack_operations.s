  ;    Programa para el estudio de los modos de direccionamiento en ensamblador

STACK_TOP 	EQU 0x10000200 

		AREA RESET, CODE  
		DCD STACK_TOP   
		DCD inicio
		SPACE (0x0C8-8)  
	 	
		ENTRY 	 
	  
inicio 		;  Inicio del programa principal
   
; Se  inicializan algunos registros	para que se pueda observar como se van modificando 
; y los valores que toma la pila con la instrucción PUSH
		LDR R0,=0x11111111
		LDR R1,=0x22222222
		LDR R2,=0x33333333
		LDR R3,=0x44444444
		LDR R4,=0x55555555
		LDR R5,=0x66666666
		LDR R6,=0x77777777
		LDR R7,=0x88888888
		LDR R8,=0x99999999
; Fin de la inicialización	
									   
		LDR  R0,=Dato1                               
		LDRB R0,[R0]		   	   				  
		LDR  R1,=Dato2		   	   				  
		LDRB R1,[R1]		   	   				  
		LDR  R2,=Dato3		   	   				  
		LDRB R2,[R2]		   	   				  
		BL Calcula 	               	  			  
		LDR  R1,=Resultado 	   	   				  
		STRH R0,[R1]               				  
while  	B    while	                 
									                     
									   
 ; Rutina que calcula el resultado final
Calcula	PUSH  {R0,R1,LR}
		BL    Suma  
		POP   {R0}
		MUL   R0,R0,R2	
		POP   {PC}  

 
 ; Rutina que calcula la suma
Suma	POP   {R4,R5}
		ADD   R4,R4,R5   
		PUSH  {R5}
		BX    LR	


		AREA Constantes, DATA, READONLY
Dato1	DCB 4
Dato2	DCB 6
Dato3	DCB 9

		AREA | Header Data|, DATA
Resultado	SPACE 2
		END  

 