/*****************************************************************************/
/* Title                 :   DIO_program.c                                   */
/* Filename              :   DIO_program.c                                   */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Oct 2, 2021                                     */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw GCC                                       */
/* Target                :   ATmega16 , ATmega32                             */
/* Notes                 :   None                                            */
/*                                                                           */
/*****************************************************************************/

/****************************************************************************/
/******************************  INCLUDES  **********************************/

#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\STD_TYPES.h"
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\errorStates.h"

#include"DIO_private.h"


/****************************************************************************/
/* Function Name   : DIO_enuSetPortDirection.                               */
/* Description     : This function used for Setting port direction.         */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                                                          */
/*                 : Arg.2: Copy_u8Dir:                                     */
/*                                        DIO_INPTU_PIN  ,   DIO_OUTPUT_PIN */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuSetPortDirection(u8 Copy_u8PortID, u8 Copy_u8Dir)
{
	ES_t Local_enuerrorState = ES_NOK ;

	if( (Copy_u8PortID <= DIO_PORTD )&& (Copy_u8Dir <= OUTPUT_PORT)  )
	{
		switch( Copy_u8PortID )
		{
		case DIO_PORTA :
			DDRA = Copy_u8Dir;
			break;

		case DIO_PORTB :
			DDRB = Copy_u8Dir;
			break;
		case DIO_PORTC :
			DDRC = Copy_u8Dir;
			break;
		case DIO_PORTD :
			DDRD = Copy_u8Dir;
			break;
		}
		Local_enuerrorState = ES_OK;

	}
	else
	{
		Local_enuerrorState = ES_OUT_OF_RANGE;

	}


	return Local_enuerrorState  ;

}//End of DIO_enuSetPortDirection().



/****************************************************************************/
/* Function Name   : DIO_enuSetPortValue.                                   */
/* Description     : This function used for Setting port value.             */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                                                          */
/*                 : Arg.2: Copy_u8Val:                                     */
/*                                        DIO_INPTU_PIN  ,  DIO_OUTPUT_PIN  */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuSetPortValue(u8 Copy_u8PortID, u8 Copy_u8Val)
{
	ES_t Local_enuerrorState = ES_NOK ;

	if( Copy_u8PortID <= DIO_PORTD )
	{
		switch( Copy_u8PortID )
		{
		case DIO_PORTA :
			PORTA = Copy_u8Val;
			break;

		case DIO_PORTB :
			PORTB = Copy_u8Val;
			break;

		case DIO_PORTC :
			PORTC = Copy_u8Val;
			break;

		case DIO_PORTD :
			PORTD = Copy_u8Val;
			break;
		}

		Local_enuerrorState = ES_OK;

	}
	else
	{
		Local_enuerrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuerrorState  ;
}//End of DIO_enuSetPortValue().


/****************************************************************************/
/* Function Name   : IO_enuToggelPort.                                      */
/* Description     : This function used for toggling the entire port.       */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuToggelPort(u8  Copy_u8PortID )
{
	ES_t Local_enuerrorState = ES_NOK ;

	if( Copy_u8PortID <= DIO_PORTD )
	{
		switch( Copy_u8PortID )
		{
		case DIO_PORTA :
			PORTA = ~PORTA;
			break;

		case DIO_PORTB :
			PORTB = ~PORTB;
			break;

		case DIO_PORTC :
			PORTC = ~PORTC;
			break;

		case DIO_PORTD :
			PORTD = ~PORTD ;
			break;
		}

		Local_enuerrorState = ES_OK;

	}
	else
	{
		Local_enuerrorState = ES_OUT_OF_RANGE;
	}


	return Local_enuerrorState  ;
}//End of DIO_enuToggelPort().


/****************************************************************************/
/* Function Name   : DIO_enuGetPortVlaue.                                   */
/* Description     : This function reads a specific port and put the value  */
/*                   in a variable through pointer to unsigned char.        */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                                                          */
/*                 : Arg.2: Address of u8 variable.                         */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuGetPortVlaue(u8 Copy_u8PortID, u8* Copy_pu8PortVal)
{
	//Local Variable to
	ES_t Local_enuerrorState = ES_NOK ;

	// Check to ensure that the passed address is not equal Null.
	if( Copy_pu8PortVal != NULL )
	{
		// Check to ensure that the passed PortID is in range.
		if( Copy_u8PortID <= DIO_PORTD )
		{

			/**********************************************************
			 * Switching for the suitable case .
			 **********************************************************/
			switch( Copy_u8PortID )
			{
			case DIO_PORTA :
				*Copy_pu8PortVal = PINA;
				break;

			case DIO_PORTB :
				*Copy_pu8PortVal = PINB;
				break;

			case DIO_PORTC :
				*Copy_pu8PortVal = PINC;
				break;

			case DIO_PORTD :
				*Copy_pu8PortVal = PIND ;
				break;
			}

			Local_enuerrorState = ES_OK;

		}
		else
		{
			/**********************************************************
			 * Handle Out Of Range case.
			 **********************************************************/
			Local_enuerrorState = ES_OUT_OF_RANGE;
		}
	}
	else
	{
		/**********************************************************
		 * Handle null pointer case.
		 **********************************************************/
		Local_enuerrorState = ES_NULL_POINTER;
	}

	return Local_enuerrorState  ;

}//End of DIO_enuGetPortVlaue().

/****************************************************************************/
/* Function Name   : DIO_enuSetPinDirection.                                */
/* Description     : This function is used for setting a certain pin in     */
/*                   a certain port.                                        */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                 : Arg.2: Copy_u8PinID:                                   */
/*                                        DIO_PIN0       ,   DIO_PIN4       */
/*                                        DIO_PIN1       ,   DIO_PIN5       */
/*                                        DIO_PIN2       ,   DIO_PIN6       */
/*                                        DIO_PIN3       ,   DIO_PIN7       */
/*                                                                          */
/*                 : Arg.3: Copy_u8Dir.                                     */
/*                                       DIO_INPTU_PIN   ,   DIO_OUTPUT_PIN */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuSetPinDirection(u8 Copy_u8PortID, u8 Copy_u8PinID , u8 Copy_u8Dir)
{
	ES_t Local_enuerrorState = ES_NOK ;

	if( (Copy_u8PortID <= DIO_PORTD) && (Copy_u8PinID <= DIO_PIN7) &&( Copy_u8Dir<= OUTPUT_PIN))
	{

		/**********************************************************
		 * Switching for the suitable case .
		 **********************************************************/
		switch( Copy_u8PortID )
		{
		case DIO_PORTA :
			if( Copy_u8Dir == INPTU_PIN)
			{
				DDRA &=~(DIO_MASK_BIT<<Copy_u8PinID);
			}
			else
			{
				DDRA |=(DIO_MASK_BIT<<Copy_u8PinID);
			}

			break;

		case DIO_PORTB :
			if( Copy_u8Dir == INPTU_PIN)
			{
				DDRB &=~(DIO_MASK_BIT<<Copy_u8PinID);
			}
			else
			{
				DDRB |=(DIO_MASK_BIT<<Copy_u8PinID);
			}
			break;

		case DIO_PORTC :

			if( Copy_u8Dir == INPTU_PIN)
			{
				DDRC &=~(DIO_MASK_BIT<<Copy_u8PinID);
			}
			else
			{
				DDRC |=(DIO_MASK_BIT<<Copy_u8PinID);
			}
			break;

		case DIO_PORTD :
			if( Copy_u8Dir == INPTU_PIN)
			{
				DDRD &=~(DIO_MASK_BIT<<Copy_u8PinID);
			}
			else
			{
				DDRD |=(DIO_MASK_BIT<<Copy_u8PinID);
			}
			break;

		}
		Local_enuerrorState = ES_OK;
	}
	else
	{
		Local_enuerrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuerrorState  ;

}//End of DIO_enuSetPinDirection().



/****************************************************************************/
/* Function Name   : DIO_enuSetPinValue.                                    */
/* Description     : This function used for Set a specific pin to high level*/
/*                   or low level.                                          */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                 : Arg.2: Copy_u8PinID:                                   */
/*                                        DIO_PIN0       ,   DIO_PIN4       */
/*                                        DIO_PIN1       ,   DIO_PIN5       */
/*                                        DIO_PIN2       ,   DIO_PIN6       */
/*                                        DIO_PIN3       ,   DIO_PIN7       */
/*                 : Arg.3: Copy_u8Val.                                     */
/*                                        DIO_LOW        ,   DIO_HIGH       */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuSetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID ,u8 Copy_u8Val)
{
	ES_t Local_enuerrorState = ES_NOK ;

	if( (Copy_u8PortID <= DIO_PORTD) && (Copy_u8PinID <= DIO_PIN7) &&( Copy_u8Val<=DIO_HIGH))
	{

		/**********************************************************
		 * Switching for the suitable case .
		 **********************************************************/
		switch( Copy_u8PortID )
		{
		case DIO_PORTA :
			if( Copy_u8Val == DIO_LOW)
			{
				PORTA &=~(DIO_MASK_BIT<<Copy_u8PinID);
			}
			else
			{
				PORTA |=(DIO_MASK_BIT<<Copy_u8PinID);
			}

			break;

		case DIO_PORTB :
			if( Copy_u8Val == DIO_LOW)
			{
				PORTB &=~(DIO_MASK_BIT<<Copy_u8PinID);
			}
			else
			{
				PORTB |=(DIO_MASK_BIT<<Copy_u8PinID);
			}

			break;

		case DIO_PORTC :

			if( Copy_u8Val == DIO_LOW)
			{
				PORTC &=~(DIO_MASK_BIT<<Copy_u8PinID);
			}
			else
			{
				PORTC |=(DIO_MASK_BIT<<Copy_u8PinID);
			}

			break;

		case DIO_PORTD :
			if( Copy_u8Val == DIO_LOW)
			{
				PORTD &=~(DIO_MASK_BIT<<Copy_u8PinID);
			}
			else
			{
				PORTD |=(DIO_MASK_BIT<<Copy_u8PinID);
			}

			break;

		}
		Local_enuerrorState = ES_OK;
	}
	else
	{
		Local_enuerrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuerrorState  ;
}//End of DIO_enuSetPinValue().

/****************************************************************************/
/* Function Name   : DIO_enuToggelPin.                                      */
/* Description     : This function inverse the value of the specific pin.   */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                                                          */
/*                 : Arg.2: Copy_u8PinID:                                   */
/*                                        DIO_PIN0       ,   DIO_PIN4       */
/*                                        DIO_PIN1       ,   DIO_PIN5       */
/*                                        DIO_PIN2       ,   DIO_PIN6       */
/*                                        DIO_PIN3       ,   DIO_PIN7       */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuToggelPin(u8  Copy_u8PortID, u8 Copy_u8PinID  )
{
	ES_t Local_enuerrorState = ES_NOK ;

	if( (Copy_u8PortID <= DIO_PORTD) &&  (Copy_u8PinID <= DIO_PIN7) )
	{
		/**********************************************************
		 * Switching for the suitable case .
		 **********************************************************/
		switch( Copy_u8PortID )
		{
		case DIO_PORTA :
			PORTA ^=(DIO_MASK_BIT<<Copy_u8PinID);
			break;

		case DIO_PORTB :
			PORTB ^=(DIO_MASK_BIT<<Copy_u8PinID);
			break;

		case DIO_PORTC :
			PORTC ^=(DIO_MASK_BIT<<Copy_u8PinID);
			break;

		case DIO_PORTD :
			PORTD ^=(DIO_MASK_BIT<<Copy_u8PinID);
			break;
		}

		Local_enuerrorState = ES_OK;

	}
	else
	{
		Local_enuerrorState = ES_OUT_OF_RANGE;
	}


	return Local_enuerrorState  ;
}//End of DIO_enuToggelPin().

/*********************************************************************************/
/* Function Name   : DIO_enuGetPinVlaue.                                         */
/* Description     : This function used for getting a specific pin value         */
/*                   and write this value in variable through pointer to u8.     */
/* Arguments       : Arg.1: Copy_u8PortID:                                       */
/*                                        DIO_PORTA      ,   DIO_PORTA           */
/*                                        DIO_PORTA      ,   DIO_PORTA           */
/*                 : Arg.2: Copy_u8PinID:                                        */
/*                                        DIO_PIN0       ,   DIO_PIN4            */
/*                                        DIO_PIN1       ,   DIO_PIN5            */
/*                                        DIO_PIN2       ,   DIO_PIN6            */
/*                                        DIO_PIN3       ,   DIO_PIN7            */
/*                                                                               */
/*                 : Arg.3: Address of u8 variable.                              */
/*                                                                               */
/* Return          : ERROR_STATE eum.                                            */
/*********************************************************************************/
ES_t DIO_enuGetPinVlaue(u8 Copy_u8PortID , u8 Copy_u8PinID , u8* Copy_pu8PinVal)
{
	ES_t Local_enuerrorState = ES_NOK ;

	// Check to ensure that the passed address is not equal Null.
	if( Copy_pu8PinVal != NULL )
	{
		if( (Copy_u8PortID <= DIO_PORTD) &&  (Copy_u8PinID <= DIO_PIN7) )
		{
			/**********************************************************
			 * Switching for the suitable case .
			 **********************************************************/
			switch( Copy_u8PortID )
			{
			case DIO_PORTA :
				*Copy_pu8PinVal = (PINA>>Copy_u8PinID)&DIO_MASK_BIT;
				break;

			case DIO_PORTB :
				*Copy_pu8PinVal = (PINB>>Copy_u8PinID)&DIO_MASK_BIT;
				break;

			case DIO_PORTC :
				*Copy_pu8PinVal = (PINC>>Copy_u8PinID)&DIO_MASK_BIT;
				break;

			case DIO_PORTD :
				*Copy_pu8PinVal = (PIND>>Copy_u8PinID)&DIO_MASK_BIT;
				break;
			}

			Local_enuerrorState = ES_OK;

		}
		else
		{
			Local_enuerrorState = ES_OUT_OF_RANGE;
		}
	}
	else
	{
		/**********************************************************
		 * Handle null pointer case.
		 **********************************************************/
		Local_enuerrorState = ES_NULL_POINTER;
	}



	return Local_enuerrorState  ;
}//End of DIO_enuGetPinVlaue().


/****************************** END OF FILE  *********************************/
/*****************************************************************************/
