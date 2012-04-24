


/**
 * @brief Set up external interrupt on a Falling edge
 *
 * Macro for setting up ext interrupt 1 on a falling edge.
 * Setting Interrupt 1 Sense Control 11 to a 1.
 * Making sure that Interrupt 1 Sense Control 10 is set to a 0.
 *
 * @author Mariya
 *
 * @see EXT_INT1_FALLING_EN
 *
 */
#define EXT_INT1_FALLING do{ 	\
								\
	MCUCR |= (1<<ISC11); /* Setting ISC11 (3rd bit) to 1 */		\
	MCUCR &= ~(1<<ISC10); /* Resetting ISC10 (2nd bit) to 0 */		\
								\
}while(0)


/**
 * @brief Enables external interrupt on a Falling edge
 *
 * Macro for enabling ext interrupt 1 on a falling edge.
 * In the Genral Interrupt Control Register: this enables Interrupt 1.
 *
 * @author Mariya
 *
 * @see EXT_INT1_FALLING
 *
 */
#define EXT_INT1_FALLING_EN  GICR |= ( 1<<INT1 ) /* Setting INT1 to 1 => enable */

