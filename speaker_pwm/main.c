#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"



int main(void)
{

	DDRB = 0x02; /*habilita PB1(OC1A)/pin 9 como salida*/

	//serial_init();    
	timer1_init();
	volatile unsigned long i;
	
	while (1) {
	
		
		prender();
		for(i=0;i < 450000;i++);
		apagar();
		for(i=0;i < 450000;i++);
		
        }

}
