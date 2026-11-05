/*----------------------------------------------------------------------------
   Name:    SYSTICK_interrupt.c
  ----------------------------------------------------------------------------*/

#include "LPC17xx.H"
uint32_t pulsador;

volatile uint32_t cuenta;  // Contador de veces de x ms

void SysTickConfigExample(uint32_t ticks) {
  SysTick->LOAD = (uint32_t)(ticks - 1); // hasta 24 bits 
  SysTick->VAL  = 0;   // se pone valor 0
  SysTick->CTRL = 0x7; 

  NVIC_SetPriority(SysTick_IRQn, (1 << 5) - 1); 
}

void SysTick_Handler(void)  // Rutina (ISR) de atencion...
//... a la excepcion 15 - IRQ del SYSTICK -
{
  cuenta++;  // Incrementa cuenta cada IRQ del SysTick
  pulsador = ((LPC_GPIO2->FIOPIN & (1 << 12)) >> 12); // KEY2
  if (pulsador == 0) {  // KEY2 pulsado?
    if (cuenta == 2) {
      LPC_GPIO3->FIOPIN &= ~(1 << 25);  // enciendo LED
    }
    if (cuenta >= 2 * 2) {
      LPC_GPIO3->FIOPIN |= (1 << 25);  // apago LED
      cuenta = 0;
    }
  } else {
    if (cuenta == 5) {
      LPC_GPIO3->FIOPIN &= ~(1 << 26);  // enciendo LED
    }
    if (cuenta >= 5 * 2) {
      LPC_GPIO3->FIOPIN |= (1 << 26);  // apago LED
      cuenta = 0;
    }
  }
}

int main(void) {
  LPC_GPIO3->FIODIR |= (1 << 25);   // P3.25 definido como salida
  LPC_GPIO3->FIODIR |= (1 << 26);   // P3.26 definido como salida
  LPC_GPIO2->FIODIR &= ~(1 << 12);  // P2.12 definido como entrada

  SysTickConfigExample(100e6/100);  // Configura SYSTICK, CPUCLOCK = 100e6 Hz

  while (1);
}