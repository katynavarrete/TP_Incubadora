/*el reley utilizado prende cuando la señal es low (0) y apaga cuando high (1)*/

#define BIT5 (0x20)

/* puertos de E/S */
volatile unsigned char * puerto_br = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_br = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_br = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/


void reley_init()
{
	//BIT5 inicia apagado
	*(puerto_br) = *(puerto_br) |=  BIT5 ;
	//BIT5 es de salida
	*(ddr_br) = *(ddr_br) | (BIT5);
	
}

void apagar_reley() 
{
	volatile unsigned char valor_br = *(puerto_br);
	valor_br |=  BIT5 ;
	*(puerto_br) = valor_br;
}

void prender_reley() 
{
	volatile unsigned char valor_br = *(puerto_br);
	valor_br &= ~(BIT5);
	*(puerto_br) = valor_br;
}

