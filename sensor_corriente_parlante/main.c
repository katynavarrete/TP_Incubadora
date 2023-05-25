#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "utils.h"


int main(void)
{

	DDRB = 0x02; /*habilita PB1(OC1A)/pin 9 como salida*/

	sensor_cor_init();  
	timer1_init();
	volatile unsigned long i;
	volatile unsigned char estado;
	
	while (1) {
	
		if(estado == 0){
			apagar();
		}
		else
			prender();
		esperar();
		estado = get_estado();
		
        }

}
