/*
 * SPI_interface.h
 *
 *  Created on: sep 6, 2021
 *      Author: Abdelrahman Kahled
 */


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_voidInit(void);

u8   SPI_u8SendDataByteSynch(u8 Copy_u8TransmittedByte);

u8   SPI_u8RecieveDataByteSynch(u8 * Copy_pu8RecievedByte);

u8   SPI_u8SendRecieveByteSynch(u8 Copy_u8TransByte,u8 * Copy_pu8RecievedByte);

u8   SPI_u8SendRecieveBufferAsynch(u8 * Copy_pu8TransmittedBuffer , u8 * Copy_pu8RecievedBuffer , u8 Copy_u8BufferSize , void(*Copy_pfNotificationFunc)(void));

#endif /* SPI_INTERFACE_H_ */