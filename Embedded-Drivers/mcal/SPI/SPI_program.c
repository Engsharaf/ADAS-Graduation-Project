/*
 * SPI_program.c
 *
 *  Created on: sep 6, 2021
 *      Author: Abdelrahman Kahled
 */



#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"
#include "SPI_register.h"

/* Global Pointers */
static u8 * SPI_pu8TransmittedBuffer       = NULL;

static u8 * SPI_pu8RecievedBuffer          = NULL;

static u8   SPI_u8BufferSize ;

static u8   SPI_u8BufferIndex;

static u8   SPI_u8BusyFlag ;

static void (*SPI_pfNotificationFun)(void) = NULL;


void SPI_voidInit(void)
{
	/* Choose Master or Slave Mode */
#if SPI_u8_SELECT_MODE == SPI_u8_MASTER
	SET_BIT(SPCR,SPCR_MSTR);
	#if SPI_u8_CLK_RATE   ==  SPI_u8_CLK_OVER_4
		CLR_BIT(SPCR,SPCR_SPR1);
		CLR_BIT(SPCR,SPCR_SPR0);
	#elif SPI_u8_CLK_RATE   ==  SPI_u8_CLK_OVER_16
		CLR_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPCR,SPCR_SPR0);
	#elif SPI_u8_CLK_RATE   ==  SPI_u8_CLK_OVER_64
		CLR_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPCR,SPCR_SPR1);
	#elif SPI_u8_CLK_RATE   ==  SPI_u8_CLK_OVER_128
		SET_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPCR,SPCR_SPR0);
	#elif SPI_u8_CLK_RATE   ==  SPI_u8_HCLK_OVER_2
		CLR_BIT(SPCR,SPCR_SPR1);
		CLR_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPSR,SPSR_SPI2X);
	#elif SPI_u8_CLK_RATE   ==  SPI_u8_HCLK_OVER_8
		CLR_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPSR,SPSR_SPI2X);
	#elif SPI_u8_CLK_RATE   ==  SPI_u8_HCLK_OVER_32
		SET_BIT(SPCR,SPCR_SPR1);
		CLR_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPSR,SPSR_SPI2X);
	#elif SPI_u8_CLK_RATE   ==  SPI_u8_HCLK_OVER_2
		SET_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPSR,SPSR_SPI2X);
#endif

#elif SPI_u8_SELECT_MODE == SPI_u8_SLAVE
	CLR_BIT(SPCR,SPCR_MSTR);
#endif

	/* Choose The Data order */
#if   SPI_u8_DATA_ORDER == SPI_u8_MSB
	CLR_BIT(SPCR,SPCR_DORD);
#elif SPI_u8_DATA_ORDER == SPI_u8_LSB
	SET_BIT(SPCR,SPCR_DORD);
#endif

	/* Choose Clk Polarity */
#if   SPI_u8_CLK_POL    == SPI_u8_FALLING_EDGE
	SET_BIT(SPCR,SPCR_CPOL);
#elif SPI_u8_CLK_POL    == SPI_u8_RAISING_EDGE
	CLR_BIT(SPCR,SPCR_CPOL);
#endif

	/* Choose Clk Phase */
#if   SPI_u8_CLK_PHASE  == SPI_u8_SAMPLE
	CLR_BIT(SPCR,SPCR_CPHA);
#elif SPI_u8_CLK_PHASE  == SPI_u8_SETUP
	SET_BIT(SPCR,SPCR_CPHA);
#endif
	/* SPI Enable */
	SET_BIT(SPCR,SPCR_SPE);
}

u8   SPI_u8SendDataByteSynch(u8 Copy_u8TransmittedByte)
{
	u8  Local_u8ReturnState       = STD_TYPES_u8_ERROR_OK;
	u16 Local_u16TimeOutCounter   = 0;

	SPDR = Copy_u8TransmittedByte;
	/* Check Collision flag */
	if( GET_BIT(SPSR,SPSR_WCOL) == 1)
	{
		Local_u8ReturnState = STD_TYPES_u8_ERROR_NOK;
	}

	/* wait until Transmission is completed */
	while( (GET_BIT(SPSR,SPSR_SPIF) == 0) && (Local_u16TimeOutCounter < SPI_u16_TIMEOUT) )
	{
		Local_u16TimeOutCounter++;
	}
	if (Local_u16TimeOutCounter >= SPI_u16_TIMEOUT)
	{
		Local_u8ReturnState = STD_TYPES_u8_ERROR_NOK;
	}

	return Local_u8ReturnState;
}

u8   SPI_u8RecieveDataByteSynch(u8 * Copy_pu8RecievedByte)
{
	u8  Local_u8ReturnState = STD_TYPES_u8_ERROR_OK;
	u16 Local_u16TimeOutCounter = 0;
	/* Check the Null Pointer */
	if(Copy_pu8RecievedByte == NULL)
	{
		Local_u8ReturnState = STD_TYPES_u8_ERROR_NOK;
	}
	else
	{
		/* wait until Transmission is completed */
		while( (GET_BIT(SPSR,SPSR_SPIF) == 0) && (Local_u16TimeOutCounter < SPI_u16_TIMEOUT) )
		{
			Local_u16TimeOutCounter++;
		}
		if(Local_u16TimeOutCounter >= SPI_u16_TIMEOUT)
		{
			Local_u8ReturnState = STD_TYPES_u8_ERROR_NOK;
		}
		else
		{
			*Copy_pu8RecievedByte = SPDR;
		}
	}

	return Local_u8ReturnState;
}

u8   SPI_u8SendRecieveByteSynch(u8 Copy_u8TransByte,u8 * Copy_pu8RecievedByte)
{
	u8  Local_u8ReturnState = STD_TYPES_u8_ERROR_OK;
	u16 Local_u16TimeOutCounter = 0;
	/* Check the Null Pointer */
	if(Copy_pu8RecievedByte == NULL)
	{
		Local_u8ReturnState = STD_TYPES_u8_ERROR_NOK;
	}
	else
	{
		/* Write Data into Data register */
		SPDR = Copy_u8TransByte;
		/* Check Collision flag */
		if( GET_BIT(SPSR,SPSR_WCOL) == 1)
		{
			Local_u8ReturnState = STD_TYPES_u8_ERROR_NOK;
		}
		/* wait until Transmission is completed */
		while( (GET_BIT(SPSR,SPSR_SPIF) == 0) && (Local_u16TimeOutCounter < SPI_u16_TIMEOUT) )
		{
			Local_u16TimeOutCounter++;
		}
		if(Local_u16TimeOutCounter >= SPI_u16_TIMEOUT)
		{
			Local_u8ReturnState = STD_TYPES_u8_ERROR_NOK;
		}
		else
		{
			*Copy_pu8RecievedByte = SPDR;
		}
	}

	return Local_u8ReturnState;
}

u8   SPI_u8SendRecieveBufferAsynch(u8 * Copy_pu8TransmittedBuffer , u8 * Copy_pu8RecievedBuffer , u8 Copy_u8BufferSize , void(*Copy_pfNotificationFunc)(void))
{
	u8 Local_u8ReturnedState = STD_TYPES_u8_ERROR_OK;
	/* Check Null Pointer */
	if( (Copy_pu8TransmittedBuffer == NULL) || (Copy_pu8RecievedBuffer == NULL) || (Copy_pfNotificationFunc == NULL) || (SPI_u8BusyFlag == 1) )
	{
		Local_u8ReturnedState = STD_TYPES_u8_ERROR_NOK;
	}
	else
	{
		/* Set Busy Flag */
		SPI_u8BusyFlag = 1;
		/* Init Global Pointers */
		SPI_pu8TransmittedBuffer = Copy_pu8TransmittedBuffer;

		SPI_pu8RecievedBuffer    = Copy_pu8RecievedBuffer;

		SPI_u8BufferSize         = Copy_u8BufferSize;

		SPI_pfNotificationFun    = Copy_pfNotificationFunc;

		/* Send The First Byte */
		SPDR = SPI_pu8TransmittedBuffer[SPI_u8BufferIndex];

		/* Enable SPI Interrupt */
		SET_BIT(SPCR,SPCR_SPIE);
	}
	return Local_u8ReturnedState;
}


void __vector_12(void)
{
	/* Read Data byte */
	SPI_pu8RecievedBuffer[SPI_u8BufferIndex] = SPDR ;

	/* Increment Buffer index */
	SPI_u8BufferIndex++;
	/* Check That Buffer index = Buffer size or not */
	if(SPI_u8BufferIndex == SPI_u8BufferSize)
	{
		/* Disable Interrupt */
		CLR_BIT(SPCR,SPCR_SPIE);

		/* Clear Buffer index */
		SPI_u8BufferIndex = 0;

		/* Call notification function */
		SPI_pfNotificationFun();

		/* Clear busy flag */
		SPI_u8BusyFlag = 0;
	}
	else
	{
		/* Send The Next Byte */
		SPDR = SPI_pu8TransmittedBuffer[SPI_u8BufferIndex];
	}

}

/*ISR(12)
{

}*/