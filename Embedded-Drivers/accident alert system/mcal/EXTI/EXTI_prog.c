/*****************************************************************************/
/*****************************************************************************/
/* Title                 :   EXTI_prog                                       */
/* Filename              :   EXTI_prog.c                                     */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Oct 8, 2021                                     */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw GCC                                       */
/* Target                :   ATmega16 , ATmega32                             */
/* Notes                 :   None                                            */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/******************************  INCLUDES  ***********************************/
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\STD_TYPES.h"
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\errorStates.h"

#include "E:\NTI\AVR\ATmeg16_Drivers\MCAL\interrupt.h"

#include "EXTI_priv.h"
#include "EXTI_Cnfg.h"


/**********************************************************************************/
/* Description     : Tow global arrays of pointers to hold the Addresses of       */
/*                   the functions and its arguments to use them in the           */
/*                   CallBack.                                                    */
/***********************************************************************************/
static volatile void (*EXTI_ApfunINTFunc[3])(void*)= { NULL , NULL , NULL } ;

static volatile void* EXTI_ApvidGenericParameter[3]= { NULL , NULL , NULL };



/****************************************************************************/
/****************************************************************************/
/* Function Name   : EXTI_enuInit.                                          */
/* Description     : Utility function to initialize the Enabled interrupts. */
/* Argument        : Address array of interrupts .                          */
/* Return          : Error state of type ES_t.                              */
/**............................................******************************/
ES_t   EXTI_enuInit( EXTI_t*  Cpy_pstrEXTICnfg )
{
	ES_t Local_enuErrorState = ES_NOK ;


	if( Cpy_pstrEXTICnfg != NULL )
	{
		u8 Local_u8Iterator = 0;

		for( Local_u8Iterator = 0 ; Local_u8Iterator < EXTI_NUM ; Local_u8Iterator++ )
		{

			if( Cpy_pstrEXTICnfg[Local_u8Iterator].EXTI_u8State == EXTI_ACTIVE )
			{
				// Enable the appropriate interrupt in each iteration.
				switch(Local_u8Iterator)
				{

				/*********************************************************
				 * Configure the interrupt0 and Handling it's cases.     *
				 *********************************************************/
				case EXTI0 :
					MCUCR  &= ~( (EXTI_MASK_BIT<<ISC00) | (EXTI_MASK_BIT<<ISC01) );

					switch(Cpy_pstrEXTICnfg[Local_u8Iterator].EXTI_u8SenceLevel)
					{
					case EXTI_RISING_EDGE :
						MCUCR   |= (EXTI_MASK_BIT<<ISC00 )|(EXTI_MASK_BIT<<ISC01 );
						break;

					case EXTI_FALLING_EDGE :
						MCUCR   |=  (EXTI_MASK_BIT<<ISC01 );
						break;

					case  EXTI_LOGIC_CHANGE:
						MCUCR   |=  (EXTI_MASK_BIT<<ISC00 );
						break;

					case EXTI_LOW_LEVEL :
						break;

					default:
						Local_enuErrorState = ES_OUT_OF_RANGE ;


					}

					//Enable the ENT0.
					GICR |=(EXTI_MASK_BIT<<INT0);
					break;

					/*********************************************************
					 * Configure the interrupt1 and Handling it's cases.     *
					 *********************************************************/
					case EXTI1 :
						MCUCR  &= ~( (EXTI_MASK_BIT<<ISC10) | (EXTI_MASK_BIT<<ISC11) );

						switch(Cpy_pstrEXTICnfg[Local_u8Iterator].EXTI_u8SenceLevel)
						{
						case EXTI_RISING_EDGE :
							MCUCR   |= (EXTI_MASK_BIT<<ISC10 )|(EXTI_MASK_BIT<<ISC11 );
							break;

						case EXTI_FALLING_EDGE :
							MCUCR   |=  (EXTI_MASK_BIT<<ISC11 );
							break;

						case  EXTI_LOGIC_CHANGE:
							MCUCR   |=  (EXTI_MASK_BIT<<ISC10 );
							break;

						case EXTI_LOW_LEVEL :
							break;

						default:
							Local_enuErrorState = ES_OUT_OF_RANGE ;
						}

						//Enable the ENT1.
						GICR |=(EXTI_MASK_BIT<<INT1);
						break;

						/*********************************************************
						 * Configure the interrupt2 and Handling it's cases.     *
						 *********************************************************/
						case EXTI2 :
							MCUCSR  &= ~(EXTI_MASK_BIT<<ISC2) ;

							switch(Cpy_pstrEXTICnfg[Local_u8Iterator].EXTI_u8SenceLevel)
							{
							case EXTI_RISING_EDGE :
								MCUCSR   |= (EXTI_MASK_BIT<<ISC2 );
								break;

							case EXTI_FALLING_EDGE :
								break;

							default:
								Local_enuErrorState = ES_OUT_OF_RANGE ;
							}

							//Enable the ENT2.
							GICR |=(EXTI_MASK_BIT<<INT2);
							break;



							default:
								Local_enuErrorState = ES_OUT_OF_RANGE ;

				}//End of outer Switch case.

				Local_enuErrorState = ES_NOK ;
			}
			else if( Cpy_pstrEXTICnfg[Local_u8Iterator].EXTI_u8State ==EXTI_DEACTIVE )
			{
				//Do nothing.
			}
			else
			{
				//Please Do Nothing.
			}

		}

	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER ;
	}


	return Local_enuErrorState;
}//End of EXTI_enuInit.




/****************************************************************************/
/****************************************************************************/
/*Function Name   : EXTI_enuSetSenceMode.                                   */
/*Description     : Utility function to Set the State of a certain interrupt*/
/*                  during run time .                                       */
/*Argument        : Arg_1:  Interrupt ID that you want to change it state.  */
/*                  =====                                                   */
/*                                                                          */
/*                          Range:                                          */
/*                                 EXTI_0 --->for interrupt_0               */
/*                                 EXTI_1 --->for interrupt_1               */
/*                                 EXTI_2 --->for interrupt_2               */
/*                                                                          */
/*                : Arg_2:  Interrupt Sense level .                         */
/*                  =====                                                   */
/*                          Range:                                          */
/*                                  ->For interrupt 0 & 1                   */
/*                                   RISING_EDGE                            */
/*                                   FALLING_EDGE                           */
/*                                   LOGIC_CHANGE                           */
/*                                   LOW_LEVEL                              */
/*                                                                          */
/*                                 ->For interrupt 2                        */
/*                                  RISING_EDGE                             */
/*                                  FALLING_EDGE                            */
/*                                                                          */
/* Return          : Error state of type ES_t.                              */
/*..........................*************************************************/
ES_t   EXTI_enuSetSenceMode( u8 Cpy_u8EXTI_ID  , u8 Cpy_u8SenceLevel )
{
	ES_t Local_enuErrorState = ES_NOK ;

	if(Cpy_u8EXTI_ID <= EXTI_NUM )
	{

		switch( Cpy_u8EXTI_ID )
		{
		/*****************************************************************
		 * Interrupt0  Sense Control Cases Handling.                     *
		 *****************************************************************/
		case EXTI0:
			MCUCR  &= ~( (EXTI_MASK_BIT<<ISC00) | (EXTI_MASK_BIT<<ISC01) );

			switch(Cpy_u8SenceLevel)
			{
			case EXTI_RISING_EDGE :
				MCUCR   |= (EXTI_MASK_BIT<<ISC00 )|(EXTI_MASK_BIT<<ISC01 );
				break;

			case EXTI_FALLING_EDGE :
				MCUCR   |=  (EXTI_MASK_BIT<<ISC01 );
				break;

			case  EXTI_LOGIC_CHANGE:
				MCUCR   |=  (EXTI_MASK_BIT<<ISC00 );
				break;

			case EXTI_LOW_LEVEL :
				break;

			default:
				Local_enuErrorState = ES_OUT_OF_RANGE ;

			}

			break ;



			/*****************************************************************
			 * Interrupt1  Sense Control Cases Handling.                     *
			 *****************************************************************/
			case EXTI1:
				MCUCR  &= ~( (EXTI_MASK_BIT<<ISC10) | (EXTI_MASK_BIT<<ISC11) );
				switch(Cpy_u8SenceLevel)
				{
				case EXTI_RISING_EDGE :
					MCUCR   |= (EXTI_MASK_BIT<<ISC10 )|(EXTI_MASK_BIT<<ISC11 );
					break;

				case EXTI_FALLING_EDGE :
					MCUCR   |=  (EXTI_MASK_BIT<<ISC11 );
					break;

				case  EXTI_LOGIC_CHANGE:
					MCUCR   |=  (EXTI_MASK_BIT<<ISC10 );
					break;

				case EXTI_LOW_LEVEL :
					break;

				default:
					Local_enuErrorState = ES_OUT_OF_RANGE ;

				}

				break ;

				/*****************************************************************
				 * Interrupt2  Sense Control Cases Handling.                     *
				 *****************************************************************/
				case EXTI2:

					switch(Cpy_u8SenceLevel)
					{
					case EXTI_RISING_EDGE :
						MCUCSR  |=(EXTI_MASK_BIT<<ISC2) ;
						break;

					case EXTI_FALLING_EDGE :
						MCUCSR  &=~(EXTI_MASK_BIT<<ISC2) ;
						break;

					default:
						Local_enuErrorState = ES_OUT_OF_RANGE ;

					}

					break ;


		}

		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;

}//End of EXTI_enuSetSenceMode.




/*****************************************************************************/
/*****************************************************************************/
/*Function Name   : EXTI_enuEnableINT.                                       */
/*Description     : Utility function to Enable a certain interrupt           */
/*                  during run time .                                        */
/*Argument        : Arg_1:  Interrupt ID that you want to Enable.            */
/*                  =====                                                    */
/*                                                                           */
/*                          Range:                                           */
/*                                 EXTI_0 --->for interrupt_0                */
/*                                 EXTI_1 --->for interrupt_1                */
/*                                 EXTI_2 --->for interrupt_2                */
/*                                                                           */
/* Return          : Error state of type ES_t.                               */
/*.......................*****************************************************/
ES_t   EXTI_enuEnableINT( u8 Cpy_u8EXTI_ID  )
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( Cpy_u8EXTI_ID < EXTI_NUM)
	{
		switch(Cpy_u8EXTI_ID)
		{

		case EXTI0:
			//Enable interrupt 0 .
			GICR |= (EXTI_MASK_BIT<< INT0);
			break;

		case EXTI1:
			//Enable interrupt 1 .
			GICR |= (EXTI_MASK_BIT<< INT1);
			break;

		case EXTI2:
			//Enable interrupt 2 .
			GICR |= (EXTI_MASK_BIT<< INT2);
			break;

		}
		Local_enuErrorState = ES_OK  ;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE ;
	}

	return Local_enuErrorState;
}//End of EXTI_enuEnableINT.




/*****************************************************************************/
/*****************************************************************************/
/*Function Name   : EXTI_enuDisableINT.                                      */
/*Description     : Utility function to Disable a certain interrupt          */
/*                  during run time .                                        */
/*Argument        : Arg_1:  Interrupt ID that you want to Disable.           */
/*                  =====                                                    */
/*                                                                           */
/*                          Range:                                           */
/*                                 EXTI_0 --->for interrupt_0                */
/*                                 EXTI_1 --->for interrupt_1                */
/*                                 EXTI_2 --->for interrupt_2                */
/*                                                                           */
/* Return          : Error state of type ES_t.                               */
/*.......................*****************************************************/
ES_t   EXTI_enuDisableINT(   u8 Cpy_u8EXTI_ID  )
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( Cpy_u8EXTI_ID < EXTI_NUM)
	{
		switch(Cpy_u8EXTI_ID)
		{

		    //Disable interrupt 0 .
		case EXTI0:
			GICR &=~(EXTI_MASK_BIT<< INT0);
			break;

			//Disable interrupt 1 .
		case EXTI1:
			GICR &=~(EXTI_MASK_BIT<< INT1);
			break;

			//Disable interrupt 2 .
		case EXTI2:
			GICR &=~(EXTI_MASK_BIT<< INT2);
			break;

		}
		Local_enuErrorState = ES_OK  ;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE ;
	}

	return Local_enuErrorState;

}//End of EXTI_enuDisableINT.


/********************************************************************************************************/
/********************************************************************************************************/
/*Function Name   : EXTI_enuCallBack.                                                                   */
/*Description     : Utility function to initiate the callback.                                          */
/*                                                                                                      */
/*Argument        : Arg_1:  Address function that return void and accept                                */
/*                  =====   pointer or void as argument.                                                */
/*                                                                                                      */
/*                : Arg_2:  Address of the parameter of the passed function.                            */
/*                  =====                                                                               */
/*                                                                                                      */
/*                : Arg_3:  Interrupt ID                                                                */
/*                                                                                                      */
/*                           Range:                                                                     */
/*                                  EXTI_0 --->for interrupt_0                                          */
/*                                  EXTI_1 --->for interrupt_1                                          */
/*                                  EXTI_2 --->for interrupt_2                                          */
/*                                                                                                      */
/*                                                                                                      */
/*                                                                                                      */
/* Return          : Error state of type ES_t.                                                          */
/*.......................********************************************************************************/
ES_t   EXTI_enuCallBack(volatile void (*Cpy_pfunAppFunc)(void*)  , volatile void* Cpy_pvidParameter ,  u8 Cpy_u8EXTI_ID  )
{
	ES_t Local_enuErrorState =ES_NOK ;

	if( (Cpy_pfunAppFunc !=NULL)&&(Cpy_u8EXTI_ID < EXTI_NUM) )
	{

		EXTI_ApfunINTFunc[Cpy_u8EXTI_ID]= Cpy_pfunAppFunc ;

		EXTI_ApvidGenericParameter[Cpy_u8EXTI_ID]= Cpy_pvidParameter;

		Local_enuErrorState =ES_OK ;

	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER ;
	}




	return Local_enuErrorState;
}//End of EXTI_enuCallBack.


/**********************************************************************/
/************* Interrupt service routine for interrupt0 ***************/
ISR(VECT_INT0)
{

	if (  EXTI_ApfunINTFunc[EXTI0] != NULL )
	{
		(*EXTI_ApfunINTFunc[EXTI0])(EXTI_ApvidGenericParameter[EXTI0]);
	}
	else
	{
		//Do nothing.
	}

}

/**********************************************************************/
/************* Interrupt service routine for interrupt1 ***************/
ISR(VECT_INT1)
{
	if (  EXTI_ApfunINTFunc[EXTI1] != NULL )
	{
		(*EXTI_ApfunINTFunc[EXTI1])(EXTI_ApvidGenericParameter[EXTI1]);
	}
	else
	{
		//Do nothing.
	}

}


/**********************************************************************/
/************* Interrupt service routine for interrupt2 ***************/
ISR(VECT_INT2)
{

	if (  EXTI_ApfunINTFunc[EXTI2] != NULL )
	{
		(*EXTI_ApfunINTFunc[EXTI2])(EXTI_ApvidGenericParameter[EXTI2]);
	}
	else
	{
		//Do nothing.
	}

}


/***************************** END OF FILE. *********************************/
/****************************************************************************/
