/*Header rfid interface*/

#include <stdint.h>


/**
 * @file
 * @brief The rfid Interface contains macros and definations for the data handling in the statemachine
 * ATmega32A and peripheral devices or between several AVR devices.
 *
 * Contains macros and definations for the data handling in the statemachine
 * 
 * @author Gunnar
 */

#ifndef RFID_H_INCLUDED
#define RFID_H_INCLUDED

/**
 * brief activate interrupt1 on portD, pin3. When the buffer is full on the RFID then DATA_READY goes high.
 *
 */

#define DATA_READY ( PIND&0x08 ) //(1<<PD3)


/**
 * @brief acivate interrupt0 on port D, pin2 for checking out when card is presented to the rfid
 *
 */
#define CARD_PRES  ( PIND &(1<<PD2))

/**
 * @brief data to be stored inside the buffer
 *
 */

char BUFFER[8];	

/**
 * @brief for incrementening the buffer and for keeping track of data to be stored inside the buffer
 *
 */

uint8_t buffer_tracker=0;

/**
 * @brief for checking if the buffer is full
 *
 */

#define IS_BUFFER_FULL if (buffer_tracker == 8)

/**
 * @brief for clearing the BUFFER_TRACKER
 *
 */

#define CLEAR_BUFFER_TRACKER buffer_tracker=0;		

/**
 * @brief method for filling the buffer with data
 *
 *
 */

//extern void FILL_BUFFER(void);


void FILL_BUFFER(void)
{
	BUFFER[buffer_tracker]=SPDR;		
	buffer_tracker++;
}	



#endif /* rfid_H_INCLUDED */
