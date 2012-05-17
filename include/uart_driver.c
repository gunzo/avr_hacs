
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

/**
 * @file
 * @brief The Universal Synchronous and Asynchronous serial Receiver and Transmitter
 * (USART) is a highly flexible serial communication device
 *
 * Contains methods for Seting up the USART and for transmitting and receiving data.
 * 
 * @author Gunnar
 */

#ifndef uart_driver_H_INCLUDED
#define uart_driver_INCLUDED



unsigned char ch;//


char flag_u=0;

/* 
 * @brief method for receiving data using polling
 *
 */
char usart_receive()
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)))
	;
	/* Get and return received data from buffer */
	return UDR;
}

/* @brief method for sending data Buffering up data in the UDR, and transmit it using polling 
 *
 * @param data to be sent

*/
void usart_transmit( char data)
{
	/* Wait for data to be transmitted */
	while ( !(UCSRA & (1<<UDRE)));

	UDR=data;

}

/* @brief Sends a string through the UART using the usart_transmit() method. 
 *
 * @brief Array pointer is used for the data
 * 
 * @see usart_transmit

 method used for transmitting a string polling based*/
void SendString (char *s)
{
  char c=0;
	
	//usart_transmit(0x0d);           //line shift
	//usart_transmit(0x0a);			//new line
	//  loop until *s != NULL
	for (;(( c=*s)!=0);s++){
	usart_transmit(*s);   //start the process of transmit interrupts
}
}


/**
 * @brief Setup the USART Transmitter and Receive complete interrupts
 *
 * Selects the number of stop bits to be inserted by the transmitter (setting 0 means 1 stop bit is used)
 * Sets the number of data bit s (8 bits)
 * Enables full duplex, double transmission speed
 * Configures baud rate
 * Enables global interrupts
 *
 * @param for seting baud rate(bits per second)
 *
 * @see usart_transmit
 */
void USART_Init( unsigned int baud )
{


	UCSRB|= (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);  //|(1<<TXCIE);
	/* Set frame format:enable the UCSRC for writing
						  1 stop bit, 8 data bit */
	UCSRC|= (1<<URSEL)|(0<<USBS)|(3<<UCSZ0);     
	UCSRA =(1<<U2X);        //double speed full duplex

	/* Set baud rate */
					
	UBRRH = (unsigned char)(baud>>8);       //Note type carsting for baud!
	UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */

}
/* interrupt service routine for receive complete - c-cmpiler manual p.133*/
ISR(USART_RXC_vect) 
{
	ch = UDR;

	/*SPI_MasterTransmit(ch);*/
	flag_u=1;
}
#endif /* uart_driver_H_INCLUDED */

