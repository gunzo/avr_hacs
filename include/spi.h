/*Header file for SPI interface master*/

/**
 * @file
 * @brief define output ports used for SPI output
 * 
 * Contains macros for SPI
 *
*/

/* 
 * @brief DD_MISO: Slave to Master on the Master In-Slave Out, MISO, line.
 *
 * Data is shifted from Master to Slave 
 *
 */
#define DD_MISO DDB6

/* 
 * @brief DD_MOSI: Master to Slave on the Master Out-Slave In, MOSI, line.
 *
 * Data is shifted from Slave to Master 
 *
 */
#define DD_MOSI DDB5  

/* 
 * @brief DD_SS: Slave select
 *
 */
#define DD_SS DDB4

/* 
 * @brief DD_SCK: Clock pulses
 *
 */
#define DD_SCK DDB7

/* 
 * @brief SCK: Data Direction Register
 * 
 * Setting up outputs and inputs for MISO, MOSI, SCK and SS
 */
#define DDR_SPI DDRB



extern void SPI_MasterInit(void);
extern void SPI_MasterTransmit(char cData);



