
/* 
   	conexion a resistencia e 10k y al pin 11
 */

#define BIT3 (0x08)

/* puertos de E/S */
volatile unsigned char * puerto_bc = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_bc = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_bc = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/

volatile unsigned char estado=0;

void sensor_cor_init(){
	*(puerto_bc) = *(puerto_bc);
	*(ddr_bc) = *(ddr_bc)  & (~ BIT3);
	*(pin_bc) =  0x08;
}


unsigned char get_estado()
{
	volatile unsigned char valor_bc = *(pin_bc);
	valor_bc &=  BIT3 ;
	if(valor_bc != BIT3){
		estado = 1;
	}
	else
		estado = 0;
	
	return estado;
}
