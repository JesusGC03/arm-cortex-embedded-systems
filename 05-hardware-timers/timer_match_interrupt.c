/*-------------------------------------------------------------------------
 * Nombre:    Timer1_Ejemplo.c 
 *-----------------------------------------------------------------------*/

#include "LPC17xx.H"
void inicializa(void) {

  LPC_SC->PCONP |= 1 << 2;         //Conectar la alimentación al Timer1
  LPC_GPIO1->FIODIR |= (1 << 18);  // P1.18 definido como salida
	LPC_GPIO3->FIODIR |= (1 << 26);
  LPC_SC->PCLKSEL0 &= ~(1 << 4);
  LPC_SC->PCLKSEL0 |= 1 << 5;      // Clock para el Timer = CCLK/2
  LPC_TIM1->MR0 = 292968;          // Se asigna valor apropiado para la frecuencia de
                                   // parpadeo del LED basado en frecuencia del reloj
  LPC_TIM1->MCR |= 0x3;            // Interrumpir cuando se alcance Match0 (bit0) y
                                   // resetear el contador del Timer
                                   // cuando alcance el valor del Match0 (bit1)
  LPC_TIM1->PR = 511;           // Cada vez que el Prescaler0 alcance este valor
                                // se incrementa en uno el contador del Timer
  LPC_TIM1->TCR |= 1 << 1;      // Resetear Timer
  LPC_TIM1->TCR &= ~(1 << 1);   // Se vuelve a poner a 0 para eliminar el Reset
  NVIC_EnableIRQ(TIMER1_IRQn);  // Habilitar interrupción Timer
  
}

void TIMER1_IRQHandler(void) {

  if ((LPC_TIM1->IR & 0x01) == 0x01){  // Si se ha interrumpido por MR0     
    LPC_TIM1->IR |= 1 << 0;           // Borrar flag de interrupción MR0
  LPC_GPIO1->FIOPIN ^= 1 << 18;       // Conmutar estado del LED
  }
  
}

int main(void) {
  inicializa();
  LPC_TIM1->TCR |= 1 << 0;      // Arrancar el Timer
  while (1)
    ;
}

