#define BIT2 (0x04)

/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/


void reley_init()
{
	//BIT2 inicia apagado
	*(puerto_b) = *(puerto_b) & (~BIT2);
	//BIT2 es de salida
	*(ddr_b) = *(ddr_b) | (BIT2);
	
}

void prender_reley() 
{
	volatile unsigned char valor_b = *(puerto_b);
	valor_b |=  BIT2 ;
	*(puerto_b) = valor_b;
}

void apagar_reley() 
{
	volatile unsigned char valor_b = *(puerto_b);
	valor_b &= ~(BIT2);
	*(puerto_b) = valor_b;
}
void esperar()
{
	volatile unsigned long i;
	for(i=0;i < 900000;i++);
}
