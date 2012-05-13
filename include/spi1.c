/*The Serial Peripheral Interface (SPI) allows high-speed synchronous data transfer between the
ATmega32A and peripheral devices or between several AVR devices.*/

#include <avr/io.h>
#include <stdio.h>
#include "spi1.h"


/*Method init Serial Peripheral interface in mastermode SPI - Master*/



/**
 * @brief SPI_MasterInit initializes the SPI communication between AVR kit and RFID reader
 *
 * Setup the SPI interface as master
 * Defines the SCK (SPI clock); 625 kHz
 * Configures !SS (Slave Select) as output
 * 
 * @see SPI_MasterTransmit 
 */

void SPI_MasterInit(void)
{
/* Set MOSI and SCK output, all others input */
DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);  
/* Enable SPI, Master, set clock rate fck/16 */
SPCR |= (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(1<<SPR0);//|(1<<SPIE);//interrupt enabled;
PORTB|=(1<<PB4);
}


/**
* @brief method for transmitting a byte from master to slave
*
* @param cData is command to be sent ATmega8 on the rfid reader for getting the UAD  
* 0x55 command for the MicroRWD is for getting the series number on the card(UID)
* 0xFE Dummy data sent for pushing out the data from the buffer
*
* @pre The SPI has to be initialized as a master
*/
void SPI_MasterTransmit(char cData)
{
PORTB&=~(1<<PB4);
/* Start transmission */
SPDR = cData;
/* Wait for transmission complete */
while(!(SPSR & (1<<SPIF))); 
PORTB|=(1<<PB4);
}




