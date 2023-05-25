
/* utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */


#define bit2 (0x04)

/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/

volatile unsigned char estado=0;

void sensor_cor_init(){
	*(puerto_b) = *(puerto_b);
	*(ddr_b) = *(ddr_b)  & (~ bit2);
	*(pin_b) =  0x04;
}

void esperar() {
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<450000; i++);
}



unsigned char get_estado(){
volatile unsigned char valor_b = *(pin_b);
	valor_b &=  bit2 ;
	if(valor_b != bit2){
		estado = 1;
	}
	else
		estado = 0;
	
	return estado;
}
