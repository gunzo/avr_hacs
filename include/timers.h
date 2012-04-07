#include <avr/io.h>
#include <stdint.h>

/** @file
 * @brief Timer access headerfile.
 *
 * Defines macros that allow easyer, but still generic, access to the timers and several of their modes.
 * 
 */



/** 
 * @brief Setting up timer0 in Clear Timer on Compare mode
 *
 * The Clear Timer on Compare mode will clear the timer when it has counted to 
 * a certain value (Parameter TOP). This macro enables the interrupt for this
 * event. The physical output bin for timer 0, dc0, will be deactivated. This
 * active behaviour might change in the future.
 *
 * @warning This macro does not start the counter, you can do so with
 *          T0_START( CLOCKDIVISION ).
 *
 * @param TOP 8 bit value at wich the timer will be cleared.
 * @see T0_START( CLOCKDIVISION )
 */
#define T0_CTC_INT( TOP ) do{ \
\
	/* Makeing sure physical pin OC0 is not touched */\
	/* Clearing COM00 and COM01 */\
	TCCR0 &= ~(_BV( COM00 )|_BV( COM01 ));\
\
	/* Setup CTC mode in the TCCR0 register */\
	TCCR0 |=  _BV( WGM01 );  /* Setting WGM01 */\
	TCCR0 &= ~_BV( WGM00 );  /* Clearing WGM00 */\
\
	/* Assigning TOP parameter to the Output Compare Register 0 */\
	OCR0 = TOP;\
\
	/* Setting the Output Compare Match Interrupt Enable 0 bit, this */\
	/* enables the interrupt when */\
	TIMSK |= _BV( OCIE0 );\
\
	/* Setting the Global Interupt Enable bit, so that all interrupts will */\
	/* work. */\
	SREG |= _BV( 7 );\
}while(0)


/** 
 * @brief Setting up timer0 in Clear Timer on Compare mode.
 *
 * This funktion uses the ::T0_CTC_INT(TOP) definition as its body.
 * Therfore the behavour is exacly the same.
 *
 * Example usage: t0_ctc_int(50)
 *
 * @param top 8 bit value at wich the timer will be cleared.
 * @see T0_CTC_INT(TOP)
 * @see t0_start(uint16_t clockdivision)
 *
 */
void t0_ctc_int(uint8_t top)
{
	T0_CTC_INT( top );
}


/**
 * @brief Starting timer0.
 *
 * The timer will be started with the given division factor. See parameter 
 * \b CLOCKDIVISION.
 *
 * @param CLOCKDIVISION Dividing factor for the main clock.
 *                      Values are: \b 1 (no division), \b 8, \b 64, \b 256 and
 *                      \b 1024.
 *                      If another value than these is given then no division 
 *                      will be applied.
 * @see T0_STOP
 * @see t0_start(uint16_t clockdivision)
 */
#define T0_START( CLOCKDIVISION ) do{ \
	/* Converting CLOCKDIVISION to a binary represation. */\
	switch ( CLOCKDIVISION ) \
	{ \
		case 1:		TCCR0 |=  (_BV( CS00 )); /* Setting bits to 1*/ \
				TCCR0 &= ~(_BV( CS02 )|_BV( CS01 )); /* Setting bits to 0*/ \
				break; \
		case 8:		TCCR0 |=   _BV( CS01 ); /* Setting bits to 1*/ \
				TCCR0 &= ~(_BV( CS02 )|_BV( CS00 )); /* Setting bits to 0*/ \
				break; \
		case 64:	TCCR0 |=  (_BV( CS01 )|_BV( CS00 )); /* Setting bits to 1*/ \
				TCCR0 &= ~(_BV( CS02 )); /* Setting bits to 0*/ \
				break; \
		case 256:	TCCR0 |=  (_BV( CS02 )); /* Setting bits to 1*/ \
				TCCR0 &= ~(_BV( CS01 )|_BV( CS00 )); /* Setting bits to 0*/ \
				break; \
		case 1024:	TCCR0 |=  (_BV( CS02 )|_BV( CS00 )); /* Setting bits to 1*/ \
				TCCR0 &= ~(_BV( CS01 )); /* Setting bits to 0*/ \
				break; \
		default:	/* Default setting is the same as 1, no division. */ \
				TCCR0 |=  (_BV( CS00 )); /* Setting bits to 1*/ \
				TCCR0 &= ~(_BV( CS02 )|_BV( CS01 )); /* Setting bits to 0*/ \
				break; \
	} \
}while(0)


/** 
 * @brief Funktion for starting timer0.
 *
 * This funktion uses the ::T0_START( CLOCKDIVISION ) definition as its body.
 * Therfore the behavour is exacly the same.
 *
 * Example usage: t0_start(256);
 *
 * @param top 8 bit value at wich the timer will be cleared.
 * @see T0_START( CLOCKDIVISION )
 *
 */
void t0_start(uint16_t clockdivision)
{
	T0_START( clockdivision );
}

/**
 * @brief Stopping timer0
 *
 * The timer will be stopped.
 *
 * @see T0_START( CLOCKDIVISION )
 */
#define T0_STOP (TCCR0 &= ~(_BV( CS02 )|_BV( CS01 )|_BV( CS00 )) )

/**
 * @brief Funktion for stopping timer0.
 *
 * This funktion uses the ::T0_STOP definition as its body. Therefore, the
 * behaviour is exacly the same.
 *
 * @see T0_STOP
 */
void t0_stop()
{
	T0_STOP;
}
