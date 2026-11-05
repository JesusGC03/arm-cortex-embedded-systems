	#include <LPC17xx.H>

volatile char a=1, b=1, c=1; // variables que controlan el funcionamiento
int cont0 = 0, cont1 = 0;
 
void inicioPINSEL(){
 //Configuración de los pines P2.10 a P2.12, como entradas de interrupción
 LPC_PINCON->PINSEL4 |= 1 << (10*2);   
 LPC_PINCON->PINSEL4 |= 1 << (11*2);   
 //Configuración de los pines P2.0 a P2.2, como GPIO
 LPC_PINCON->PINSEL4 &= ~ (3 << (0*2));  
 LPC_PINCON->PINSEL4 &= ~ (3 << (1*2));  
	
	//Configuramos pines P0.4, P0.6 y P0.8 como GPIO (salidas)
	LPC_PINCON->PINSEL0 &= ~((3 << (4*2)) | (3 << (6*2)));
	LPC_GPIO0->FIODIR |= (1 << (4*2)) | (1 << (6*2));
	
	//Configramos pines P0.5, P0.7 y P0.9 como entradas con pull-up
	LPC_PINCON->PINSEL0 &= ~((3 << (5*2)) | (3 << (7*2)));
	LPC_PINCON->PINMODE0 &= ~((3 << (5*2)) | (3 << (7*2)));
	LPC_GPIO0->FIODIR &= ~((1 << 5) | (1 << 7));
	
	//LEDS apagados inicialmente
	LPC_GPIO0->FIODIR = (1 << 4) | (1 << 6);
}

void inicioIRQs(){
	LPC_SC->EXTMODE = 0x3; // -> xx11 Activamos por flanco EINT0 y EINT1
	LPC_SC->EXTPOLAR = 0x1; // -> xx01 Activamos flanco de bajada (EINT1) y de subida (EINT0)
	
  LPC_SC->EXTINT = (1 << 0) | (1 << 1);
  NVIC_ClearPendingIRQ(EINT0_IRQn);
  NVIC_ClearPendingIRQ(EINT1_IRQn);
	
  NVIC_SetPriorityGrouping(4);    //Asignación de prioridades
  NVIC_SetPriority(EINT0_IRQn, 0x4);
  NVIC_SetPriority(EINT1_IRQn, 0x6);

  NVIC_EnableIRQ(EINT0_IRQn);    //Habilitación de las interrupciones
  NVIC_EnableIRQ(EINT1_IRQn);
}

//ISR de las interrupciones
void EINT0_IRQHandler(){
  LPC_SC->EXTINT |= (1);   // Borrar el flag de la EINT0 --> EXTINT.0
  //LPC_GPIO2->FIOSET=0x00000001;   // Activar el pin P2.10
  //while(a) ;
  //LPC_GPIO3->FIOCLR=0x00000001;   // Desactivar el pin P2.10
	
	LPC_GPIO0->FIOSET |= (1 << 4);		// Activar pin P0.4
	while(LPC_GPIO0->FIOPIN&(1<<5));	// Activo mientras P0.5 sea 0
	LPC_GPIO0->FIOCLR |= (1 << 4);		// Activar pin P0.4
}

void EINT1_IRQHandler(){
  LPC_SC->EXTINT |= (1 << 1);   // Borrar el flag de EINT1 ->EXTINT.1
  //LPC_GPIO2->FIOSET=0x00000002;   // Activar el pin P2.11
  //while(b);
  //LPC_GPIO2->FIOCLR=0x00000002;   // Desactivar el pin P2.11
	
	LPC_GPIO0->FIOSET |= (1 << 6);		// Activar pin P0.4
	while(LPC_GPIO0->FIOPIN&(1<<7));	// Activo mientras P0.5 sea 0
	LPC_GPIO0->FIOCLR |= (1 << 6);		// Activar pin P0.4
}

//Programa principal
main (){
  inicioPINSEL();
  inicioIRQs();
  while(1);
}