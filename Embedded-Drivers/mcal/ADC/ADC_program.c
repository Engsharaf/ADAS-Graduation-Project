/****************************************************************************/
/* Title                 :   ADC_program                                    */
/* Filename              :   ADC_program.c                                  */
/* Author                :   Shaban Abdullah Awad                           */
/* Origin Date           :   Oct 13, 2021                                   */
/* Version               :   1.0.0                                          */
/* Compiler              :   mingw GCC                                      */
/* Target                :   ATmega16 , ATmega32                            */
/* Notes                 :   None                                           */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/******************************  INCLUDES  **********************************/
#include "STD_TYPES.h"
#include "errorStates.h"

#include "interrupt.h"
#include "GIE_interface.h"

#include "ADC_private.h"
#include "ADC_Config.h"

/*********************************************************************************/
/* Description     : Tow global arrays of pointers to hold the Addresses of      */
/*                   the functions and its arguments to use the in the           */
/*                   CallBack.                                                   */
/*********************************************************************************/
static volatile void (*ADC_pvidfunISRFunc)(void*)= NULL ;

static volatile void* ADC_pvidISRParameter=  NULL ;


/*****************************************************************************/
/*****************************************************************************/
/* Function Name   : ADC_enuInit.                                            */
/* Description     : Utility function to initialize the ADC .                */
/* Argument        : None .                                                  */
/* Return          : Error state of type ES_t.                               */
/**.............**************************************************************/
ES_t ADC_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK ;


	/*************************************************************************/
	/*ADC Voltage Reference cases Handling.                                  */
	/*************************************************************************/
	ADMUX  &=~((ADC_MSK_BIT<<REFS1)|(ADC_MSK_BIT<<REFS0));

#if      ADC_REF_VOLT   ==    AREF_REF
	//Do nothing.

#elif    ADC_REF_VOLT   ==    AVCC_REF
	ADMUX  |=(ADC_MSK_BIT<<REFS0);

#elif    ADC_REF_VOLT   ==    INTERNAL_AREF
	ADMUX  |=(ADC_MSK_BIT<<REFS1)|(ADC_MSK_BIT<<REFS0);

#else
#error "The ADC_REF_VOLT value that you Chosen is not Valid!!."

#endif


	/****************************************************************************************/
	/*ADC Prescaler cases Handling and Right Presentation of the ADC result is Selected.    */
	/****************************************************************************************/
	ADCSRA  &=~((ADC_MSK_BIT<<ADPS0)|(ADC_MSK_BIT<<ADPS1)|(ADC_MSK_BIT<<ADPS2));

#if      ADC_PRES   ==    PRES_2
	//Do nothing.

#elif    ADC_PRES   ==    PRES_4
	ADCSRA |=(ADC_MSK_BIT<<ADPS1);

#elif    ADC_PRES   ==    PRES_8
	ADCSRA |=(ADC_MSK_BIT<<ADPS0)|(ADC_MSK_BIT<<ADPS1);

#elif    ADC_PRES   ==    PRES_16
	ADCSRA |=(ADC_MSK_BIT<<ADPS2);

#elif    ADC_PRES   ==    PRES_32
	ADCSRA |=(ADC_MSK_BIT<<ADPS0)|(ADC_MSK_BIT<<ADPS2);

#elif    ADC_PRES   ==    PRES_64
	ADCSRA |=(ADC_MSK_BIT<<ADPS1)|(ADC_MSK_BIT<<ADPS2);

#elif    ADC_PRES   ==    PRES_128
	ADCSRA |=(ADC_MSK_BIT<<ADPS0)|(ADC_MSK_BIT<<ADPS1)|(ADC_MSK_BIT<<ADPS2);

#else

#error "Not valid ADC_PRES value!!."

#endif

	return Local_enuErrorState   ;
}//End of ADC_enuInit.




/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuEnable.                                           */
/* Description     : Utility function to Enable ADC .                         */
/* Argument        : None .                                                   */
/* Return          : Error state of type ES_t.                                */
/**.....................*******************************************************/
ES_t ADC_enuEnable(void)
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( !((ADCSRA>>ADEN)& ADC_MSK_BIT) )
	{
		/* Enable ADC .             */
		ADCSRA |= (ADC_MSK_BIT<<ADEN);

		Local_enuErrorState = ES_OK ;

	}
	else
	{
		Local_enuErrorState = ES_OK ;
	}

	return Local_enuErrorState   ;
}//End of ADC_enuEnable.


/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuDisable.                                          */
/* Description     : Utility function to Disable ADC .                        */
/* Argument        : None .                                                   */
/* Return          : Error state of type ES_t.                                */
/**.....................*******************************************************/
ES_t ADC_enuDisable(void)
{

	ES_t Local_enuErrorState = ES_NOK ;

	if( ((ADCSRA>>ADEN)& ADC_MSK_BIT) )
	{
		/* Disable ADC .             */
		ADCSRA &=~(ADC_MSK_BIT<<ADEN);

		Local_enuErrorState = ES_OK ;

	}
	else
	{
		Local_enuErrorState = ES_OK ;
	}

	/* Report the Final State.   */
	return Local_enuErrorState    ;

}//End of ADC_enuEnable.




/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuStartConversion.                                  */
/* Description     : Utility function to Trigger ADC Start Conversion.        */
/* Argument        : None .                                                   */
/* Return          : Error state of type ES_t.                                */
/**.................***********************************************************/
ES_t ADC_enuStartConversion(void)
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( !((ADCSRA>>ADSC)&ADC_MSK_BIT) )
	{
		ADCSRA |=(ADC_MSK_BIT<<ADSC);

		Local_enuErrorState = ES_OK;
	}
	else
	{
		//Do nothing.
	}

	/* Report the Final State.   */
	return Local_enuErrorState    ;

}//End of ADC_enuStartConversion.




/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuPollingSys.                                       */
/* Description     : This Function Stuck the execution of the program By      */
/*                   using polling Technique.                                 */
/* Argument        : None .                                                   */
/* Return          : Error state of type ES_t.                                */
/**.................***********************************************************/
ES_t ADC_enuPollingSys(void)
{
	ES_t Local_enuErrorState = ES_NOK ;


	/* Monitor the ADC interrupt flag. */
	while( !((ADCSRA>>ADIF)&ADC_MSK_BIT) );

	/* Earase the flag.        */
	ADCSRA |=(ADC_MSK_BIT<<ADIF);

	/* Report the Final State.   */
	return Local_enuErrorState    ;

}//End of ADC_enuPollingSys.


/********************************************************************************/
/********************************************************************************/
/* Function Name   : ADC_enuRead.                                               */
/* Description     : Utility Function Read whole ten bits of ADC Data Register. */
/* Argument        : Address Variable of u8 Type .                              */
/* Return          : Error state of type ES_t.                                  */
/**.................*************************************************************/
ES_t ADC_enuRead(u16* Cpy_pu16Value )
{
	ES_t Local_enuErrorState = ES_NOK ;

	*Cpy_pu16Value   =  ADCL ;

	*Cpy_pu16Value  |=  ((u16)ADCH<< SHIFT_EIGHT_BIT) ;

	/* Report the Final State.   */
	return Local_enuErrorState    ;

}//End of ADC_enuRead.




/********************************************************************************/
/********************************************************************************/
/* Function Name   : ADC_enuReadHighValue.                                               */
/* Description     : Utility Function Read whole ten bits of ADC Data Register. */
/* Argument        : Address Variable of u8 Type .                              */
/* Return          : Error state of type ES_t.                                  */
/**.................*************************************************************/
ES_t ADC_enuReadHighValue(u8 * Copy_pu8Value)
{
	ES_t Local_enuErrorState = ES_NOK;


	*Copy_pu8Value  = (ADCL >> 2);
	*Copy_pu8Value |= (ADCH << 6);

	return Local_enuErrorState;
}





/*********************************************************************************/
/*********************************************************************************/
/* Function Name   : ADC_enuSelectChannel.                                       */
/* Description     : Function to Select a specific ADC Channel to read.          */
/*                   using polling Technique.                                    */
/* Argument        : The Selected channel:                                       */
/*                                                                               */
/*                 :Range:                                                       */
/*                        ADC_CHANNEL_0  ,  ADC_CHANNEL_0_0  ,  ADC_CHANNEL_2_1  */
/*                        ADC_CHANNEL_1  ,  ADC_CHANNEL_1_0  ,  ADC_CHANNEL_3_1  */
/*                        ADC_CHANNEL_2  ,  ADC_CHANNEL_0_0  ,  ADC_CHANNEL_4_1  */
/*                        ADC_CHANNEL_3  ,  ADC_CHANNEL_1_0  ,  ADC_CHANNEL_5_1  */
/*                        ADC_CHANNEL_4  ,  ADC_CHANNEL_2_2  ,  ADC_CHANNEL_6_1  */
/*                        ADC_CHANNEL_5  ,  ADC_CHANNEL_3_2  ,  ADC_CHANNEL_7_1  */
/*                        ADC_CHANNEL_6  ,  ADC_CHANNEL_2_2  ,  ADC_CHANNEL_0_2  */
/*                        ADC_CHANNEL_7  ,  ADC_CHANNEL_3_2  ,  ADC_CHANNEL_1_2  */
/*                                          ADC_CHANNEL_0_1  ,  ADC_CHANNEL_2_2  */
/*                                          ADC_CHANNEL_1_1  ,  ADC_CHANNEL_3_2  */
/*                                                                               */
/* Return          : Error state of type ES_t.                                   */
/**......................*********************************************************/
ES_t ADC_enuSelectChannel(u8 Cpy_u8ChannelID )
{
	ES_t Local_enuErrorState = ES_NOK ;

	/* Check that the Passed Arg. is in the Correct range. */
	if( Cpy_u8ChannelID <= CHANNEL_4_2 )
	{
		/* Clearing the previous Choice.    */
		ADMUX &=~( (ADC_MSK_BIT<<MUX4)|(ADC_MSK_BIT<<MUX3)|(ADC_MSK_BIT<<MUX2)|(ADC_MSK_BIT<<MUX1)|(ADC_MSK_BIT<<MUX0)  );

		/* Write the New Choice in the ADMUX Register. */
		ADMUX |= Cpy_u8ChannelID ;

		/* Report that the Selected channel has been Selected.*/
		Local_enuErrorState = ES_OK ;
	}
	else
	{
		/* Report that the passed Channel is Not Valid to Selected.*/
		Local_enuErrorState = ES_OUT_OF_RANGE ;
	}

	/* Report the Final State.   */
	return Local_enuErrorState    ;

}//End of ADC_enuSelectChannel.




/*********************************************************************************/
/*********************************************************************************/
/* Function Name   : ADC_enuEnableTriggeringMode.                                */
/* Description     : Function to Select  the ADC triggring source.               */
/* Argument        : The Selected Triggerring Source.                            */
/*                                                                               */
/*                 : Range:                                                      */
/*                         ADC_FREE_RUNNING        ,  ADC_EXTI0_OVF              */
/*                         ADC_ANALOG_COMPARATOR   ,  ADC_EXTI0_CTC_B            */
/*                         ADC_EXTI0               ,  ADC_EXTI1_OVF              */
/*                         ADC_EXTI0_CTC           ,  ADC_EXTI1_CAP_EVNT         */
/*                                                                               */
/*                                                                               */
/* Return          : Error state of type ES_t.                                   */
/**..............................*************************************************/
ES_t ADC_enuEnableTriggeringMode(u8 Cpy_u8TriggingSource)
{
	ES_t Local_enuErrorState = ES_NOK ;


	if( Cpy_u8TriggingSource <= EXTI1_CAP_EVNT )
	{
		/* Disable auto triggering source.  */
		ADCSRA  &=~(ADC_MSK_BIT<<ADATE);

		/* Reset the Auto_triggering Source Selection Bits.                                 */
		SFIOR &=~(  (ADC_MSK_BIT<<ADTS2) | ( ADC_MSK_BIT<<ADTS1 ) | (ADC_MSK_BIT<<ADTS0)   );

		/* Switch to the Suitable Triggrinning Source.*/
		switch( Cpy_u8TriggingSource )
		{
		case FREE_RUNNING :
			break;

		case ANALOG_COMPARATOR :
			SFIOR |=(ADC_MSK_BIT<<ADTS0) ;
			break;

		case EXTI0 :
			SFIOR |=(ADC_MSK_BIT<<ADTS1) ;
			break;

		case EXTI0_CTC :
			SFIOR |=(ADC_MSK_BIT<<ADTS0) ;
			SFIOR |=(ADC_MSK_BIT<<ADTS1) ;
			break;

		case EXTI0_OVF :
			SFIOR |=(ADC_MSK_BIT<<ADTS2) ;
			break;

		case EXTI0_CTC_B :
			SFIOR |=(ADC_MSK_BIT<<ADTS0) ;
			SFIOR |=(ADC_MSK_BIT<<ADTS2) ;
			break;

		case EXTI1_OVF :
			SFIOR |=(ADC_MSK_BIT<<ADTS2) ;
			SFIOR |=(ADC_MSK_BIT<<ADTS1) ;
			break;

		case EXTI1_CAP_EVNT :
			SFIOR |=(ADC_MSK_BIT<<ADTS0) ;
			SFIOR |=(ADC_MSK_BIT<<ADTS1) ;
			SFIOR |=(ADC_MSK_BIT<<ADTS2) ;

			break;

		default:;

		}

		//Enable auto triggering source.
		ADCSRA  |=(ADC_MSK_BIT<<ADATE);

		/* Report that the Triggerring Source has been Selected.*/
		Local_enuErrorState = ES_OK ;
	}
	else
	{
		/* Report that the passed Triggerring Sourc is Not Valid.*/
		Local_enuErrorState =  ES_OUT_OF_RANGE ;
	}

	/* Report the Final State.   */
	return Local_enuErrorState    ;


}//End of ADC_enuEnableTriggeringMode.




/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuDisableTriggeringMode.                            */
/* Description     : Utility Fuction to Disable the AutoTriggerring mode.     */
/* Argument        : None.                                                    */
/* Return          : Error state of type ES_t.                                */
/**..............................**********************************************/
ES_t ADC_enuDisableTriggeringMode(void)
{
	ES_t Local_enuErrorState = ES_NOK ;


	// Check if the ADC is enabled.
	if( ((ADCSRA>>ADATE)&ADC_MSK_BIT) )
	{
		// Disable the ADC.
		ADCSRA  &=~(ADC_MSK_BIT<<ADATE);

		// Update the Error State.
		Local_enuErrorState = ES_OK ;
	}
	else
	{
		//Do nothing.
	}

	/* Report the Final State.   */
	return Local_enuErrorState    ;

}//End of ADC_enuDisableTriggeringMode.




/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuEnableInterruptMode.                              */
/* Description     : Utility Function to Enable the ADC interrupt when the    */
/*                   Conversion is compolet.                                  */
/* Argument        : None.                                                    */
/* Return          : Error state of type ES_t.                                */
/**............................************************************************/
ES_t ADC_enuEnableInterruptMode(void)
{
	ES_t Local_enuErrorState = ES_NOK ;

	/* -Check if the interrupt is already Enabled.  */
	if( !((ADCSRA>>ADIE)&ADC_MSK_BIT) )
	{
		// Enable the ADC Interrupt.
		ADCSRA |=(ADC_MSK_BIT<<ADIE);

		// Update the Error State.
		Local_enuErrorState = ES_OK ;
	}
	else
	{
		//Do nothing.
	}

	/* Report the Final State.   */
	return Local_enuErrorState    ;

}//End ofADC_enuEnableInterruptMode.




/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuDisableInterruptMode.                             */
/* Description     : Utility Function to Disable the ADC.                     */
/* Argument        : None.                                                    */
/* Return          : Error state of type ES_t.                                */
/**.................***********************************************************/
ES_t ADC_enuDisableInterruptMode(void)
{
	ES_t Local_enuErrorState = ES_NOK ;

	/* Check if the interrupt is already Disabled.  */
	if( ((ADCSRA>>ADIE)&ADC_MSK_BIT) )
	{
		// Disable the ADC interrupt.
		ADCSRA &=~(ADC_MSK_BIT<<ADIE);

		// Report that the interrupt is Disabled.
		Local_enuErrorState = ES_OK ;
	}
	else
	{
		// Do nothing.
	}

	// Report the final State.
	return Local_enuErrorState   ;

}//End of ADC_enuDisableInterruptMode.








/*********************************************************/
/*********************************************************/
/*********************************************************/
ES_t ADC_enuCallBack(volatile void(*Cpy_pfunAppFunc)(void*) ,  void* Cpy_pvidAppPara)
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( Cpy_pfunAppFunc != NULL )
	{
		ADC_pvidfunISRFunc   = Cpy_pfunAppFunc ;

		ADC_pvidISRParameter = Cpy_pvidAppPara ;

		Local_enuErrorState  = ES_OK ;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER  ;
	}

	/* Report the Final State.   */
	return Local_enuErrorState    ;

}//End of


ISR(VECT_ADC)
{

	if (ADC_pvidfunISRFunc != NULL)
	{
		ADC_pvidfunISRFunc(ADC_pvidISRParameter);
	}

}



/****************************** END OF FILE  *********************************/
/*****************************************************************************/
