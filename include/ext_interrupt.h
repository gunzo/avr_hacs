/** @file
 * @brief External Interrupt Macros
 *
 * Including:
 * External Interrupt 1 / External Interrupt 0 <--- Enabled
 * External Interrupt 1 / 0 <--- Disabled
 * External Interrupt 1 / 0 <--- Set up on a Rising Edge
 * External Interrupt 1 / 0 <--- Set up on a Falling Edge
 *
 * @see EXT_INT0_EN
 * @see EXT_INT0_DIS
 * @see EXT_INT0_RISING
 * @see EXT_INT0_FALLING
 * @see EXT_INT1_EN
 * @see EXT_INT1_DIS
 * @see EXT_INT1_RISING
 * @see EXT_INT1_FALLING
 *
*/


/**
 * @brief Set up external interrupt 1 on a Rising edge
 *
 * Macro for setting up ext interrupt 1 on a rising edge.
 * Setting Interrupt 1 Sense Control 11 to a 1.
 * Setting Interrupt 1 Sense Control 10 to a 1.
 *
 * @author Mariya
 *
 * @see EXT_INT1_EN
 * @see EXT_INT1_DIS
 * @see EXT_INT1_FALLING
 *
 */
#define EXT_INT1_RISING do{ 	\
								\
	MCUCR |= (1<<ISC11); /* Setting ISC11 (3rd bit) to 1 */		\
	MCUCR |= (1<<ISC10); /* Setting ISC10 (2nd bit) to 1 */		\
								\
}while(0)


/**
 * @brief Set up external interrupt on a Falling edge
 *
 * Macro for setting up ext interrupt 1 on a falling edge.
 * Setting Interrupt 1 Sense Control 11 to a 1.
 * Making sure that Interrupt 1 Sense Control 10 is set to a 0.
 *
 * @author Mariya
 *
 * @see EXT_INT1_EN
 * @see EXT_INT1_DIS
 * @see EXT_INT1_RISING
 *
 */
#define EXT_INT1_FALLING do{ 	\
								\
	MCUCR |= (1<<ISC11); /* Setting ISC11 (3rd bit) to 1 */		\
	MCUCR &= ~(1<<ISC10); /* Resetting ISC10 (2nd bit) to 0 */		\
								\
}while(0)


/**
 * @brief Enables external interrupt 1
 *
 * Macro for enabling External Interrupt 1.
 * GICR (Genral Interrupt Control Register).
 *
 * @author Mariya
 *
 * @see EXT_INT1_DIS
 * @see EXT_INT1_RISING
 * @see EXT_INT1_FALLING
 *
 */
#define EXT_INT1_EN  GICR |= ( 1<<INT1 ) /* Setting INT1 to 1 => enable */


/**
 * @brief Disables external interrupt 1 
 *
 * Macro for disabling External Interrupt 1.
 *
 * @author Mariya
 *
 * @see EXT_INT1_EN
 * @see EXT_INT1_RISING
 * @see EXT_INT1_FALLING
 *
 */
 #define EXT_INT1_DIS GICR &= ~( 1<<INT1 ) /* Making sure INT1 is set to a 0 => disabled */






/**
 * @brief Set up external interrupt 0 on a Rising edge
 *
 * Macro for setting up ext interrupt 0 on a rising edge.
 * Setting Interrupt 0 Sense Control 11 to a 1.
 * Setting Interrupt 0 Sense Control 10 to a 1.
 *
 * @author Mariya
 *
 * @see EXT_INT0_EN
 * @see EXT_INT0_DIS
 * @see EXT_INT0_FALLING
 *
 */
#define EXT_INT0_RISING do{ 	\
								\
	MCUCR |= (1<<ISC01); /* Setting ISC11 (3rd bit) to 1 */		\
	MCUCR |= (1<<ISC00); /* Setting ISC10 (2nd bit) to 1 */		\
								\
}while(0)


/**
 * @brief Set up external interrupt on a Falling edge
 *
 * Macro for setting up ext interrupt 0 on a falling edge.
 * Setting Interrupt 0 Sense Control 11 to a 1.
 * Making sure that Interrupt 0 Sense Control 10 is set to a 0.
 *
 * @author Mariya
 *
 * @see EXT_INT0_EN
 * @see EXT_INT0_DIS
 * @see EXT_INT0_RISING
 *
 */
#define EXT_INT0_FALLING do{ 	\
								\
	MCUCR |= (1<<ISC01); /* Setting ISC11 (3rd bit) to 1 */		\
	MCUCR &= ~(1<<ISC00); /* Resetting ISC10 (2nd bit) to 0 */		\
								\
}while(0)


/**
 * @brief Enables external interrupt 0
 *
 * Macro for enabling External Interrupt 0.
 * GICR (Genral Interrupt Control Register).
 *
 * @author Mariya
 *
 * @see EXT_INT0_DIS
 * @see EXT_INT0_RISING
 * @see EXT_INT0_FALLING
 *
 */
#define EXT_INT0_EN  GICR |= ( 1<<INT1 ) /* Setting INT0 to 1 => enable */


/**
 * @brief Disables external interrupt 0
 *
 * Macro for disabling External Interrupt 0.
 *
 * @author Mariya
 *
 * @see EXT_INT0_EN
 * @see EXT_INT0_RISING
 * @see EXT_INT0_FALLING
 *
 */
 #define EXT_INT0_DIS GICR &= ~( 1<<INT1 ) /* Making sure INT0 is set to a 0 => disabled */



