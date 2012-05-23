#include <avr/io.h>
#include "rfid.h"



#ifndef rfid_H_INCLUDED
#define rfid_H_INCLUDED

void FILL_BUFFER(void)
	{
	BUFFER[BUFFER_TRACKER]=SPDR;
				BUFFER_TRACKER++;
	}
	
				
				
#endif /* rfid_h_INCLUDED */
