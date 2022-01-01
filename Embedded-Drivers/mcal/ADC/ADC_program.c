
/*
 * ADC_program.c
 *
 *  Created on: May 26, 2021
 *      Author: Abdelrahman Sharaf
 */
#include"../STD_TYPES.h"
#include "../BIT_math.h"
#include "ADC_cfg.h"
#include "ADC_priv.h"
#include "ADC_int.h"

void (*PF)(void);
/*****************************************************************************************
 * function name: ADC_vdEnableADC
 * input        :void
 * return type  :void
 * Description  : this function is to enable adc
 * **************************************************************************************
 */
void ADC_vdEnableADC(void)
{
	SET_BIT(ADC_ADCSRA_REG,ADC_ADEN);
}
/*****************************************************************************************
 * function name: ADC_vdDisableADC
 * input        :void
 * return type  :void
 * Description  : this function is to disable adc
 * **************************************************************************************
 */
void ADC_vdDisableADC(void)
{
	CLEAR_BIT(ADC_ADCSRA_REG,ADC_ADEN);

}
/*****************************************************************************************
 * function name: ADC_vdIntialize
 * input        :void
 * return type  :void
 * Description  : this function is to select voltage reference and ADC_prescalare
 * and setting ADC_ADJUSTMENT
 * **************************************************************************************
 */
void ADC_vdIntialize(void)
{
#if ADC_VOLATGE_REFERENCE==ADC_AREF
	CLEAR_BIT(ADC_ADMUX_REG,ADC_REFS0);
	CLEAR_BIT(ADC_ADMUX_REG,ADC_REFS1);
#endif
#if ADC_VOLATGE_REFERENCE == ADC_INTERNAL_VCC
	SET_BIT(ADC_ADMUX_REG,ADC_REFS0);
	CLEAR_BIT(ADC_ADMUX_REG,ADC_REFS1);
#endif
#if ADC_VOLATGE_REFERENCE == ADC_INTERNAL_2_VOLT
	SET_BIT(ADC_ADMUX_REG,ADC_REFS0);
	SET_BIT(ADC_ADMUX_REG,ADC_REFS1);
#endif

	/*
	 * setting ADC_PRESCALAER
	 */
	ADC_ADCSRA_REG = ((ADC_ADCSRA_REG & ~(0x07))|ADC_PRESCALER);
//	CLEAR_BIT(ADC_ADCSRA_REG,0);
//	CLEAR_BIT(ADC_ADCSRA_REG,1);
//	CLEAR_BIT(ADC_ADCSRA_REG,2);
	/*
	 * setting ADC_ADJUSTMENT
	 */
#if ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTMENT
	CLEAR_BIT(ADC_ADMUX_REG,ADC_ADLAR);
#endif

#if ADC_ADJUSTMENT == ADC_LEFT_ADJUSTMENT
	SET_BIT(ADC_ADMUX_REG,ADC_ADLAR);
#endif

	ADC_vdEnableADC();
}
/*****************************************************************************************
 * function name: ADC_vdGetADC_Value
 * input        :u8channel_id
 * return type  :ADC value
 * Description  : this function is to get ADC value for single channel
 * **************************************************************************************
 */
u16 ADC_u16GetADC_Value(u8 u8channel_id)
{
	/*
	 * select channel
	 */
	if(u8channel_id<8)
	{
		ADC_ADMUX_REG = ((ADC_ADMUX_REG & ~(0x1f) )| u8channel_id );

		/*
		 * start coversion
		 */
		SET_BIT(ADC_ADCSRA_REG,ADC_ADSC);
//		while((GET_BIT(ADC_ADCSRA_REG,ADC_ADIF))==0)
		while((GET_BIT(ADC_ADCSRA_REG,ADC_ADSC))==1)
		{
			/*
			 * wait untill finish
			 */
		}
		return ADC_ADC_REG;
	}
	else
	{
		return INVALID_VALUE;
	}



}
/*****************************************************************************************
 * function name: ADC_vdGetADC_ValueWithCommon_ADC1
 * input        :u8channel_id
 * return type  :ADC value
 * Description  : this function is to get ADC value for double channel with common
 * 				  negative edge ADC1
 * **************************************************************************************
 */
u16 ADC_vdGetADC_ValueWithCommon_ADC1(u8 u8channel_id)
{
	/*
	 * select channel
	 */
	ADC_ADMUX_REG = ((ADC_ADMUX_REG & ~(0x1f) )| u8channel_id );

	/*
	 * enable adc
	 */
	ADC_vdEnableADC();
	/*
	 * start coversion
	 */
	SET_BIT(ADC_ADCSRA_REG,ADC_ADSC);
	while((GET_BIT(ADC_ADCSRA_REG,ADC_ADSC))==1)
	{
		/*
		 * wait untill finish
		 */
	}
	return ADC_ADC_REG;

}
/*****************************************************************************************
 * function name: ADC_vdSetADCISR_Callback
 * input        :pointer to function
 * return type  :void
 * Description  : this function is a call back function setter to set ADC ISR function
 * **************************************************************************************
 */
void ADC_vdSetADCISR_Callback(void (*callback)(void))
{
	PF = callback;
}
/*****************************************************************************************
 * function name: ADC_vdSetADCISR_Callback
 * input        :pointer to function
 * return type  :void
 * Description  : this function is a call back function setter to set ADC ISR function
 * **************************************************************************************
 */
void ADC_vdGetAdcWithInterrupt(u8 u8channel_id)
{
	ADC_vdEnableAdcInterrupt();
	if(u8channel_id<8)
	{
		ADC_ADMUX_REG = ((ADC_ADMUX_REG & ~(0x1f) )| u8channel_id );

		/*
		 * start coversion
		 */
		SET_BIT(ADC_ADCSRA_REG,ADC_ADSC);
	}
}
u16 ADC_u16ReadADCVal(void)
{
	return ADC_ADC_REG;
}
void ADC_vdEnableAdcInterrupt(void)
{
	SET_BIT(ADC_ADCSRA_REG,ADC_ADIE);
}
/*
 * for compiler
 */
void __vector_16(void) __attribute__(( signal , used ));
void __vector_16(void)
{
	PF();
}
/*****************************************************************************************
 * function name: ADC_vdEnableAdcAutoTriggerMode
 * input        : void
 * return type  :void
 * Description  : this function is to enable auto trigger mode
 * **************************************************************************************
 */
void ADC_vdEnableAdcAutoTriggerMode(void)
{
	SET_BIT(ADC_ADCSRA_REG,ADC_ADATE);
}
/*****************************************************************************************
 * function name: ADC_AutoTrigger
 * input        : void
 * return type  :void
 * Description  : this function is to enable auto trigger mode and select trigger mode
 * **************************************************************************************
 */
void ADC_AutoTrigger(void)
{
	ADC_vdEnableAdcAutoTriggerMode();
#if ADC_AUTO_TRIGGER_MODE == ADC_Free_Running_Mode
	CLEAR_BIT(ADC_SFIOR_REG,ADC_ADTS0);
	CLEAR_BIT(ADC_SFIOR_REG,ADC_ADTS1);
	CLEAR_BIT(ADC_SFIOR_REG,ADC_ADTS2);
#endif

#if ADC_AUTO_TRIGGER_MODE == ADC_Timer_Counter0_Compare_Match
	SET_BIT(ADC_SFIOR_REG,ADC_ADTS0);
	SET_BIT(ADC_SFIOR_REG,ADC_ADTS1);
	CLEAR_BIT(ADC_SFIOR_REG,ADC_ADTS2);
#endif

#if ADC_AUTO_TRIGGER_MODE == ADC_Timer_Counter0_Overflow
	CLEAR_BIT(ADC_SFIOR_REG,ADC_ADTS0);
	CLEAR_BIT(ADC_SFIOR_REG,ADC_ADTS1);
	SET_BIT(ADC_SFIOR_REG,ADC_ADTS2);
#endif

#if ADC_AUTO_TRIGGER_MODE == ADC_Timer_Counter_Compare_Match_B
	SET_BIT(ADC_SFIOR_REG,ADC_ADTS0);
	CLEAR_BIT(ADC_SFIOR_REG,ADC_ADTS1);
	SET_BIT(ADC_SFIOR_REG,ADC_ADTS2);
#endif

#if ADC_AUTO_TRIGGER_MODE == ADC_Timer_Counter1_Overflow
	CLEAR_BIT(ADC_SFIOR_REG,ADC_ADTS0);
	SET_BIT(ADC_SFIOR_REG,ADC_ADTS1);
	SET_BIT(ADC_SFIOR_REG,ADC_ADTS2);
#endif

#if ADC_AUTO_TRIGGER_MODE == ADC_Timer_Counter1_Overflow
	SET_BIT(ADC_SFIOR_REG,ADC_ADTS0);
	SET_BIT(ADC_SFIOR_REG,ADC_ADTS1);
	SET_BIT(ADC_SFIOR_REG,ADC_ADTS2);
#endif


#if ADC_AUTO_TRIGGER_MODE == ADC_External_Interrupt_Request
	CLEAR_BIT(ADC_SFIOR_REG,ADC_ADTS0);
	SET_BIT(ADC_SFIOR_REG,ADC_ADTS1);
	CLEAR_BIT(ADC_SFIOR_REG,ADC_ADTS2);
#endif



#if ADC_AUTO_TRIGGER_MODE == ADC_ANALOG_COMPARATOR
	SET_BIT(ADC_SFIOR_REG,ADC_ADTS0);
	CLEAR_BIT(ADC_SFIOR_REG,ADC_ADTS1);
	CLEAR_BIT(ADC_SFIOR_REG,ADC_ADTS2);
#endif


}