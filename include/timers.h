/** Funktions and macros that allow easier use of timers in the atmega32.*/

#include <avr/io.h>



/** Setting up timer1 in Clear Timer on Compare mode.
 * Example usage:
 * /code{.c}
 * T0_CTC_INT(50, 4)
 * /encode
 *
 * @param TOP 8 bit compare value at wich the timer should be cleared.
 * @param prescaler Selecting clock source. Bit 2, 1 and 0 are written into CS02, CS01 and CS00 see Atmega32 manual (2503Q-AVR-02/11) p.82.
 */
#define T0_CTC_INT(TOP, prescaler) do{ \
	/* Makeing sure physical pin OC0 is not touched */\
	/* Clearing COM00 and COM01 */\
	TCCR0 &= ~(_BV( COM00 )|_BV( COM01 ));\
	/* Setup CTC mode in the TCCR0 register */\
	TCCR0 |= _BV(WGM01);  /* Setting WGM01 */\
	TCCR0 &= ~_BV(WGM00);  /* Clearing WGM00 */\
\
	/* Assigning TOP parameter to the Output Compare Register 0 */\
	OCR0 = TOP;\
\
	/* Assigning the values in prescaler to CS0 bits in the register.*/\
	/* Clear CS02, CS01 and CS00 bits */\
	TCCR0 &= ~(_BV( CS02 )|_BV( CS01 )|_BV( CS00 ));\
	/* Setting CS02, CS01 and CS00 when the coresponding bits in the */\
	/* parameter "prescaler" are set. Even though it is not necessary */\
	/* to do this, it will help improve compatibility with future devices. */\
	if (prescaler & _BV( 2 )) { TCCR0 |= _BV( CS02 ); } else { TCCR0 &= ~_BV( CS02 ); }\
	if (prescaler & _BV( 1 )) { TCCR0 |= _BV( CS01 ); } else { TCCR0 &= ~_BV( CS01 ); }\
	if (prescaler & _BV( 0 )) { TCCR0 |= _BV( CS00 ); } else { TCCR0 &= ~_BV( CS00 ); }\
\
	/* Setting the Output Compare Match Interrupt Enable 0 bit, this */\
	/* enables the interrupt when */\
	TIMSK |= _BV( OCIE0 );\
\
	/* Setting the Global Interupt Enable bit, so that all interrupts will */\
	/* work. */\
	SREG |= _BV( 7 );\
}while(0)
