#define F_CPU 10000000UL // 10 MHz
#include <util/delay.h>
#include <string.h>
#include <include/timers.h>

#define LCD_CLOCKDIVISION 8
#define LCD_EXTRA_DIV 30 //20 caused errors
#define LCD_TOP_DIV 60 //40 caused errors
#include <include/display.h>
#include <include/avrboard.h>

/**
 * @file
 *
 * @brief Test file for display.h
 *
 * This file is an attept to test the display.h header file. This is done by
 * calling the funktions that should be tested and manualy verifing the output
 * on the display. 
 *
 * @author Hannes
 */


void lcd_line_jumb_test()
{
	LCD_JUMP_LINE_START(4);
	_delay_ms(1);

	LCD_CHAR_NIBBLE( 'e'>>4 );
	LCD_CHAR_NIBBLE( 'e' );
	LCD_CHAR_BYTE( 'H' );

	LCD_JUMP_LINE_START(3);
	_delay_ms(1);

	LCD_CHAR_BYTE( 'o' );
	LCD_CHAR_BYTE( 'l' );
	LCD_CHAR_BYTE( 'l' );

	LCD_JUMP_LINE_START(2);
	_delay_ms(1);

	LCD_CHAR_BYTE( 'o' );
	LCD_CHAR_BYTE( 'W' );
	LCD_CHAR_BYTE( ' ' );

	LCD_JUMP_LINE_START(1);
	_delay_ms(1);

	LCD_CHAR_BYTE( 'd' );
	LCD_CHAR_BYTE( 'l' );
	LCD_CHAR_BYTE( 'r' );
}

int main(void)
{
	/* TEST 1 
	 *
	 * This is tested: LCD_INT
	 *
	 * None of the other tests will work if this fails. If it works, the display
	 * will be completly empty.
	 */
	LCD_INIT;

	_delay_ms(10000);

	/* TEST 2 
	 *
	 * This is tested: LCD_CHAR_BYTE( BYTE ), LCD_JUMP_LINE_START( LINE_NUMBER )
	 * LCD_CHAR_NIBBLE( NIBBLE ).
	 *
	 * Does some sophisticated line jumb test. The test jumps to line 4
	 * and writes "eH". Then jubms to line 3 and writes "oll". In line two "oW"
	 * is written and in line one "dlr". If read on the display form bottom
	 * to top and right to left, "Hello World" should be read.*/
	lcd_line_jumb_test();

	_delay_ms(10000);

	/* TEST 3
	 *
	 * This is tested: lcd_write (char *display_text) and if it only writes 80 
	 * characters.
	 *
	 * The display fits 80 characters. This test writes 8 times the numbers form
	 * 0 to 9. Appended to that is two times the Text: "This_should_not_apear".
	 * This last text should not appear if the method is working as intended.
	 * Otherwise this additionally test will overwrite the numbers in the beginning
	 * of the display.
	 */
	LCD_JUMP_LINE_START(1);
	lcd_write( "01234567890123456789012345678901234567890123456789012345678901234567890123456789This_should_not_apear!This_should_not_apear!" );

	_delay_ms(10000);

	/* TEST 4 
	 * 
	 * This is tested: lcd_write_line(char *line_text) and if it will clear
	 * the rest of the line, in case the provided string does not do so.
	 *
	 * This writes the string "Cleared:" into the first line. There should be no
	 * numbers after the semicolon if the test is working.
	 */
	LCD_JUMP_LINE_START(1);
	lcd_write_line( "Cleared:" );

	_delay_ms(10000);

	/* TEST 5 
	 *
	 * This is tested: lcd_write_line(char *line_text) and if it will stop
	 * writing characters if the provided string is longer than a line.
	 *
	 * The String "This line is so long, it does not even fit in..." is written
	 * to the third line. Only "This line is so long" should be seen. The
	 * rest should not overwrite any any other lines.
	 */
	LCD_JUMP_LINE_START(3);
	lcd_write_line( "This line is so long, it does not even fit in..." );

	_delay_ms(10000);

	/* TEST 6 
	 *
	 * This is tested: LCD_CLEAR, simply clears the lcd.
	 *
	 * Testing if clearing the display works. 
	 */
	LCD_CLEAR;

	_delay_ms(10000);

	/* Filling the screen again. */
	LCD_JUMP_LINE_START(1);
	lcd_write( "01234567890123456789012345678901234567890123456789012345678901234567890123456789This_should_not_apear!This_should_not_apear!" );

	_delay_ms(10000);

	/* TEST 7
	 *
	 * This is tested: LCD_CLEAR_LINE
	 *
	 * We attempt to clear the second line by jumping to it and then calling
	 * LCD_CLEAR_LINE.
	 */
	LCD_JUMP_LINE_START(2);
	LCD_CLEAR_LINE;

	while(1) {}
}
