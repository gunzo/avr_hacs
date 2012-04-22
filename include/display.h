
#define F_CPU 1000000 // 1 MHz
#include <util/delay.h>

/** @file
 * @brief Contains a display related methods.
 *
 * Contains a row of macros and definitions used to make writeing to the display
 * easier.
 */

/**
 * @brief LCD Register Select port number.
 *
 * @author Hannes
 */
#define LCD_RS 2

/**
 * @brief LCD port Enable port number.
 *
 * @author Hannes
 */
#define LCD_EN 3

/**
 * @brief LCD port Data4 port number.
 *
 * @author Hannes
 */
#define LCD_D4 4

/**
 * @brief LCD port Data5 port number.
 *
 * @author Hannes
 */
#define LCD_D5 5

/**
 * @brief LCD port Data6 port number.
 *
 * @author Hannes
 */
#define LCD_D6 6

/**
 * @brief LCD port Data7 port number.
 *
 * @author Hannes
 */
#define LCD_D7 7


/**
 * @brief LCD comunication port.
 *
 * @author Hannes
 */
#define LCD_PORT PORTA

/**
 * @brief LCD Data Direction Register.
 *
 * Used to setup the pins on LCD_PORT as output pins.
 *
 * @author Hannes
 */
#define LCD_DDR DDRA

/**
 * @brief Sets the pins on ::LCD_PORT as output
 *
 * Uses ::LCD_DDR to do so. Into every pin that is needed as output pin, we
 * write a 1.
 *
 * @author Hannes
 */
#define LCD_PORT_SETUP (LCD_DDR |= (_BV( LCD_RS )\
                                   |_BV( LCD_EN )\
				   |_BV( LCD_D4 )\
				   |_BV( LCD_D5 )\
				   |_BV( LCD_D6 )\
				   |_BV( LCD_D7 )\
				   ))
