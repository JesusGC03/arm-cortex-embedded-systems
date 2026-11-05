/*----------------------------------------------------------------------------
   Name:    SYSTICK_interrupt.c
  ----------------------------------------------------------------------------*/

#include "LPC17xx.H"
uint32_t pulsador;

volatile uint32_t cuenta;  // Contador de veces de x ms
volatile uint8_t minutos = 0, segundos = 0;

void SysTickConfigExample(uint32_t ticks) {
  SysTick->LOAD = (uint32_t)(ticks - 1); // hasta 24 bits 
  SysTick->VAL  = 0;   // se pone valor 0
  SysTick->CTRL = 0x7; 

  NVIC_SetPriority(SysTick_IRQn, (1 << 5) - 1); 
}

void ConfiguraEINT0() {
    LPC_SC->EXTMODE  |=  (1 << 0);
    LPC_SC->EXTPOLAR &= ~(1 << 0);

    LPC_SC->EXTINT = (1 << 0);
    NVIC_ClearPendingIRQ(EINT0_IRQn);

    NVIC_EnableIRQ(EINT0_IRQn);
}

void ConfiguraPuertos(){
	LPC_PINCON->PINSEL7 &= ~(3 << ((26 - 16) * 2));		// P3.26 GPIO
	LPC_PINCON->PINMODE7 &= ~(3 << ((26 - 16) * 2));	// ponemos 00
	LPC_PINCON->PINMODE7 |= (1 << ((26 - 16) * 2) + 1);	// ponemos 10
	LPC_GPIO3->FIODIR |= (1 << 26);   // P3.26 definido como salida
	LPC_GPIO3->FIOSET = (1 << 26);
	
	LPC_PINCON->PINSEL4 &= ~(3 << (10 * 2));
	LPC_PINCON->PINSEL4 |= (1 << (10 * 2));	
}

void ConfiguraSystick(){
	SysTick->LOAD = 100000 - 1;
	SysTick->VAL  = 0;   // se pone valor 0
  SysTick->CTRL = 0x7; 
}

void EINT0_IRQHandler(void) {
  LPC_SC->EXTINT = (1 << 0);

	cuenta = 0;
	segundos = 0;
	minutos = 0;
	
	ConfiguraSystick();
}

void SysTick_Handler(void)  // Rutina (ISR) de atencion...
//... a la excepcion 15 - IRQ del SYSTICK -
{
  cuenta++;  // Incrementa cuenta cada IRQ del SysTick
	
	if (cuenta == 1000){
		cuenta = 0;
		segundos++;
		LPC_GPIO3->FIOPIN ^= (1 << 26);
		if (segundos == 60){
			segundos = 0;
			minutos++;
		}
	}
}

int main(void) {
	ConfiguraPuertos();
	ConfiguraEINT0();
  // SysTickConfigExample(100e6/100);  // Configura SYSTICK, CPUCLOCK = 100e6 Hz -> 10ns
  while (1);
}