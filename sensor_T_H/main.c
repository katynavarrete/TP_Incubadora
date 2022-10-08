/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/


#include "utils.h"
#include "serial.h"
#include <util/delay.h>
#include <avr/interrupt.h>

void enviar_num(unsigned char num){
	
	unsigned char val, divisor, tmp;
	/*convertir val en ascii*/
	val = num;
	divisor = 10;		
	while ( divisor  > 0){
		tmp = (val / divisor)+48;
		val = val % divisor;
		serial_put_char(tmp);
		divisor = divisor / 10;
	}
	
} 


int main(void)
{
	char estado;	
	
	sensor_init();
	serial_init();
	unsigned char *datos;
	cli();
	while(1){
		
		/* enviar al sensor señal baja (0)  por 18 miliseg*/
		senial_baja();
		_delay_ms(18);
		senial_alta();
		_delay_us(30);
		entrada();
		
		leer_datos();
		datos = get_datos();
		if((datos[0]+datos[1]+datos[2]+datos[3]) == datos[4])
		
			serial_put_String("Datos correctos \r\n:");
		else{
			enviar_num(datos[4]);		
			serial_put_String("Datos Incorrectos \r\n:");
		}
		serial_put_String("Humedad:");
		enviar_num(datos[0]);
		serial_put_char(',');
		enviar_num(datos[1]);
		serial_put_String("\r\n");
		esperar();
		serial_put_String("Temperatura:");
		enviar_num(datos[2]);
		serial_put_char(',');
		enviar_num(datos[3]);
		serial_put_String("\r\n");
		reiniciar_datos();
		esperar();
		
	}
    	return 0;
}

