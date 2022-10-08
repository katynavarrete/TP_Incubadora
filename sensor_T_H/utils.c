/* se usa el pin 12 de la placa */
#include <util/delay.h>
#define BIT5 0x10

/* puertos de E/S */
volatile unsigned char * port_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/

void esperar()
{
	volatile unsigned long i;
	for(i=0;i < 1800000;i++);
}
void sensor_init()
{

	/* configuracion del pin 13 */
	*(ddr_b) = *(ddr_b) |(BIT5);
	
	/*sensor inactivo */
	*(port_b) = *(port_b) & (~BIT5);

	
	
	//*(pin_b) = BIT5;

}

void senial_alta() 
{
	/* configuracion el pin 13 como de salida */
	*(ddr_b) = *(ddr_b) |(BIT5);
	volatile unsigned char valor_b = *(port_b);
	valor_b |=  (BIT5);
	
	*(port_b) = valor_b;
}

void senial_baja() 
{
	/* configuracion el pin 13 como de salida */
	*(ddr_b) = *(ddr_b) |(BIT5);
	
	/* envia 0 al pin 13 */
	volatile unsigned char valor_b = *(port_b);
	valor_b &= (~BIT5);
	*(port_b) = valor_b;
	
	
}
unsigned char datos[5] = {0,0,0,0,0};
void entrada()
{ 
	/* configuracion el pin 13 como de entrada */
	*(ddr_b) = *(ddr_b) &(~BIT5);
}
void leer_datos()
{
	
	volatile unsigned char i;
	volatile unsigned char tiempo;
	volatile unsigned char cnt = 7;
    	volatile unsigned char idx = 0;
    	volatile unsigned char valor;
    	
    	volatile unsigned char pin_entrada = 1;
    	/* espera hasta que  la señal baje por que puede no haber salido del intervalo de 20-40 microseg*/
    	while(pin_entrada != 0){
    		pin_entrada = *(pin_b) & BIT5;
    	}	
    	/*espera mientras que la señal suba corresponde a los 80 microseg*/
    	while(pin_entrada == 0)
    		pin_entrada = *(pin_b) & BIT5;
    		
    	/*espera que la señal baje, corresponde a los siguientes 80 microseg*/		
    	while(pin_entrada != 0)
   		pin_entrada = *(pin_b) & BIT5;
    			
    	
    	for( i = 0; i < 40; i++)
    	{
    		tiempo = 0;
  		/*espero hasta que la señal sea 1*/
  		while(pin_entrada == 0)
  		 	pin_entrada = *(pin_b) & BIT5;
    		/*cuento cuantos microseg pasan hasta que la señal baje*/
    		while(pin_entrada != 0){
    			_delay_us(1);
    			tiempo++;
    			pin_entrada = *(pin_b) & BIT5;
    		}	
    		
    		/*si tiempo es mayor a 40 es por que es 1 sino es 0*/
    		if( tiempo > 30){
    			datos[idx] |= (1 << cnt);
    		}
    		if( cnt == 0 ){
			cnt = 7;
			idx++;
		}	
		else{
			cnt--;
		}
    		
    		
    	}
    	/**
	for(i = 0; i < 40 ; i++){
		
		valor = *(pin_b) & BIT5;
		if(valor > 0){
			datos[idx] |= (1 << cnt);
		}	
		if( cnt == 0 ){
			cnt = 7;
			idx++;
		}	
		else{
			cnt--;
		}
	}*/
	
		
}
char* get_datos(){

	return datos;	
}
void reiniciar_datos()
{
	unsigned char i; 
	
	for(i = 0; i < 5; i++){
		datos[i] = 0;
	}
}		 






