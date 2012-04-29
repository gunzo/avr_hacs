/** @file
 * @brief Contains display related methods.
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

#ifndef LCD_CLOCKDIVISION
/**
 * @brief This is the clockdivision F_CPU is divided by.
 *
 * This variable can be overriten by defining it before display.h is included:
 * \code
 * LCD_CLOCKDIVISION <new value>
 * #include <include/display.h>
 * \endcode
 *
 * @warning Only some values are valid. Pleas check ::T0_START  or 
 *          ::T1_START for more infotmations!
 *
 * @see LCD_EXTRA_DIV
 * @see LCD_TOP_DIV
 * @see T1_START
 * 
 * @author Hannes
 */
# define LCD_CLOCKDIVISION 64
#endif

#ifndef LCD_EXTRA_DIV
/**
 * @brief EXTRA factor multiplies to LCD_CLOCKDIVISION.
 *
 * This variable can be overriten by defining it before display.h is included:
 * \code
 * LCD_EXTRA_DIV <new value>
 * #include <include/display.h>
 * \endcode
 *
 * @see LCD_CLOCKDIVISION
 * @see LCD_TOP_DIV
 * @see T1_CTC
 *
 * @author Hannes
 */
# define LCD_EXTRA_DIV 10
#endif

#ifndef LCD_TOP_DIV
/**
 * @brief TOP factor multiplies to LCD_CLOCKDIVISION.
 *
 * This variable can be overriten by defining it before display.h is included:
 * \code
 * LCD_EXTRA_DIV <new value>
 * #include <include/display.h>
 * \endcode
 *
 * @see LCD_CLOCKDIVISION
 * @see LCD_EXTRA_DIV
 * @see T1_CTC
 *
 * @author Hannes
 */
# define LCD_TOP_DIV 20
#endif

/* This include must be after the definitions above. */
#include <include/display_snippets.h>

/**
 * @brief Sends a nibble to the LCD
 *
 * This macro sends  the lowest four bit of the parameter \b NIBBLE to the LCD.
 *
 * Since the display is not sensitive to long low phases between a pulse when
 * writing a byte, this macro can be preceded or postpositioned by commands 
 * that use some time (tested: 1 second). 
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
 * @param WRITE_CHAR_EN If 0, the nibble is written as command; if non 0, the
 *                      nibble is writen into the character Memory. 
 *
 * @param NIBBLE The first four bits of this parameter will be send to the
 *               display.
 *
 * @author Hannes
 */
#define LCD_WRITE_NIBBLE( WRITE_CHAR_EN , NIBBLE ) do{\
	/* Set the needed pins up. */\
	LCD_PORT_SETUP;\
	/* If WRITE_CHAR_EN is true...  */\
	if ( WRITE_CHAR_EN )\
	/* ...then the LCD should interpret the data as a character... */\
	{ LCD_CHAR_MODE; }\
	else\
	/* ...else it should interpret the data as a command. */\
	{ LCD_CMD_MODE; }\
	/* Prepares everything for the wait statements. */\
	LCD_WAIT_SETUP;\
	/* Start the wait timer. */\
	LCD_WAIT_TIMER_START;\
	/* Setting up the data that should to be send. */\
	LCD_DATA_SETUP_LOW_NIBBLE( NIBBLE );\
	/* Set clock high and wait. */\
	LCD_WAIT_CLK_HIGH;\
	/* Set clock low and wait. */\
	LCD_WAIT_CLK_LOW;\
	/* Done. Stop the wait timer. */\
	LCD_WAIT_TIMER_STOP;\
}while(0)

/**
 * @brief Sends a nibble as command to the LCD
 *
 * This macro is just a frontend to LCD_WRITE_NIBBLE( WRITE_CHAR_EN , NIBBLE )
 * that sets WRITE_CHAR_EN to 0 in order to enabel command mode.
 *
 * @param NIBBLE Nibble that should be send to the Display.
 *
 * @see LCD_WRITE_NIBBLE( WRITE_CHAR_EN , NIBBLE )
 * @see LCD_CHAR_NIBBLE( NIBBLE )
 *
 * @author Hannes
 */
#define LCD_CMD_NIBBLE( NIBBLE ) LCD_WRITE_NIBBLE( 0 , NIBBLE )

/**
 * @brief Sends a nibble as a character to the LCD
 *
 * This macro is just a frontend to LCD_WRITE_NIBBLE( WRITE_CHAR_EN , NIBBLE )
 * that sets WRITE_CHAR_EN to 1 in order to enabel charackter mode.
 *
 * @param NIBBLE Nibble that should be send to the Display.
 *
 * @see LCD_WRITE_NIBBLE( WRITE_CHAR_EN , NIBBLE )
 * @see LCD_CMD_NIBBLE( NIBBLE )
 *
 * @author Hannes
 */
#define LCD_CHAR_NIBBLE( NIBBLE ) LCD_WRITE_NIBBLE( 1 , NIBBLE )

/**
 * @brief Sends a byte to the LCD
 *
 * This macro sends the lowest four bit of the parameter \b BYTE, to the LCD,
 * then the highest 4 bit.
 *
 * Since the display is not sensitive to long low phases between a pulse when
 * writing a byte, this macro can be preceded or postpositioned by commands 
 * that use some time (tested: 1 second). 
 *
 * @param WRITE_CHAR_EN If 0, the nibble is written as command; if non 0, the
 *                      nibble is writen into the character Memory. 
 *
 * @param BYTE The first four bits of this parameter will be send to the
 *             display.
 *
 * @author Hannes
 */
#define LCD_WRITE_BYTE( WRITE_CHAR_EN , BYTE ) do{\
	/* Set the needed pins up. */\
	LCD_PORT_SETUP;\
	/* If WRITE_CHAR_EN is true...  */\
	if ( WRITE_CHAR_EN )\
	/* ...then the LCD should interpret the data as a character... */\
	{ LCD_CHAR_MODE; }\
	else\
	/* ...else it should interpret the data as a command. */\
	{ LCD_CMD_MODE; }\
	/* Prepares everything for the wait statements. */\
	LCD_WAIT_SETUP;\
	/* Start the wait timer. */\
	LCD_WAIT_TIMER_START;\
	/* Setting up the data that should to be send, high nibble. */\
	LCD_DATA_SETUP_HIGH_NIBBLE( BYTE );\
	/* Set clock high and wait. */\
	LCD_WAIT_CLK_HIGH;\
	/* Set clock low and wait. */\
	LCD_WAIT_CLK_LOW;\
\
	/* Setting up the data that should to be send, low nibble. */\
	LCD_DATA_SETUP_LOW_NIBBLE( BYTE );\
	/* Set clock high and wait. */\
	LCD_WAIT_CLK_HIGH;\
	/* Set clock low and wait. */\
	LCD_WAIT_CLK_LOW;\
	/* Done. Stop the wait timer. */\
	LCD_WAIT_TIMER_STOP;\
}while(0)

/**
 * @brief Sends a byte as command to the LCD
 *
 * This macro is just a frontend to LCD_WRITE_BYTE( WRITE_CHAR_EN , BYTE )
 * that sets WRITE_CHAR_EN to 0 in order to enabel command mode.
 *
 * @param BYTE Byte that should be send to the Display.
 *
 * @see LCD_WRITE_NIBBLE( WRITE_CHAR_EN , NIBBLE )
 * @see LCD_CHAR_NIBBLE( NIBBLE )
 *
 * @author Hannes
 */
#define LCD_CMD_BYTE( BYTE ) LCD_WRITE_BYTE( 0 , BYTE )

/**
 * @brief Sends a byte as a character to the LCD
 *
 * This macro is just a frontend to LCD_WRITE_BYTE( WRITE_CHAR_EN , BYTE )
 * that sets WRITE_CHAR_EN to 1 in order to enabel charackter mode.
 *
 * @param BYTE Byte that should be send to the Display.
 *
 * @see LCD_WRITE_NIBBLE( WRITE_CHAR_EN , NIBBLE )
 * @see LCD_CMD_NIBBLE( NIBBLE )
 *
 * @author Hannes
 */
#define LCD_CHAR_BYTE( BYTE ) LCD_WRITE_BYTE( 1 , BYTE )
