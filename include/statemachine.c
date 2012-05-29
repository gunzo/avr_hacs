/**
 * @file
 * @brief statemachine has the task of scanning the card, reading the data on it and parsing the card UID to the PC terminal.
 * 
 * @author Gunnar
 */

#include <avr/io.h>
#define F_CPU 10000000UL
#include <util/delay.h>
#include <string.h>
#include "include/spi.h"
#include "timer0.h"
#include "include/timers.h"
#include "avrboard.h"
#include "uart_driver.h"
#include "rfid.h"

#define idle 0


#define card_present  2
#define activate_timer_int  3
#define read_data  4
#define send_command  5
#define wait_on_data  6
#define wait_on_card_removed 7

char timerflag=0;






void CheckReader()
{
	
	static char state=0; 

			
		switch (state)
		{
			
			
		case idle : 
			
			
		
		
			if ((CARD_PRES)==0x04) 
			{
			state = card_present;
		

			timerflag=0;
			}
			else 
			{
			state=idle;
			
			}break;
		
		case card_present:  
	
		
			SPI_MasterTransmit(0x55);  
			state= wait_on_data;
			break;
		
		case wait_on_data : 
		
			if((DATA_READY)==0x08) 
	
			{
				state = activate_timer_int; 
			}
			else
			{
				state = wait_on_data;
				
			}break;
	
		case activate_timer_int : 
	
			TIMSK |= (1<< OCIE0 );
			state = read_data;

			break;
	
		case read_data :
	
			if((DATA_READY)==0x08)
			{
			
				if (timerflag== 1) 
				
				{
				
				timerflag=0;
				
				SPI_MasterTransmit(0xF5);
				FILL_BUFFER
				
				
					IS_BUFFER_FULL
					{
					
					TIMSK &= ~(1<<OCIE0); 
				
					state = wait_on_card_removed;
					
					}
			 	}

			 }

			break;
		case  wait_on_card_removed:
	
				
			
		
	
			
			if (!(card_pres))
			{
				
				SendString(BUFER);
					
				state=idle;
				CLEAR_BUFFER_TRACKER;				
    	
			}
										
		
			else 
			{
	
			state=wait_on_card_removed	;
		
			
							
			}
			break;			
	
	
			default: 
			state=idle;
			break;
	
	}
}




	







int main(void)
{
	USART_Init(0x40);  
	SPI_MasterInit();
	initTimer0(0); 
	sei();

;
	

	while(1)
	{
	CheckReader();
	}
	return 0;
}

 

ISR (TIMER0_COMP_vect)  
{
	

	timerflag=1;
	
} 
