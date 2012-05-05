#include <avr/io.h>
#include <stdint.h>

/** @file
 * @brief Timer access headerfile.
 *
 * Defines macros that allow easyer, but still generic, access to the timers and several of their modes.
 * 
 */

#ifndef TIMERS_H_INCLUDED
#define TIMERS_H_INCLUDED

/** 
 * @brief Setting up timer0 in Clear Timer on Compare mode
 *
 * The Clear Timer on Compare mode will clear the timer when it has counted to 
 * a certain value (Parameter TOP). The physical output bin for timer 0, dc0, 
 * will be deactivated. This active behaviour might change in the future.
 *
 * @note To enable the Interupt at a compare match (or clear action), run
 *       \code 
 *       T0_CTC_INT_ON;
 *       \endcode 
 *       after this macro.
 *
 * @param TOP 8 bit value at wich the timer will be cleared.
 *
 * @see T0_START( CLOCKDIVISION )
 * @see T0_COMP_MATCH
 * @see T0_CTC_INT_ON 
 */
#define T0_CTC( TOP ) do{ \
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
}while(0)


/**
 * @brief Represents timer 0 compare match state 
 *
 * This can be used as argument for boolean tests like in if-statements or while
 * loops. When a compare match between the timer 0 value and OCR0 occured, this
 * will return a logical 1 and a logical 0 otherwise.
 *
 * Example:
 * \code
 * if ( T0_COMP_MATCH ) 
 * { ... }
 *
 * while ( !T0_COMP_MATCH )
 * { ... }
 * \endcode
 *
 * @warning If no Interupt vector for the compare match is executed, this flag
 *          must be cleared manulay. This can be done with 
 *          ::T0_COMP_MATCH_CLEAR.
 *
 * @see T0_CTC( TOP )
 * @see T0_COMP_MATCH_CLEAR
 */
#define T0_COMP_MATCH (TIFR & _BV( OCF0 ))

/**
 * @brief Clears the compare match flag for timer 0
 *
 * If a compare match between the timer 0 value and OCR0 occured, the compare 
 * match flag is set. If this flag should be cleared manualy, this macro can be
 * used.
 *
 * @see T0_CTC( TOP )
 * @see T0_COMP_MATCH
 */
#define T0_COMP_MATCH_CLEAR (TIFR |= _BV( OCF0 ))

/** 
 * @brief Setting up timer0 in Clear Timer on Compare mode.
 *
 * This funktion uses the ::T0_CTC(TOP) definition as its body.
 * Therfore the behavour is exacly the same.
 *
 * @note To enable the Interupt at a compare match (or clear action), run
 *       \code 
 *       T0_CTC_INT_ON;
 *       \endcode 
 *       after this macro.
 *
 * @param top 8 bit value at wich the timer will be cleared.
 * @see T0_CTC(TOP)
 * @see t0_start(uint16_t clockdivision)
 *
 */
void t0_ctc(uint8_t top)
{
	T0_CTC( top );
}


/**
 * @brief Deactivates CTC interupt for Timer 0
 *
 * The Clear Timer on Compare match interrupt will be dissabled for timer 0. If
 * the interupt was not enabled, this definition will waste a single cycle.
 *
 * @see T0_CTC( TOP )
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
 * @see T0_CTC( TOP )
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
 * @param clockdivision 8 bit value at wich the timer will be cleared.
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
 * This can be done wherther the timer is running or not.
 *
 * @see T0_START( CLOCKDIVISION )
 * @see T0_STOP
 */
#define T0_RESET ( TCNT0 = 0x00 )


/** 
 * @brief Setting up timer1 in Clear Timer on Compare mode
 *
 * The Clear Timer on Compare mode will clear the timer when it has counted to 
 * a certain value (Parameter TOP). The physical output pins for compare 
 * registers 1 A and 1 B, OC1A and OC1B, will be deactivated. This active
 * behaviour might change in the future.
 *
 * @note To enable the Interupt at a compare match (or clear action), run
 *       \code 
 *       T1_CTC_INT_ON;
 *       \endcode 
 *       after this macro.
 *
 * @note Unlicke the other timers on the Atmega32, this timer is 16bits wide
 * 	 and therefore supports higher resolutions than other timers.
 *
 * @param TOP 16 bit value at witch the timer will be cleared. 
 * @param COMP_EXTRA 16 bit value at witch a second compartion can be made. See
 *        ::T1_COMP_MATCH_EXTRA
 *
 * @see T1_START( CLOCKDIVISION )
 * @see T1_COMP_MATCH_TOP
 * @see T1_CTC_INT_ON
 */
#define T1_CTC( TOP , COMP_EXTRA ) do{ \
\
	/* Makeing sure physical pins OC1A and OC1B are not touched */\
	/* Clearing COM1A0 and COM1A1 */\
	TCCR1A &= ~(_BV( COM1A0 )|_BV( COM1A1 ));\
	/* Clearing COM1B0 and COM1B1 */\
	TCCR1A &= ~(_BV( COM1B0 )|_BV( COM1B1 ));\
\
	/* Setup CTC mode in the TCCR0 register */\
	TCCR1B |=   _BV( WGM12 );		/* Setting  WGM12       */\
	TCCR1A &= ~(_BV( WGM11 )|_BV( WGM10 ));	/* Clearing WGM11, WGM10*/\
	TCCR1B &= ~ _BV( WGM13 );		/* Clearing WGM13       */\
\
	/* Assigning TOP parameter to the Output Compare Register 1 A */\
	OCR1A = TOP;\
	/* Assigning TOP parameter to the Output Compare Register 1 B */\
	OCR1B = COMP_EXTRA;\
}while(0)


/**
 * @brief Represents timer 1 compare match state with TOP.
 *
 * This can be used as argument for boolean tests like in if-statements or while
 * loops. When a compare match between the timer 1 value and OCR1A occured, this
 * will return a logical 1 and a logical 0 otherwise.
 *
 * Example:
 * \code
 * if ( T0_COMP_MATCH_TOP ) 
 * { ... }
 *
 * while ( !T0_COMP_MATCH_TOP )
 * { ... }
 * \endcode
 *
 * @note If the ctc mode with timer one is used, the comparsion for clearing
 *       the timer can only happen with Output Compare Register 1 A. So, if the
 *       ctc mode for timer 1 is set up, this is one of the macros to go with.
 *
 * @warning If no Interupt vector for the compare match is executed, this flag
 *          must be cleared manulay. This can be done with 
 *          ::T1_COMP_MATCH_TOP_CLEAR.
 *
 * @see T1_CTC( TOP , COMP_EXTRA )
 * @see T1_COMP_MATCH_TOP_CLEAR
 */
#define T1_COMP_MATCH_TOP (TIFR & _BV( OCF1A ))

/**
 * @brief Clears the compare match flag for timer 1 with OCR1A
 *
 * If a compare match between the timer 1 value and OCR1A occured, the compare 
 * match flag is set. If this flag should be cleared manualy, this macro can be
 * used.
 *
 * @see T1_CTC( TOP , COMP_EXTRA)
 * @see T1_COMP_MATCH_TOP
 * @see T1_COMP_MATCH_EXTRA
 */
#define T1_COMP_MATCH_TOP_CLEAR (TIFR |= _BV( OCF1A ))


/**
 * @brief Represents timer 1 compare match state with COMP_EXTRA.
 *
 * This can be used as argument for boolean tests like in if-statements or while
 * loops. When a compare match between the timer 1 value and COMP_EXTRA occured,
 * this will return a logical 1 and a logical 0 otherwise.
 *
 * Example:
 * \code
 * if ( T1_COMP_MATCH_EXTRA ) 
 * { ... }
 *
 * while ( !T1_COMP_MATCH_EXTRA )
 * { ... }
 * \endcode
 *
 * @note If the ctc mode with timer one is used, the comparsion for clearing
 *       the timer can only happen with Output Compare Register 1 A. So, if the
 *       ctc mode for timer 1 is set up, this is one of the macros to go with.
 *
 * @warning If no Interupt vector for the compare match is executed, this flag
 *          must be cleared manulay. This can be done with 
 *          ::T1_COMP_MATCH_EXTRA_CLEAR.
 *
 * @see T1_CTC( TOP , COMP_EXTRA )
 * @see T1_COMP_MATCH_EXTRA_CLEAR
 * @see T1_COMP_MATCH_TOP
 */
#define T1_COMP_MATCH_EXTRA (TIFR & _BV( OCF1B ))

/**
 * @brief Clears the compare match flag for timer 1 with OCR1A
 *
 * If a compare match between the timer 1 value and OCR1A occured, the compare 
 * match flag is set. If this flag should be cleared manualy, this macro can be
 * used.
 *
 * @see T1_CTC( TOP , COMP_EXTRA)
 * @see T1_COMP_MATCH_EXTRA
 * @see T1_COMP_MATCH_TOP
 */
#define T1_COMP_MATCH_EXTRA_CLEAR (TIFR |= _BV( OCF1B ))



/** 
 * @brief Setting up timer1 in Clear Timer on Compare mode.
 *
 * This funktion uses the ::T1_CTC( TOP ) definition as its body.
 * Therfore the behavour is exacly the same.
 *
 * @note To enable the Interupt at a compare match (or clear action), run
 *       \code 
 *       T1_CTC_INT_ON;
 *       \endcode 
 *       after this macro.
 *
 * @param top 16 bit value at witch the timer will be cleared.
 * @param comp_extra 16 bit value at witch a second compartion can be made. See
 *        ::T1_COMP_MATCH_EXTRA
 *
 * @see T1_CTC(TOP)
 * @see t1_start(uint16_t clockdivision)
 *
 */
void t1_ctc(uint16_t top , uint16_t comp_extra)
{
	T1_CTC( top , comp_extra);
}


/**
 * @brief Deactivates CTC interupt for Timer 1
 *
 * The Clear Timer on Compare match interrupt will be dissabled for timer 1. If
 * the interupt was not enabled, this definition will waste a single cycle.
 *
 * @see T1_CTC( TOP )
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
 * @see t1_ctc(uint16_t top , uint16_t comp_extra)
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
 * @see T1_CTC( TOP )
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
 * This can be done wherther the timer is running or not.
 *
 * @see T1_START( CLOCKDIVISION )
 * @see T1_STOP
 */
#define T1_RESET ( TCNT1 = 0x0000 )


#endif /* TIMERS_H_INCLUDED */
