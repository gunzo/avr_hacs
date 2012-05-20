#include<avr/io.h>

/**
 * @file
 * @brief Olimex AVR Board specific headerfile
 *
 * Contains definitions/funktions that are specific to the olimex
 * AVR-P40-USB-8535 board (http://www.olimex.com/dev/avr-p40-usb-8535.html)
 *
 * @author Hannes
 */

#ifndef AVRBOARD_H_INCLUDED
#define AVRBOARD_H_INCLUDED

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
 *
 * @author Hannes
 */
#define LED_ACTIVATE ( DDRB |= _BV( 0 ) )

/**
 * @brief Switch LED on
 *
 * If the LED pin is set up as output, the LED will light up.
 *
 * @pre For this to have some effect, the port for the LED must be set as an
 *      output. This can be done with ::LED_ACTIVATE
 *
 * @see LED_ACTIVATE
 * @see LED_OFF
 * @see LED_TOGGLE
 *
 * @author Hannes
 */
#define LED_ON ( PORTB &= ~_BV( 0 ) )

/**
 * @brief Switch LED off
 *
 * If the LED pin is set up as output, the LED will not light up.
 *
 * @pre For this to have some effect, the port for the LED must be set as an
 *      output. This can be done with ::LED_ACTIVATE
 *
 * @see LED_ACTIVATE
 * @see LED_ON
 * @see LED_TOGGLE
 *
 * @author Hannes
 */
#define LED_OFF ( PORTB |= _BV( 0 ) )

/**
 * @brief Toggle the LED
 *
 * If the LED pin is set up as output, the LED will be toggled, meaning it will
 * be switched off when the LED was on or switch on, when it was off.
 *
 * @pre For this to have some effect, the port for the LED must be set as an
 *      output. This can be done with ::LED_ACTIVATE
 *
 * @see LED_ACTIVATE
 * @see LED_ON
 * @see LED_OFF
 *
 * @author Hannes
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
 *
 * @author Hannes
 */
#define BTN !(PINB & 0b00010000)


#endif /* AVRBOARD_H_INCLUDED */
