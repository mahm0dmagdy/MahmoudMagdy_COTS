/*
 * SPI_reg.h
 *
 * Created: 11/30/2023 6:02:28 PM
 *  Author: mahmo
 */ 


#ifndef SPI_REG_H_
#define SPI_REG_H_

/* SPI Control Register */
#define    SPCR    *((volatile uint8*)0x2D)

#define    SPCR_SPR0   0u   /*  SPR0: SPI Clock Rate Select */
#define    SPCR_SPR1   1u   /*  SPR1: SPI Clock Rate Select */
#define    SPCR_CPHA   2u   /* CPHA: Clock Phase */
#define    SPCR_CPOL   3u   /* CPOL: Clock Polarity */
#define    SPCR_MSTR   4u   /* MSTR: Master/Slave Select */
#define    SPCR_DORD   5u   /* DORD: Data Order */
#define    SPCR_SPE    6u   /* SPE: SPI Enable */
#define    SPCR_SPIE   7u   /* SPIE: SPI Interrupt Enable */


/* SPI Status Register */
#define    SPSR    *((volatile uint8*)0x2E)

#define   SPSR_SPI2X   0u  /* SPI2X: Double SPI Speed Bit */
#define   SPSR_WCOL    1u  /* WCOL: Write COLlision Flag */
#define   SPSR_SPIF    2u  /* SPIF: SPI Interrupt Flag */


/* SPI Data Register */
#define    SPDR    *((volatile uint8*)0x2F)

#endif /* SPI_REG_H_ */