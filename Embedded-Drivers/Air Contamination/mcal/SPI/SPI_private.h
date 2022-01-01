/*
 * SPI_private.h
 *
 *  Created on: sep 6, 2021
 *      Author: Abdelrahman Kahled
 */


#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

/* define regs spi */

#define SPCR      *((volatile u8 *)0x2D)
#define SPSR      *((volatile u8 *)0x2E)
#define SPDR      *((volatile u8 *)0x2F)

/* SPCR Bits */

#define SPCR_SPIE               7
#define SPCR_SPE                6
#define SPCR_DORD               5
#define SPCR_MSTR               4
#define SPCR_CPOL               3
#define SPCR_CPHA               2
#define SPCR_SPR1               1
#define SPCR_SPR0               0


/* SPSR bits */
#define SPSR_SPIF               7
#define SPSR_WCOL               6

#define SPSR_SPI2X              0



/* Macros For Config */

/* Macros for Selecting the mode Master or slave */
#define SPI_u8_MASTER           0
#define SPI_u8_SLAVE            1


/* Macros for the data order */
#define SPI_u8_MSB              0
#define SPI_u8_LSB              1


/* Macros for clk pol */
#define SPI_u8_RAISING_EDGE     0
#define SPI_u8_FALLING_EDGE     1

/* Macros For CLK Phase */
#define SPI_u8_SAMPLE           0
#define SPI_u8_SETUP            1



/* Macros for Clk Rate in Master Mode */
#define SPI_u8_CLK_OVER_4       0
#define SPI_u8_CLK_OVER_16      1
#define SPI_u8_CLK_OVER_64      2
#define SPI_u8_CLK_OVER_128     3
#define SPI_u8_HCLK_OVER_2      4
#define SPI_u8_HCLK_OVER_8      5
#define SPI_u8_HCLK_OVER_32     6
#define SPI_u8_HCLK_OVER_64     7


void __vector_12(void)   __attribute__((signal));



#define ISR(NO)        void __vector_##NO(void) __attribute__((signal)); \
							void __vector_##NO(void)


#endif /* SPI_PRIVATE_H_ */
