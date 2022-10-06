
/* utils.h - funciones utiles al TP2 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#ifndef _UTILS_H
#define _UTILS_H

void sensor_init();
void senial_alta();
void senial_baja();
void esperar();
void entrada();
void leer_datos();
char* get_datos();
#endif	/* _UTILS_H */
