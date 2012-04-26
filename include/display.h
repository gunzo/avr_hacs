/** @file
 * @brief Contains a display related methods.
 *
 * Contains a row of macros and definitions used to make writing to the display
 * easier.
 *
 * @warning Macros and funktions in this headerfile use timer 1. You should not 
 *          set up timer 1 with planing to run LCD macros or funktions 
 *          afterwards. Your settings will most likely be lost.
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

/**
 * @brief Sends a nibble to the LCD
 *
 * This macro sends a the lowest four bit of the parameter \b NIBBLE to the LCD
 * display ( DEM20485 SYH-LY/V ). Other Pin and Port definitions from this
 * headerfile are used.
 *
 * Since the display is not sencitive to long low phases between a pulse when
 * writing a byte, this macro can be preceded or postpositioned by time
 * commands that use some time (tested: 1 second). 
 *
 * Example for writing a byte with a delay between the nibble writes. (Main 
 * ommited):
 * \code
 * #define F_CPU 10000000UL // 10 MHz
 * #include <util/delay.h>
 *
 * ...
 *
 *  // Clears the display 
 *  LCD_WRITE_NIBBLE( 0  , 0b0000 ); // "0" "0" "0" "0"
 *   _delay_ms(2);
 *  LCD_WRITE_NIBBLE( 0  , 0b0001 ); // "0" "0" "0" "1"
 *
 * ...
 * \endcode
 *
 * @param RS Rgister Select bit. If 0, the nibble is written as command; if 1, 
 *           the nibble is writen into the charachter Memory. 
 *
 * @param NIBBLE The first four bit of this parameter will be send to the
 *               display.
 * @see LCD_RS
 * @see LCD_EN
 * @see LCD_D4
 * @see LCD_D5
 * @see LCD_D6
 * @see LCD_D7
 * @see LCD_PORT
 * @see LCD_DDR
 */
#define LCD_WRITE_NIBBLE( RS ,  NIBBLE ) do{\
	/* We have enought time to prepare everything for the writing. */\
	/* A test showed that the display is not sensitive to mutch longer Low */\
	/* times than Pulse times. */\
\
	/* Preparing. */\
	/* Setting up RS (Must happen as early as possible before EN goes high). */\
	if ( RS ) { LCD_PORT |= _BV( LCD_RS ); } else { LCD_PORT &= ~_BV( LCD_RS ); }\
	/* Stopping and reseting timer 1. */\
	T1_STOP;\
	T1_RESET;\
	/* Setting up Timer 1 in Clear Timer on Compare mode. */\
	T1_CTC( 20 , 10 );\
\
	/* Setup Data. */\
	/* If NIBBLE bit  X  is set,     set also  LCD_DX          oterhwise clear bit  LCD_DX  .*/\
	if( NIBBLE & _BV( 0 ) ) { LCD_PORT |= _BV( LCD_D4 ); } else { LCD_PORT &= ~_BV( LCD_D4 ); }\
	if( NIBBLE & _BV( 1 ) ) { LCD_PORT |= _BV( LCD_D5 ); } else { LCD_PORT &= ~_BV( LCD_D5 ); }\
	if( NIBBLE & _BV( 2 ) ) { LCD_PORT |= _BV( LCD_D6 ); } else { LCD_PORT &= ~_BV( LCD_D6 ); }\
	if( NIBBLE & _BV( 3 ) ) { LCD_PORT |= _BV( LCD_D7 ); } else { LCD_PORT &= ~_BV( LCD_D7 ); }\
\
	/* Generating EN signal. */\
	/* Starting timer 1. */\
	T1_START( 64 );\
\
	/* HIGH phase. */\
	LCD_PORT |= _BV( LCD_EN ); /* EN HIGH */\
	/* Waiting for the EXTRA compare match. */\
	while( !T1_COMP_MATCH_EXTRA );\
\
	/* LOW phase. */\
	LCD_PORT &= ~_BV( LCD_EN ); /* EN LOW */\
	/* Waiting for the TOP compare match. */\
	while( !T1_COMP_MATCH_TOP );\
\
	/* Cleaning up. */\
	/* Stopping and reseting timer 1. */\
	T1_STOP;\
	T1_RESET;\
	/* Clearing the EXTRA compare match flag. */\
	T1_COMP_MATCH_EXTRA_CLEAR;\
	/* Clearing the TOP compare match flag. */\
	T1_COMP_MATCH_TOP_CLEAR;\
}while(0)
