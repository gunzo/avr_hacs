#include <avr/io.h>
#include <avr/interrupt.h>
#include </home/fragraider/ingenioerhoejskolen_i_koebenhavn_IHK/digital_electronics_2/avr_hacs/include/timers.h>
#include </home/fragraider/ingenioerhoejskolen_i_koebenhavn_IHK/digital_electronics_2/avr_hacs/include/avrboard.h>

#define F_CPU 10000000UL // 10 MHz
#include <util/delay.h>

/** @file
 *
 * @brief Tests timer 1 macros and functions in timer.h
 *
 * This file can be used to test functions and macros for timer 1 in 
 * ::timers.h . Some of the macros and functions have to be exclusively
 * uncommented to test them. The comments in the source code will help with
 * this.
 *
 * ::timers.h allows access to the second compare register timer 1 has, this
 * will be tested here too.
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
 * Used in ISR(TIMER1_COMPA_vect)
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
ISR(TIMER1_COMPA_vect)
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
		t1_ctc( TOP_val , 0 );
		// The biggest valid value is used to see if the uint16_t
		// works on the avr.
		t1_start(1024);
	}

	if (count == 100)
	{
		// Setup something else using the ctc definition
		T1_CTC( TOP_val + 1 , 0 );
		T1_START(256);
	}

	if (count == 200)
	{
		// end it all...
		/* Uncomment the doomsday funktion of your choise, comment the others: */

		//t1_stop();
		//T1_STOP;

		/* Doomsday, but not realy... see "Daysaver if" in while loop in main */

		//T1_CTC_INT_OFF;
		t1_ctc_int_off();

		count = 0;
	}
}

/** 
 * @brief Allows controll over the Programm flow outside the interupt.
 *
 * In the main, we can test the Timer reset funktionality and the reactivation
 * of the interrupt itself.
 *
 */
int main(void)
{
// Switching the Global interupt on
SREG |= _BV( 7 );

// Port B, pin 0 as output.
LED_ACTIVATE;
// Switch the LED off.
LED_OFF;

// Setup a clear on match timer interupt.
t1_ctc( 2*TOP_val , TOP_val );

// Delay, so that the tester can prepare his eys
_delay_ms(1000);

// Invalid value, the counter should run fast, the LED imideatly ON.
T1_START(4);

/* This next part causes a _VERY_ short flash of the LED at the very 
 * beginning if T0_COMP_MATCH_EXTRA and T0_COMP_MATCH_EXTRA_CLEAR are working
 * :). If one of them is not working, nothing more will happen, the LED will 
 * never change.*/
// We will not go on until we manualy caught a compare match
while( !T1_COMP_MATCH_EXTRA ) { LED_ON; }
T1_COMP_MATCH_EXTRA_CLEAR;
// We will also not go on if we could not clear the match flag.
while( T1_COMP_MATCH_EXTRA ) {}
LED_OFF;

/* To see some effect, we stop the timer and start it again afer a delay. */
T1_STOP;
// Delay, so that the tester can prepare his eys
_delay_ms(1000);
T1_START(4);

/* This next part causes a very short flashing of the LED at the very beginning
 * if T0_COMP_MATCH and T0_COMP_MATCH_CLEAR are working :). If one of them is 
 * not working, nothing more will happen, the LED will never change. */
// We will not go on until we manualy caught a compare match
while( !T1_COMP_MATCH_TOP ) { LED_ON; }
T1_COMP_MATCH_TOP_CLEAR;
// We will also not go on if we could not clear the match flag.
while( T1_COMP_MATCH_TOP ) {}
LED_OFF;

// Delay before the rest of the test starts.
_delay_ms(1000);

// Activating the ctc interrupt
t1_ctc_int_on();

	// Loop forever
	while(1)
	{
		/* "Daysaver if" */
		if ( !(TIMSK & _BV( OCIE1A )) )
		{
			_delay_ms(5000); 
			/* Uncoment a Daysaver (or not) */
			//T1_CTC_INT_ON;
			t1_ctc_int_on(); 
		}


		/* Clear the timer value when the Putton is pushed
		 * (For testing T1_RESET. As long the putton is pushed, nothing
		 * should happen anymore if the compare value is not to small.)
		 */
		if ( BTN )
		{
			T1_RESET;
		}
	}
}
