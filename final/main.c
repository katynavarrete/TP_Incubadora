/*
 	parlante en pin 9 .
 	servo en pin 10
 	sensor corriente 11 .
 	sensor humedad y tempertura 12 .
 	reley 13	
*/
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <util/delay.h>

#include "lcd_ssd1306.h"
#include "twi.h"
#include "font.h"
#include "utils_corriente.h"
#include "timer.h"
#include "utils_hum_tem.h"

volatile unsigned char *valores;
#define HUMEDAD_MIN 40
#define HUMEDAD_MAX 50

#define TEMPERATURA_MIN 37
#define TEMPERATURA_MAX 38

void enviar_valores(unsigned char num, unsigned char columna , unsigned fila){
	
	unsigned char val, divisor, tmp, i =0;
	
	/*convertir val en ascii*/
	val = num;
	divisor = 1;
	if(num > 99 )
		divisor = 100;
	else if( num > 9)
		 divisor = 10;
		 		
	while ( divisor  > 0){
		tmp = (val / divisor)+48;
		val = val % divisor;
		lcd_ssd1306_draw_char(columna, fila, tmp, 1);
		columna+=6;
		divisor = divisor / 10;
	}
	
} 

void leer_sensor()
{
		/* enviar al sensor señal baja (0)  por 18 miliseg*/
		senial_baja();
		_delay_ms(18);
		senial_alta();
		/* enviar al sensor señal alta (1)  por 30 microseg*/
		_delay_us(30);
		entrada();
		leer_datos();
		valores = get_datos();
}

void mostrar_valores()
{
	lcd_ssd1306_clear_buffer();
	lcd_ssd1306_print_text(5,10, "HUMEDAD: ");
	enviar_valores(valores[0],59,10);
	lcd_ssd1306_print_text(5,40, "TEMPERATURA: ");
	enviar_valores(valores[2],83,40);
	lcd_ssd1306_render_buffer();
}

void alarma(unsigned char tipo)
{
	lcd_ssd1306_clear_buffer();
	switch(tipo){
		case 0:
			lcd_ssd1306_print_text(5,10, "HUM BAJA");
		break;
		case 1:
			lcd_ssd1306_print_text(5,10, "HUM ALTA");
		break;
		case 2:
			lcd_ssd1306_print_text(5,10, "TEMP BAJA");
		break;
		case 3:
			lcd_ssd1306_print_text(5,10, "TEMP ALTA");
		break;
		case 4:
			lcd_ssd1306_print_text(5,10, "CORTE DE LUZ");
		break;
	}
	lcd_ssd1306_render_buffer();
	
	prender();
	_delay_ms(500);
	apagar();
	
	_delay_ms(500);
}


void main() 
{
	DDRB = 0x02; /*habilita PB1(OC1A)/pin 9 como salida*/
	/* Inicializa el driver i2c / TWI */
	twi_init();

	/* Inicializa el driver del LCD ssd1306 */
	lcd_ssd1306_init();

	sensor_init();
	
	//serial_init();    
	timer1_init();
	
	/* Enable interrupts. */
	sei();       
	volatile unsigned char estado;
		
	while (1) {	/* Un programa embebido nunca finaliza */
	
		leer_sensor();
		/* controla la temp y hum, el parametro indica el tipo de alarma*/
		if(valores[0] < HUMEDAD_MIN)
			alarma(0);
		else if(valores[0] > HUMEDAD_MAX)
			alarma(1);
		
		if(valores[2] < TEMPERATURA_MIN)
			alarma(2);
		else if(valores[2] > TEMPERATURA_MAX)
			alarma(3);
			
		/*controla si hay luz*/
		estado = get_estado();
		if(estado != 0){
			prender();
			alarma(4);
		}
		else
			apagar();
		
		mostrar_valores();		

		reiniciar_datos();
		_delay_ms(2000);
		
		
		
	}
}
