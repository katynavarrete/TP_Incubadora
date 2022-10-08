#include "utils.h"


int main(void)
{	
 	int i;
	reley_init(); 
	
	while(1)
	{
		prender_reley();
		esperar();
		apagar_reley();
		esperar();
	}
	return 0;
}


