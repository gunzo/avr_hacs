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
	/* enables the interrupt when a compare match occurs. */\
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
 * @brief Deactivates CTC interupt for Timer 0
 *
 * The Clear Timer on Compare match interrupt will be dissabled for timer 0. If
 * the interupt was not enabled, this definition will waste a single cycle.
 *
 * @see T0_CTC_INT( TOP )
 * @see T0_CTC_INT_ON
 * @see t0_ctc_int_off(void)
 */
#define T0_CTC_INT_OFF ( TIMSK &= ~_BV( OCIE0 ) )


/**
 * @brief Deactivates CTC interupt for Timer 0
 *
 * The Clear Timer on Compare match interrupt will be dissabled for timer 0. If
 * the interupt was not enabled.
 *
 * This funktion uses the ::T0_CTC_INT_OFF as its Body.
 *
 * @see T0_CTC_INT_OFF
 * @see t0_ctc_int(uint8_t top)
 * @see t0_ctc_int_on(void)
 */
void t0_ctc_int_off(void)
{
	T0_CTC_INT_OFF;
}


/**
 * @brief Activates CTC interupt for Timer 0
 *
 * The Clear Timer on Compare match interrupt will be Enabled for timer 0. If
 * the interupt was not disabled, this definition will waste a single cycle.
 *
 * @see T0_CTC_INT( TOP )
 * @see T0_CTC_INT_OFF
 * @see t0_ctc_int_on(void)
 */
#define T0_CTC_INT_ON ( TIMSK |= _BV( OCIE0 ) ) 


/**
 * @brief Activates CTC interupt for Timer 0
 *
 * The Clear Timer on Compare match interrupt will be Enabled for timer 0. If
 * the interupt was not disabled.
 *
 * This funktion uses the ::T0_CTC_INT_ON as its Body.
 *
 * @see T0_CTC_INT_ON
 * @see T0_CTC_INT_OFF
 * @see t0_ctc_int_on(void)
 */
void t0_ctc_int_on(void)
{
	T0_CTC_INT_ON;
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


/**
 * @brief Resets timer 0 count value
 *
 * This will clear the value in the count register for timer 0. The timer will
 * count from 0 after this. 
 *
 * This can be done wherter the timer is running or not.
 *
 * @see T0_START( clockdivision )
 * @see T0_STOP
 */
#define T0_RESET ( TCNT0 = 0x00 )


/** 
 * @brief Setting up timer1 in Clear Timer on Compare mode
 *
 * The Clear Timer on Compare mode will clear the timer when it has counted to 
 * a certain value (Parameter TOP). This macro enables the interrupt for this
 * event. The physical output pin for the timer 1A compare register, oc1a, 
 * will be deactivated. This active behaviour might change in the future.
 *
 * @note Unlicke the other timers on the Atmega32, this timer is 16bits wide
 * 	 and therefore supports higher resolutions than other timers.
 *
 * @param TOP 16 bit value at witch the timer will be cleared.
 */
#define T1_CTC_INT( TOP ) do{ \
\
	/* Makeing sure physical pin OC1A is not touched */\
	/* Clearing COM1A0 and COM1A1 */\
	TCCR1A &= ~(_BV( COM1A0 )|_BV( COM1A1 ));\
\
	/* Setup CTC mode in the TCCR0 register */\
	TCCR1B |=   _BV( WGM12 );		/* Setting  WGM12       */\
	TCCR1A &= ~(_BV( WGM11 )|_BV( WGM10 ));	/* Clearing WGM11, WGM10*/\
	TCCR1B &= ~ _BV( WGM13 );		/* Clearing WGM13       */\
\
	/* Assigning TOP parameter to the Output Compare Register 1A */\
	OCR1A = TOP;\
\
	/* Setting the Output Compare Match Interrupt Enable 1A bit, this */\
	/* enables the interrupt when a compare match occurs. */\
	TIMSK |= _BV( OCIE1A );\
\
	/* Setting the Global Interupt Enable bit, so that all interrupts will */\
	/* work. */\
	SREG |= _BV( 7 );\
}while(0)


/** 
 * @brief Setting up timer1 in Clear Timer on Compare mode.
 *
 * This funktion uses the ::T1_CTC_INT( TOP ) definition as its body.
 * Therfore the behavour is exacly the same.
 *
 * Example usage: t1_ctc_int(500)
 *
 * @param top 16 bit value at witch the timer will be cleared.
 * @see T1_CTC_INT(TOP)
 * @see t1_start(uint16_t clockdivision)
 *
 */
void t1_ctc_int(uint16_t top)
{
	T1_CTC_INT( top );
}


/**
 * @brief Deactivates CTC interupt for Timer 1
 *
 * The Clear Timer on Compare match interrupt will be dissabled for timer 1. If
 * the interupt was not enabled, this definition will waste a single cycle.
 *
 * @see T1_CTC_INT( TOP )
 * @see T1_CTC_INT_ON
 * @see t1_ctc_int_off(void)
 */
#define T1_CTC_INT_OFF ( TIMSK &= ~_BV( OCIE1A ) )


/**
 * @brief Deactivates CTC interupt for Timer 1
 *
 * The Clear Timer on Compare match interrupt will be dissabled for timer 1. If
 * the interupt was not enabled.
 *
 * This funktion uses the ::T1_CTC_INT_OFF as its Body.
 *
 * @see T1_CTC_INT_OFF
 * @see t1_ctc_int(uint16_t top)
 * @see t1_ctc_int_on(void)
 */
void t1_ctc_int_off(void)
{
	T1_CTC_INT_OFF;
}


/**
 * @brief Activates CTC interupt for Timer 1
 *
 * The Clear Timer on Compare match interrupt will be Enabled for timer 1. If
 * the interupt was not disabled, this definition will waste a single cycle.
 *
 * @see T1_CTC_INT( TOP )
 * @see T1_CTC_INT_OFF
 * @see t1_ctc_int_on(void)
 */
#define T1_CTC_INT_ON ( TIMSK |= _BV( OCIE1A ) ) 


/**
 * @brief Activates CTC interupt for Timer 1
 *
 * The Clear Timer on Compare match interrupt will be Enabled for timer 1. If
 * the interupt was not disabled.
 *
 * This funktion uses the ::T1_CTC_INT_ON as its Body.
 *
 * @see T1_CTC_INT_ON
 * @see T1_CTC_INT_OFF
 * @see t1_ctc_int_on(void)
 */
void t1_ctc_int_on(void)
{
	T1_CTC_INT_ON;
}


/**
 * @brief Starting timer1.
 *
 * The timer will be started with the given division factor. See parameter 
 * \b CLOCKDIVISION.
 *
 * @param CLOCKDIVISION Dividing factor for the main clock.
 *                      Values are: \b 1 (no division), \b 8, \b 64, \b 256 and
 *                      \b 1024.
 *                      If another value than these is given then no division 
 *                      will be applied.
 * @see T1_STOP
 * @see t1_start(uint16_t clockdivision)
 */
#define T1_START( CLOCKDIVISION ) do{ \
	/* Converting CLOCKDIVISION to a binary represation. */\
	switch ( CLOCKDIVISION ) \
	{ \
		case 1:		TCCR1B |=  (_BV( CS10 )); /* Setting bits to 1*/ \
				TCCR1B &= ~(_BV( CS12 )|_BV( CS11 )); /* Setting bits to 0*/ \
				break; \
		case 8:		TCCR1B |=   _BV( CS11 ); /* Setting bits to 1*/ \
				TCCR1B &= ~(_BV( CS12 )|_BV( CS10 )); /* Setting bits to 0*/ \
				break; \
		case 64:	TCCR1B |=  (_BV( CS11 )|_BV( CS10 )); /* Setting bits to 1*/ \
				TCCR1B &= ~(_BV( CS12 )); /* Setting bits to 0*/ \
				break; \
		case 256:	TCCR1B |=  (_BV( CS12 )); /* Setting bits to 1*/ \
				TCCR1B &= ~(_BV( CS11 )|_BV( CS10 )); /* Setting bits to 0*/ \
				break; \
		case 1024:	TCCR1B |=  (_BV( CS12 )|_BV( CS10 )); /* Setting bits to 1*/ \
				TCCR1B &= ~(_BV( CS11 )); /* Setting bits to 0*/ \
				break; \
		default:	/* Default setting is the same as 1, no division. */ \
				TCCR1B |=  (_BV( CS10 )); /* Setting bits to 1*/ \
				TCCR1B &= ~(_BV( CS12 )|_BV( CS11 )); /* Setting bits to 0*/ \
				break; \
	} \
}while(0)


/** 
 * @brief Funktion for starting timer1.
 *
 * This funktion uses the ::T1_START( CLOCKDIVISION ) definition as its body.
 * Therfore the behavour is exacly the same.
 *
 * Example usage: t1_start(256);
 *
 * @param clockdivision Dividing factor for the main clock.
 *                      Values are: \b 1 (no division), \b 8, \b 64, \b 256 and
 *                      \b 1024.
 *                      If another value than these is given then no division 
 *                      will be applied.
 * @see T1_START( CLOCKDIVISION )
 *
 */
void t1_start(uint16_t clockdivision)
{
	T1_START( clockdivision );
}

/**
 * @brief Stopping timer1
 *
 * The timer will be stopped.
 *
 * @see T1_START( CLOCKDIVISION )
 */
#define T1_STOP (TCCR1B &= ~(_BV( CS12 )|_BV( CS11 )|_BV( CS10 )) )

/**
 * @brief Funktion for stopping timer1.
 *
 * This funktion uses the ::T1_STOP definition as its body. Therefore, the
 * behaviour is exacly the same.
 *
 * @see T1_STOP
 */
void t1_stop()
{
	T1_STOP;
}


/**
 * @brief Resets timer 1 count value
 *
 * This will clear the value in the count register for timer 1. The timer will
 * count from 1 after this. 
 *
 * This can be done wherter the timer is running or not.
 *
 * @see T1_START( clockdivision )
 * @see T1_STOP
 */
#define T1_RESET ( TCNT1 = 0x0000 )


