/*
 * StateSystem.c
 *
 * Created: 12/04/2012 09:36:06
 *  Author: gunnar
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
//#include "include/display.h"
#define idle 0
//#define data_ready  PIND&0x08  //(1<<PD3)
//#define card_pres  PIND &(1<<PD2)

#define card_present  2
#define activate_timer_int  3
#define read_data  4
#define send_command  5
#define wait_on_data  6
#define wait_on_card_removed 7

char timerflag=0;






void CheckReader()
{
	
	static char state=0; //IDLE
//	static int i=0;
			
		switch (state)
		{
			
			
		case idle : //System waiting for card
			
			//scan card
		
		
			if ((CARD_PRES)==0x04) 
			{
			state = card_present;
		

			timerflag=0;
			}
			else 
			{
			state=idle;
			
			}break;
		
		case card_present:  // Card has been scanned
	
		
			SPI_MasterTransmit(0x55);  //!!!!!!!!!!!!!!!!SPI_Transmit(0x55) 
			state= wait_on_data;
			break;
		
		case wait_on_data :  // waiting for the data to be streamed
		
			if((DATA_READY)==0x08) //flag 
		//	if(data_ready)
			{
				state = activate_timer_int; //!!!!!!!!!1
			}
			else
			{
				state = wait_on_data;
				
			}break;
	
		case activate_timer_int : // we activate the timer
	
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
	USART_Init(0x40);  //full duplex
	SPI_MasterInit();
	initTimer0(0); // we have zero parameter to stop the timer  //disable the timerinterrupt, setup for compare match interrupt
	sei();
//	LCD_INIT;
	/*
    initTimer0(0);  
    */
	/* Settinng up a CTC interupt and starting the timer 0 with a prescaler
	 * of 64. */
	//T0_CTC_INT( 0x10 ); expected while before the void!!!!
	//T0_START( 64 );
	
	/* Swithcing the LED on the AVR board off*/
	LED_ACTIVATE;
	LED_OFF;
//	lcd_write("Scan CARD");
	

	while(1)
	{
	CheckReader();
	}
	return 0;
}

 

ISR (TIMER0_COMP_vect)  
{
	
//	read_data_spi(); 
	timerflag=1;
	
} 
