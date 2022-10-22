
/* Ejemplo de controlador LCD ssd1306 usando i2c
 * Rafael Ignacio Zurita <rafa@fi.uncoma.edu.ar>
 *
 * El driver i2c está en : twi.c y twi.h (tiene interrupciones)
 * Driver i2c autor: https://github.com/scttnlsn/avr-twi
 *
 * Pensado para usar en la materia Programacion de Sistemas Embebidos
 * Sacamos la idea y los comandos al LCD de un ejemplo original para 
 * RaspberryPi : gcc ssd1306.c -lwiringPi -o ssd1306 
 */

/* POR HACER:
 *
 * - Se pueden acelerar las escrituras de los los datos si 
 *   se envía unicamente una sola vez el byte de comando
 *   y luego el resto de los bytes (en vez de un byte comando por cada
 *   byte de datos)
 *
 * - Se debe reescribir el driver i2c para usar solo baremetal
 *   sin las macros de avr-libc.
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

void main() 
{
	/* variables para la animacion del pixel en pantalla */
	int i = 0;
	int inc_i = 0;
	int j = 0;
	int inc_j = 0;

	/* Inicializa el driver i2c / TWI */
	twi_init();

	/* Inicializa el driver del LCD ssd1306 */
	lcd_ssd1306_init();
	unsigned char *datos;
	/* Enable interrupts. */
	sei();       

	
	
	
	while (1) {	/* Un programa embebido nunca finaliza */
	
		

		/* enviar al sensor señal baja (0)  por 18 miliseg*/
		senial_baja();
		_delay_ms(18);
		senial_alta();
		/* enviar al sensor señal alta (1)  por 30 microseg*/
		_delay_us(30);
		entrada();
		leer_datos();
		datos = get_datos();
		
		lcd_ssd1306_clear_buffer();
		lcd_ssd1306_print_text(5,10, "HUMEDAD: ");
		enviar_datos(datos[0],59,10);
		//lcd_ssd1306_print_text(59,10, convertir_string(20));
		lcd_ssd1306_print_text(5,40, "TEMPERATURA: ");
		enviar_datos(datos[2],83,40);
		//lcd_ssd1306_print_text(83,40, convertir_string(30));
		lcd_ssd1306_render_buffer();
		reiniciar_datos();
		_delay_ms(2000);
		
	}
}
