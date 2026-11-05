#include <LPC17xx.H>

int32_t i;
void delay_1ms(uint32_t);
	

// Función de retardo
void delay_1ms(uint32_t ms)
{
  uint32_t n;
  for(n=0;n<ms*4545;n++);
}

int main(void)
{
  while(1){
    if(i==0) {
      i=1;
      delay_1ms(25);     
    }
    else{
      i=0;
      delay_1ms(25);     
    } 
   }
}
