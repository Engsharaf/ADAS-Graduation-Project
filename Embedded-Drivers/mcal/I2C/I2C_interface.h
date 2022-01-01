/*
 * I2C_interface.h
 *
 *  Created on: sep 6, 2021
 *      Author: Abdelrahman Kahled
 */


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_


typedef enum
{
	I2C_Ok,
	I2C_SC_Error,
	I2C_RSC_Error,
	I2C_SLA_W_Error,
	I2C_SLA_R_Error,
	I2C_DATA_Error,
	I2C_MR_DATA_Error

}I2C_Error_States;


void I2C_voidMasterInit(void);

void I2C_voidSlaveInit(u8 Copy_u8SlaveAdd);

I2C_Error_States I2C_enuSendStartCondition(void);

I2C_Error_States I2C_enuSendReStartCondition(void);

I2C_Error_States I2C_enuSendSlaveAddWithWrite(u8 Copy_u8SlaveAdd);

I2C_Error_States I2C_enuSendSlaveAddWithRead(u8 Copy_u8SlaveAdd);

I2C_Error_States I2C_enuMasterSendDataByte(u8 Copy_u8Data);

I2C_Error_States I2C_enuMasterReadDataByte(u8 * Copy_pu8Data);

void I2C_voidSetACK(void);

void I2C_voidSetNACK(void);

void I2C_voidSendStopCondition(void);




#endif /* I2C_INTERFACE_H_ */