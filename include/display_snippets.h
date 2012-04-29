/** @file 
 * @brief Basic elements to create LCD macros and funktions.
 *
 * This file contains short macros that are used in the display.h file. The
 * aim of this additional header is to contain macros that are on a low
 * abstraction level. These macros are created to reduce code duplication in the
 * display.h header file, by giving code snippeds that are prone to be used 
 * repetively a sencefull name. 
 *
 * Therefore, the macros in this file are optimised to create efficent code and
 * not to be easily usable.
 *
 * @note The macros in this file should \b not be used to communicate with the
 * display. Instead, use the macros/funktions form display.h.
 *
 * @author Hannes
 */

/**
 * @brief Sets the pins on ::LCD_PORT as output.
 *
 * @author Hannes
 */
#define LCD_PORT_SETUP (LCD_DDR |= (\
				    _BV( LCD_RS )\
				   |_BV( LCD_EN )\
				   |_BV( LCD_D4 )\
				   |_BV( LCD_D5 )\
				   |_BV( LCD_D6 )\
				   |_BV( LCD_D7 )\
				   )\
			)

/**
 * @brief LCD will understand data as new charachter.
 *
 * @pre Pin LCD_RS needs to be setup as output. ::LCD_PORT_SETUP can be used to
 * do so.
 *
 * @author Hannes
 */
#define LCD_CHAR_MODE ( LCD_PORT |= _BV( LCD_RS ) )

/**
 * @brief LCD will understand data as new command.
 *
 * @pre Pin LCD_RS needs to be setup as output. ::LCD_PORT_SETUP can be used to
 * do so.
 *
 * @author Hannes
 */
#define LCD_CMD_MODE ( LCD_PORT &= ~_BV( LCD_RS ) )

/**
 * @brief Sets up low nibble LCD data bits for the LCD.
 *
 * This should be set as early as possible before Enable ( LCD_EN ) goes high.
 *
 * @pre Pins LCD_D4 to LCD_D7 need to be setup as output. ::LCD_PORT_SETUP can
 * be used to do so.
 *
 * @author Hannes
 */
#define LCD_DATA_SETUP_LOW_NIBBLE( BYTE ) do{\
	/* If BYTE bit  X  is set,     set also  LCD_DX          oterhwise clear bit  LCD_DX  .*/\
	if( BYTE & _BV( 0 ) ) { LCD_PORT |= _BV( LCD_D4 ); } else { LCD_PORT &= ~_BV( LCD_D4 ); }\
	if( BYTE & _BV( 1 ) ) { LCD_PORT |= _BV( LCD_D5 ); } else { LCD_PORT &= ~_BV( LCD_D5 ); }\
	if( BYTE & _BV( 2 ) ) { LCD_PORT |= _BV( LCD_D6 ); } else { LCD_PORT &= ~_BV( LCD_D6 ); }\
	if( BYTE & _BV( 3 ) ) { LCD_PORT |= _BV( LCD_D7 ); } else { LCD_PORT &= ~_BV( LCD_D7 ); }\
}while(0)

/**
 * @brief Sets up high nibble LCD data bits for the LCD.
 *
 * This should be set as early as possible before Enable ( LCD_EN ) goes high.
 *
 * @author Hannes
 */
#define LCD_DATA_SETUP_HIGH_NIBBLE( BYTE ) do{\
	/* If BYTE bit  X  is set,     set also  LCD_DX          oterhwise clear bit  LCD_DX  .*/\
	if( BYTE & _BV( 4 ) ) { LCD_PORT |= _BV( LCD_D4 ); } else { LCD_PORT &= ~_BV( LCD_D4 ); }\
	if( BYTE & _BV( 5 ) ) { LCD_PORT |= _BV( LCD_D5 ); } else { LCD_PORT &= ~_BV( LCD_D5 ); }\
	if( BYTE & _BV( 6 ) ) { LCD_PORT |= _BV( LCD_D6 ); } else { LCD_PORT &= ~_BV( LCD_D6 ); }\
	if( BYTE & _BV( 7 ) ) { LCD_PORT |= _BV( LCD_D7 ); } else { LCD_PORT &= ~_BV( LCD_D7 ); }\
}while(0)

/**
 * @brief Sets the timer used for timing the wait cycles up.
 *
 * @see LCD_WAIT_TIMER_START
 *
 * @author Hannes
 */
#define LCD_WAIT_SETUP do{\
	/* Stopping and reseting timer 1. */\
	T1_STOP;\
	T1_RESET;\
	/* Clearing the EXTRA compare match flag. */\
	T1_COMP_MATCH_EXTRA_CLEAR;\
	/* Clearing the TOP compare match flag. */\
	T1_COMP_MATCH_TOP_CLEAR;\
	/* Setting up Timer 1 in Clear Timer on Compare mode. */\
	T1_CTC( LCD_TOP_DIV , LCD_EXTRA_DIV );\
}while(0)

/**
 * @brief Starts the timer used for timing the wait cycles.
 *
 * @pre ::LCD_WAIT_SETUP should be run to setup the wait timer.
 * @post Very soon after starting the wait timer, you should run 
 *       LCD_WAIT_CLK_HIGH to make sure LCD_EN will be high long enough for the
 *       display to work.
 *
 * @see LCD_WAIT_SETUP
 * @see LCD_WAIT_TIMER_STOP
 *
 * @author Hannes
 */
#define LCD_WAIT_TIMER_START T1_START( LCD_CLOCKDIVISION ) 

/**
 * @brief Stops the timer used for timing the wait cycles.
 *
 * @see LCD_WAIT_TIMER_START
 *
 * @author Hannes
 */
#define LCD_WAIT_TIMER_STOP T1_STOP

/**
 * @brief Clears the timer used for timing the wait cycles.
 *
 * @see LCD_WAIT_TIMER_START
 * 
 * @author Hannes
 */
#define LCD_WAIT_TIMER_RESET T1_RESET

/**
 * @brief Sets LCD_EN high and waits for the EXTRA flag.
 *
 * If used, the ::LCD_WAIT_SETUP will setup a EXTRA and TOP compare register.
 * This macro sets LCD_EN and waits until the EXTRA flag goes high. Then the
 * EXTRA compare flag will be cleared and the macro is finished. LCD_EN is not
 * cleared by this macro.
 *
 * @pre It is very advisable to run ::LCD_WAIT_TIMER_START
 * @post It is advisable to run ::LCD_WAIT_CLK_LOW
 *
 * @see LCD_WAIT_TIMER_START
 * @see LCD_WAIT_CLK_LOW
 *
 * @author Hannes
 */
#define LCD_WAIT_CLK_HIGH do{\
	/* HIGH phase. */\
	LCD_PORT |= _BV( LCD_EN ); /* EN HIGH */\
	/* Waiting for the EXTRA compare match. */\
	while( !T1_COMP_MATCH_EXTRA );\
	/* Clearing the compare match EXTRA flag. */\
	T1_COMP_MATCH_EXTRA_CLEAR;\
}while(0)

/**
 * @brief Sets LCD_EN low and waits for the TOP flag.
 *
 * If used, the ::LCD_WAIT_CLK_HIGH will set the LCD_EN bit.
 * This macro clears LCD_EN and waits until the TOP flag goes high. Then the
 * TOP compare flag will be cleared and the macro is finished.
 *
 * @pre It is advisable to run ::LCD_WAIT_CLK_HIGH
 *
 * @see LCD_WAIT_CLK_HIGH
 * @see LCD_WAIT_TIMER_STOP
 *
 * @author Hannes
 */
#define LCD_WAIT_CLK_LOW do{\
	/* LOW phase. */\
	LCD_PORT &= ~_BV( LCD_EN ); /* EN LOW */\
	/* Waiting for the TOP compare match. */\
	while( !T1_COMP_MATCH_TOP );\
	/* Clearing the compare match TOP flag. */\
	T1_COMP_MATCH_TOP_CLEAR;\
}while(0)
