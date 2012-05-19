#include <avr/io.h>
#include <avr/interrupt.h>
#include </home/fragraider/ingenioerhoejskolen_i_koebenhavn_IHK/digital_electronics_2/avr_hacs/include/timers.h>
#include </home/fragraider/ingenioerhoejskolen_i_koebenhavn_IHK/digital_electronics_2/avr_hacs/include/avrboard.h>

#define F_CPU 1000000UL // 1 MHz
#include <util/delay.h>

/** @file
 *
 * @brief Tests timer 1 macros and funktions in timer.h
 *
 * This file can be used to test funktions and macros for timer 1 in 
 * ::timers.h . Some of the macros and funktions have to be exclusively
 * uncommented to test them. The commends in the source code will help with
 * this. Since timers.h provides access to some more features special to
 * timer 1, this testfile is somewhat more complex than the timer 0 
 * testfile ( ::timer_0_test.c ).
 *
 * @author Hannes
 */

/** 
 * @brief Counts how often the timer compare check interrupt happens. 
 *
 * Used in ISR(TIMER1_COMPA_vect)
 */
static uint8_t count=0;

#define TOP_val 60

/** 
 * @brief Interrupt for Clear Timer on Compare interrupt.
 *
 * When the Interrupt happend 10 times, the LED is
 * toggled.
 * The LED will blink 3 times long, 3 times short. What happens then can be
 * choosen in this interupt. See 
 * \code
 * if (count == 200)
 * \endcode
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
		PORTB ^= _BV( 0 );
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
DDRB |= _BV( 0 );
// Switch the LED off.
PORTB |= _BV( 0 );

// Setup a clear on match timer interupt.
t1_ctc( TOP_val , TOP_val/2 );

// Invalid value, the counter should run fast, the LED imideatly ON.
T1_START(4);

/* This next part causes a _VERY_ short flashing of the LED at the very 
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
_delay_ms(500);
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
