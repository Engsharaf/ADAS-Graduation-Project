/*
 * SPI_config.h
 *
 *  Created on: sep 6, 2021
 *      Author: Abdelrahman Kahled
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/* Config for Master or slave mode */
/* Options = SPI_u8_MASTER
			 SPI_u8_SLAVE  */

#define SPI_u8_SELECT_MODE     SPI_u8_MASTER

/* Config for The Data order */
/* Options = SPI_u8_MSB
             SPI_u8_LSB */
#define SPI_u8_DATA_ORDER      SPI_u8_MSB

/* Config for CLK Polarity */
/* options = SPI_u8_RAISING_EDGE
		     SPI_u8_FALLING_EDGE  */

#define SPI_u8_CLK_POL        SPI_u8_RAISING_EDGE

/* Config for CLK Phase */
/* options = SPI_u8_SAMPLE
             SPI_u8_SETUP  */
#define SPI_u8_CLK_PHASE      SPI_u8_SETUP

/* config for CLK Rate */
/* Options = SPI_u8_CLK_OVER_4
             SPI_u8_CLK_OVER_16
             SPI_u8_CLK_OVER_64
             SPI_u8_CLK_OVER_128
             SPI_u8_HCLK_OVER_2
             SPI_u8_HCLK_OVER_8
             SPI_u8_HCLK_OVER_32
             SPI_u8_HCLK_OVER_64 */

#define SPI_u8_CLK_RATE      SPI_u8_CLK_OVER_16

/* config Macro for time out */

#define SPI_u16_TIMEOUT      50000

#endif /* SPI_CONFIG_H_ */