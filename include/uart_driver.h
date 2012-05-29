#include <avr/io.h>
#include <avr/interrupt.h>

extern void USART_Init( unsigned int baud );
extern void SendString (char *s);  //used when polling transmit
extern void sendmsg (char *s); //used when transmit interupts is used
extern void usart_transmit(unsigned char data); //Polling transmit one char/byte
extern char usart_receive();  //polling receive one byte
extern unsigned char ch;
extern char flag_u;
