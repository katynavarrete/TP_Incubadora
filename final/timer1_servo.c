#include <avr/io.h>
#include <avr/interrupt.h>



typedef struct
{
    uint8_t tccr1a;  /* Registro de control A del timer1 */
    uint8_t tccr1b;  /* Registro de control B del timer1 */
    uint8_t tccr1c;  /* Registro de control C del timer1 */
    uint8_t reserved;
    uint8_t tcnt1l;  /* Registro timer/contador parte baja*/
    uint8_t tcnt1h;  /* Registro timer/contador parte alta*/
    uint8_t icr1l;   /* Registro de captura de entrada Byte parte baja*/
    uint8_t icr1h;   /* Registro de captura de entrada Byte parte alta*/
    uint8_t ocr1al;  /* Registro comparador A parte baja*/
    uint8_t ocr1ah;  /* Registro comparador A parte alta*/
    uint8_t ocr1bl;  /* Registro comparador B parte baja*/
    uint8_t ocr1bh;  /* Registro comparador B parte alta*/

} volatile timer1_t;


volatile timer1_t *timer1 = (timer1_t *)(0x80);

/* registro mascara de interrupciones timer 1 */
volatile unsigned char *timer1_timsk1 = (unsigned char *)(0x6F);

#define SYSTEM_TICKS 16000000
#define PRESCALAR 8

#define TIMER1_CS 0x02  /* prescalar = 8*/
#define TIMER1_CTC 0x80 /* OC1A no invertido*/

#define TIMER1_WG0 0x02 /* Fast PWM TOP ICR1*/
#define TIMER1_WG1 0x18 /* Fast PWM TOP ICR1*/


#define TIMER1_ICR1H 0x9C 
#define TIMER1_ICR1L 0x40

#define DER_H 0x13
#define DER_L 0x88

#define MED_H 0x0B
#define MED_L 0xB8

#define IZQ_H 0x03
#define IZQ_L 0xE8

void timer1_init( void )
{
	timer1->tccr1a = (TIMER1_CTC | TIMER1_WG0) ;
	timer1->tccr1b = (TIMER1_CS | TIMER1_WG1) ;

	timer1->icr1h = TIMER1_ICR1H; /* define la parte alta de TOP del contador */
	timer1->icr1l = TIMER1_ICR1L; /* define la parte baja de TOP del contador */

	//(*timer1_timsk1) |= 0x02;  /* 0x01: al producirse overflow se dispara una interrupcion*/ 
	
	timer1-> ocr1ah = 0x00;
    	timer1-> ocr1al = 0x00;
	
}


ISR(TIMER1_COMPA_vect)
{
	/*timer1-> ocr1ah = 0x00;
    	timer1-> ocr1al = 0x00;*/
		
}
void apagar(void)
{
	timer1-> ocr1ah = 0x00;
    	timer1-> ocr1al = 0x00;
}
void mover_izq(void)
{
	//2000
	timer1-> ocr1ah = IZQ_H;
    	timer1-> ocr1al = IZQ_L;
}
void mover_der(void)
{
	//4000
	timer1-> ocr1ah = DER_H;
    	timer1-> ocr1al = DER_L;
}

	
