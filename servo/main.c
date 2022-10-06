#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"



int main(void)
{

	DDRB = 0x02; /*habilita PB1(OC1A) como pin de salida - pin 9 de avr*/
	 
	timer1_init();
	volatile unsigned long i;
	
	while (1) {
	
		
		mover_der();
		for(i=0;i < 450000;i++);
		apagar();
		for(i=0;i < 450000;i++);
		mover_izq();
		for(i=0;i < 450000;i++);
		
		
        }

}
