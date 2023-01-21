/*
  componentes: 
	pantalla
	parlante en pin 9 con resistencia
	sensor T/H en pin 12
*/

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <util/delay.h>

#include "lcd_ssd1306.h"
#include "twi.h"
#include "font.h"
#include "utils.h"
#include "timer.h"

#define LIM_TEMP 34
#define LIM_HUM 65

void enviar_datos(unsigned char num, unsigned char columna , unsigned fila){
	
	unsigned char val, divisor, tmp, i =0;
	
	/*convertir val en ascii*/
	val = num;
	divisor = 10;		
	while ( divisor  > 0){
		tmp = (val / divisor)+48;
		val = val % divisor;
		lcd_ssd1306_draw_char(columna, fila, tmp, 1);
		columna+=6;
		divisor = divisor / 10;
	}
	
} 

void control_T_H(unsigned char valor_H, unsigned char valor_T)
{
	if( valor_H < LIM_HUM || valor_T < LIM_TEMP)
	{
		lcd_ssd1306_clear_buffer();
		prender();
		_delay_ms(1000);
		apagar();
		if(valor_H < LIM_HUM)	 
			lcd_ssd1306_print_text(5,10, "HUMEDAD BAJA");
				
	
		if(valor_T < LIM_TEMP)
		 	lcd_ssd1306_print_text(5,40, "TEMPERATURA BAJA");
		
		lcd_ssd1306_render_buffer();
	}

}

void main() 
{
	/* activa el timer1 para usar el parlante */	
	DDRB = 0x02;
	
	/* Inicializa el driver i2c / TWI */
	twi_init();
	
	/*inicializa el timer*/
	timer1_init();
	
	/* Inicializa el driver del LCD ssd1306 */
	lcd_ssd1306_init();
	
	unsigned char *datos;
	/* Enable interrupts. */
	sei();       

	while (1) {	
		
		/* enviar al sensor señal baja (0)  por 18 miliseg*/
		senial_baja();
		_delay_ms(18);
		
		/* enviar al sensor señal alta (1)  por 30 microseg*/
		senial_alta();
		_delay_us(30);
		
		/*lectura de los datos del sensor*/
		entrada();
		leer_datos();
		datos = get_datos();
		
		lcd_ssd1306_clear_buffer();
		
		lcd_ssd1306_print_text(5,10, "HUMEDAD: ");
		enviar_datos(datos[0],59,10);
		
		lcd_ssd1306_print_text(5,40, "TEMPERATURA: ");
		enviar_datos(datos[2],83,40);
		
		lcd_ssd1306_render_buffer();
		_delay_ms(2000);
		
		control_T_H(datos[0], datos[2]);
		
		reiniciar_datos();
		_delay_ms(3000);
		
	}
}
