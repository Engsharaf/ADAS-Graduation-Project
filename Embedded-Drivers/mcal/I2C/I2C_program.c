/*
 * I2C_program.c
 *
 *  Created on: sep 6, 2021
 *      Author: Abdelrahman Kahled
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"
#include "I2C_reg.h"



void I2C_voidMasterInit(void)
{
	/* Set frequency 400 khz , prescalar value 0 */
	CLR_BIT(TWSR,TWSR_TWPS1);
	CLR_BIT(TWSR,TWSR_TWPS0);
	TWBR = 0x02;

	/* Enable ACK */
	SET_BIT(TWCR,TWCR_TWEA);

	/* Enable I2C */
	SET_BIT(TWCR,TWCR_TWEN);


}

void I2C_voidSlaveInit(u8 Copy_u8SlaveAdd)
{
	/* Set Slave Address In TWAR */
	TWAR = Copy_u8SlaveAdd<<1;


	/* Enable ACK */
	SET_BIT(TWCR,TWCR_TWEA);

	/* Enable I2C */
	SET_BIT(TWCR,TWCR_TWEN);


}

I2C_Error_States I2C_enuSendStartCondition(void)
{
	I2C_Error_States Local_enuState = I2C_Ok;

	/* Start Condition */
	SET_BIT(TWCR,TWCR_TWSTA);

	/* Clear Flag */
	SET_BIT(TWCR,TWCR_TWINT);


	/* Polling On The Flag */
	while(!GET_BIT(TWCR,TWCR_TWINT));

	/* Check Status code */
	if((TWSR & I2C_STATUS_CODE_MASK) != I2C_MT_SC_ACK)
	{
		Local_enuState = I2C_SC_Error;
	}
	else
	{

	}
	return Local_enuState;
}

I2C_Error_States I2C_enuSendReStartCondition(void)
{
	I2C_Error_States Local_enuState = I2C_Ok;
	/* Start Condition */
	SET_BIT(TWCR,TWCR_TWSTA);

	/* Clear Flag */
	SET_BIT(TWCR,TWCR_TWINT);


	/* Polling On The Flag */
	while(!GET_BIT(TWCR,TWCR_TWINT));

	/* Check Status code */
	if((TWSR & I2C_STATUS_CODE_MASK) != I2C_MT_RSC_ACK)
	{
		Local_enuState = I2C_RSC_Error;
	}
	else
	{

	}
	return Local_enuState;
}

I2C_Error_States I2C_enuSendSlaveAddWithWrite(u8 Copy_u8SlaveAdd)
{
	I2C_Error_States Local_enuState = I2C_Ok;
	/* Write Slave Address */
	TWDR = Copy_u8SlaveAdd<<1;
	/* Write W Bit */
	CLR_BIT(TWDR,0);

	/* Clear Start Condition  */
	CLR_BIT(TWCR,TWCR_TWSTA);

	/* Clear Flag */
	SET_BIT(TWCR,TWCR_TWINT);

	/* Polling On the Flag */
	while(!GET_BIT(TWCR,TWCR_TWINT));

	/* Check Status code */
	if((TWSR & I2C_STATUS_CODE_MASK) != I2C_MT_SLA_W_ACK)
	{
		Local_enuState = I2C_SLA_W_Error;
	}
	else
	{

	}
	return Local_enuState;

}

I2C_Error_States I2C_enuSendSlaveAddWithRead(u8 Copy_u8SlaveAdd)
{
	I2C_Error_States Local_enuState = I2C_Ok;
	/* Write Slave Address */
	TWDR = Copy_u8SlaveAdd<<1;
	/* Write W Bit */
	SET_BIT(TWDR,0);

	/* Clear Start Condition  */
	CLR_BIT(TWCR,TWCR_TWSTA);

	/* Clear Flag */
	SET_BIT(TWCR,TWCR_TWINT);

	/* Polling On the Flag */
	while(!GET_BIT(TWCR,TWCR_TWINT));

	/* Check Status code */
	if((TWSR & I2C_STATUS_CODE_MASK) != I2C_MR_SLA_R_ACK)
	{
		Local_enuState = I2C_SLA_R_Error;
	}
	else
	{

	}
	return Local_enuState;

}

I2C_Error_States I2C_enuMasterSendDataByte(u8 Copy_u8Data)
{
	I2C_Error_States Local_enuState = I2C_Ok;
	/* Write Data on The Data register */
	TWDR = Copy_u8Data;


	/* Clear Flag */
	SET_BIT(TWCR,TWCR_TWINT);

	/* Polling On the Flag */
	while(!GET_BIT(TWCR,TWCR_TWINT));

	/* Check Status code */
	if((TWSR & I2C_STATUS_CODE_MASK) != I2C_MT_DATA_ACK)
	{
		Local_enuState = I2C_DATA_Error;
	}
	else
	{

	}

	return Local_enuState;

}

I2C_Error_States I2C_enuMasterReadDataByte(u8 * Copy_pu8Data)
{
	I2C_Error_States Local_enuState = I2C_Ok;

	/* Clear flag */
	SET_BIT(TWCR,TWCR_TWINT);

	/* Polling on the Flag */
	while(!GET_BIT(TWCR,TWCR_TWINT));

	/* Checking whether ACK or NACK should be returned */
	if(GET_BIT(TWCR,TWCR_TWEA) == 1) /* indicates that ACK should be returned */
	{
		/* Check Status code which indicates that Data byte has been received and ACK has been returned */
		if((TWSR & I2C_STATUS_CODE_MASK) != I2C_MR_DATA_ACK)
		{
			Local_enuState = I2C_MR_DATA_Error;
		}
		else
		{
			*Copy_pu8Data = TWDR;
		}
	}
	else if(GET_BIT(TWCR,TWCR_TWEA) == 0) /* indicates that NACK should be returned */
	{
		/* Check Status code which indicates that Data byte has been received and NACK has been returned */
		if((TWSR & I2C_STATUS_CODE_MASK) != I2C_MR_DATA_NACK)
		{
			Local_enuState = I2C_MR_DATA_Error;
		}
		else
		{
			*Copy_pu8Data = TWDR;
		}

	}

	return Local_enuState;
}

void I2C_voidSetACK(void)
{
  //Set Acknowledge Bit
  SET_BIT(TWCR,TWCR_TWEA);
}

void I2C_voidSetNACK(void)
{
  //Clear Acknowledge Bit to Send NACK
  CLR_BIT(TWCR,TWCR_TWEA);
}

void I2C_voidSendStopCondition(void)
{
	//Stop Condition
	SET_BIT(TWCR,TWCR_TWSTO);

	//Clear Flag
	SET_BIT(TWCR,TWCR_TWINT);


}