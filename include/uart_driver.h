#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * @file
 * @brief header file for the usart_driver
 * 
 * @author Gunnar
 */
extern void USART_Init( unsigned int baud );
extern void SendString (char *s);  //used when polling transmit
extern void usart_transmit(unsigned char data); //Polling transmit one char/byte

extern unsigned char ch;
extern char flag_u;
