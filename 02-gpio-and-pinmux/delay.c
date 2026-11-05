/* delay.c */

#include "delay.h"

void delay_1ms(uint32_t ms)
{
   	unsigned long i;
	 	for(i=0;i<ms*4545;i++); 
}
