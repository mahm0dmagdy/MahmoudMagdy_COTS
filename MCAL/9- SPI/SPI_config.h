/*
 * SPI_config.h
 *
 * Created: 11/30/2023 5:59:46 PM
 *  Author: mahmo
 */ 


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_
/*@details Configure your node as master or slave --> Options: 1- MASTER
											   2- SLAVE
*/
#define SPI_NODE     MASTER


/*@details Configure CLK PRESCALER --> Options are: 1- DIVISION_BY_4  
								                    2- DIVISION_BY_16 
								                    3- DIVISION_BY_64 
								                    4- DIVISION_BY_128
								                    5- DIVISION_BY_2  
								                    6- DIVISION_BY_8  
								                    7- DIVISION_BY_32 
*/
#define SPI_PRESCALER  DIVISION_BY_128

/*@details Configure
*/

#endif /* SPI_CONFIG_H_ */