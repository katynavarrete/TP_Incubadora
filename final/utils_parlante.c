#define BIT0 0x01


/* puertos de E/S */
volatile unsigned char * port_bp = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_bp = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_bp = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/


void speaker_init()
{
	//el esta apagado
	*(port_bp) = *(port_bp) & (~BIT0);
	//configuro el bit5 como salida
	*(ddr_bp) = *(ddr_bp) |(BIT0);

}

void prender_speaker() 
{
	volatile unsigned char valor_b = *(port_bp);
	valor_b |=  (BIT0);
	
	*(port_bp) = valor_b;
}

void apagar_speaker() 
{
	volatile unsigned char valor_b = *(port_bp);
	valor_b &= (~BIT0);
	
	*(port_bp) = valor_b;
}



