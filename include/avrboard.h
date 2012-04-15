#include<avr/io.h>

/**
 * @file
 * @brief Olimex AVR Board specific headerfile
 *
 * Contains definitions/funktions that are specific to the olimex
 * AVR-P40-USB-8535 board (http://www.olimex.com/dev/avr-p40-usb-8535.html)
 */

/**
 * @brief Setup LED pin as output
 *
 * This will imedeatly set the pin, the LED is connected to, as output. Since the
 * default value in registers is often 0, the LED will probably Light up ( Active
 * low behaviour, see the olimex schematic for reference: 
 * http://www.olimex.com/dev/images/AVR/avr-p40-usb-a-sch.png ).
 *
 * @see LED_ON
 * @see LED_OFF
 * @see LED_TOGGLE
 */
#define LED_ACTIVATE ( DDRB |= _BV( 0 ) )

/**
 * @brief Switch LED on
 *
 * If the LED pin is set up as output, the LED will light up.
 *
 * @see LED_ACTIVATE
 * @see LED_OFF
 * @see LED_TOGGLE
 */
#define LED_ON ( PORTB &= ~_BV( 0 ) )

/**
 * @brief Switch LED off
 *
 * If the LED pin is set up as output, the LED will not light up.
 *
 * @see LED_ACTIVATE
 * @see LED_ON
 * @see LED_TOGGLE
 */
#define LED_OFF ( PORTB |= _BV( 0 ) )

/**
 * @brief Toggle the LED
 *
 * If the LED pin is set up as output, the LED will be toggled, meaning it will
 * be switched off when the LED was on or switch on, when it was off.
 *
 * @see LED_ACTIVATE
 * @see LED_ON
 * @see LED_OFF
 */
#define LED_TOGGLE ( PORTB ^= _BV( 0 ) )

/**
 * @brief Represents button state
 *
 * BTN can be used as argument for boolean tests like in if-statements or while
 * loops. When the button is bushed, BTN will contain a non zero value (logical
 * one). When the button is not bushed the value will be zero.
 *
 * Example:
 * \code
 * if( BTN )
 * { LED_ON }
 * else 
 * { LED_OFF }
 * \endcode
 */
#define BTN !(PINB & 0b00010000)
