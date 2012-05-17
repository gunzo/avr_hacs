/*Header file for SPI interface master*/

/*define output ports used for SPI output*/
#define DD_MISO DDB6
#define DD_MOSI DDB5  
#define DD_SS DDB4
#define DD_SCK DDB7
#define DDR_SPI DDRB



extern void SPI_MasterInit(void);
extern void SPI_MasterTransmit(char cData);



