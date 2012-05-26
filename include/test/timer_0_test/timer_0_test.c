#include <avr/io.h>
#include <avr/interrupt.h>
#include </home/fragraider/ingenioerhoejskolen_i_koebenhavn_IHK/digital_electronics_2/avr_hacs/include/timers.h>
#include </home/fragraider/ingenioerhoejskolen_i_koebenhavn_IHK/digital_electronics_2/avr_hacs/include/avrboard.h>

#define F_CPU 10000000UL // 10 MHz
#include <util/delay.h>

/** @file
 *
 * @brief Tests timer 0 macros and functions in timer.h
 *
 * This file can be used to test functions and macros for timer 0 in 
 * ::timers.h . Some of the macros and functions have to be exclusively
 * uncommented to test them. The commends in the source code will help with
 * this.
 *
 * Note: In the comments for the source code, doomsday means, the LED will
 * stay off due to a disabled interrupt. Daysaver refers to the reactivation
 * of the interrupt some time after it was disabled.
 *
 * @author Hannes
 */

/** 
 * @brief Counts how often the timer compare check interrupt happens. 
 *
 * Used in ISR(TIMER0_COMP_vect)
 */
static uint8_t count=0;

#define TOP_val 150 

/** Interrupt for Clear Timer on Compare.
 *
 * Every 10th interrupt, the LED is toggled.
 *
 * When the interrupt happened 50 times, the parameters for the clock are 
 * changed.
 *
 * When the interrupt happened 100 times, the parameters for the clock are
 * changed again.
 *
 * After 200 interrupt calls, the tester can test macros or function that stop
 * the timer or disable the interrupt for the timer.
 *
 * This will stop the blinking of the led entirely... The interrupt is not
 * reachable anymore. Why this is not final and allows testing of other timer 
 * timer related functions, see the main function.
 *
 * @see count
 */
ISR(TIMER0_COMP_vect)
{
	// increment the counter.
	count++;

	// Every 10 steps...
	if ( count%10 == 1 ) 
	{
		// ...toggle the LED
		LED_TOGGLE;
	}


	if (count == 50)
	{
		// Setup something else using the ctc funktion
		t0_ctc( TOP_val );
		// The biggest valid value is used to see if the uint16_t
		// works on the avr.
		t0_start(1024);
	}

	if (count == 100)
	{
		// Setup something else using the ctc definition
		T0_CTC( TOP_val + 1 );
		T0_START(256);
	}

	if (count == 200)
	{
		// end it all...
		/* Uncomment the doomsday funktion of your choise, comment the others: */

		//t0_stop();
		//T0_STOP;

		/* Doomsday, but not realy... see Daysaver if in while loop in main */

		//T0_CTC_INT_OFF;
		t0_ctc_int_off();

		count = 0;
	}
}

/** Does nothing but setup and waiting. Everything else is handeled with interrupts. */
int main(void)
{
// Switching the Global interupt on
SREG |= _BV( 7 );

// Port B, pin 0 as output.
LED_ACTIVATE;
// Switch the LED off.
LED_OFF;

// Setup a clear on match timer interupt.
t0_ctc( 2*TOP_val );

// Delay, so the tester can prepare his eys.
_delay_ms(1000);

// Invalid value, the counter should run fast.
T0_START(4);

/* This next part causes a very short flashing of the LED at the very beginning
 * if T0_COMP_MATCH and T0_COMP_MATCH_CLEAR are working :) */
// We will not go on until we manualy caught a compare match
while( !T0_COMP_MATCH ) { LED_ON; }
T0_COMP_MATCH_CLEAR;
// We will also not go on if we could not clear the match flag.
while( T0_COMP_MATCH ) {}
LED_OFF;

// Delay before the rest of the test starts.
_delay_ms(1000);

// Activating the ctc interrupt
t0_ctc_int_on(); 

	// Loop forever
	while(1)
	{
		/* "Daysaver if" */
		if ( !(TIMSK & _BV( OCIE0 )) )
		{
			_delay_ms(5000); 
			/* Uncoment a Daysaver (or not) */
			//T0_CTC_INT_ON;
			t0_ctc_int_on(); 
		}


		/* Clear the timer value when the Putton is pushed
		 * (For testing T0_RESET. As long the putton is pushed, nothing
		 * should happen anymore if the compare value is not to small.)
		 */
		if ( BTN )
		{
			T0_RESET;
		}

	}
}
