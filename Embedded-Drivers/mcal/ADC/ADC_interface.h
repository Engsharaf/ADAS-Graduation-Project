
/*
 * ADC_interface.h
 *
 *  Created on: May 26, 2021
 *      Author: Abdelrahman sharaf
 */

#ifndef ADC_INT_H_
#define ADC_INT_H_
/*
 * channels
 */


#define CHANNEL0 0
#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4
#define CHANNEL5 5
#define CHANNEL6 6
#define CHANNEL7 7

#define INVALID_VALUE 65535
/*
 * voltage refernce
 */
#define ADC_AREF                               1
#define ADC_INTERNAL_VCC                       5
#define ADC_INTERNAL_2_VOLT                    2
/*
 * adjustment
 */
#define ADC_RIGHT_ADJUSTMENT                   0
#define ADC_LEFT_ADJUSTMENT                    1
/*
 * ADCSRA register
 */
#define ADC_ADEN                               7
#define ADC_ADSC                               6
#define ADC_ADATE                              5
#define ADC_ADIF                               4
#define ADC_ADIE                               3
/*
 * admux_reg
 */
#define ADC_REFS0                             6
#define ADC_REFS1                             7
#define ADC_ADLAR                             5
#define ADC_DIVIDED_BY_2                       0x00
#define ADC_DIVIDED_BY_4                       0x02
#define ADC_DIVIDED_BY_8                       0x03
#define ADC_DIVIDED_BY_16                      0x04
#define ADC_DIVIDED_BY_32                      0x05
#define ADC_DIVIDED_BY_64                      0x06
#define ADC_DIVIDED_BY_128                     0x07
/*
 * auto trigger modes
 */
#define ADC_Free_Running_Mode                  0
#define ADC_ANALOG_COMPARATOR                  1
#define ADC_External_Interrupt_Request         2
#define ADC_Timer_Counter0_Compare_Match       3
#define ADC_Timer_Counter0_Overflow            4
#define ADC_Timer_Counter_Compare_Match_B      5
#define ADC_Timer_Counter1_Overflow            6
#define ADC_Timer_Counter1_Capture Event       7
/*
 * SFIOR
 */
#define ADC_ADTS0 5
#define ADC_ADTS1 6
#define ADC_ADTS2 7

/*****************************************************************************************
 * function name: ADC_vdEnableADC
 * input        :void
 * return type  :void
 * Description  : this function is to enable adc
 * **************************************************************************************
 */
void ADC_vdEnableADC(void);


/*****************************************************************************************
 * function name: ADC_vdDisableADC
 * input        :void
 * return type  :void
 * Description  : this function is to disable adc
 * **************************************************************************************
 */
void ADC_vdDisableADC(void);


/*****************************************************************************************
 * function name: ADC_vdIntialize
 * input        :void
 * return type  :void
 * Description  : this function is to select voltage reference and ADC_prescalare
 * and setting ADC_ADJUSTMENT
 * **************************************************************************************
 */
void ADC_vdIntialize(void);


/*****************************************************************************************
 * function name: ADC_vdGetADC_Value
 * input        :u8channel_id
 * return type  :ADC value
 * Description  : this function is to get ADC value for single channel
 * **************************************************************************************
 */
u16 ADC_u16GetADC_Value(u8 u8channel_id);


/*****************************************************************************************
 * function name: ADC_vdGetADC_ValueWithCommon_ADC1
 * input        :u8channel_id
 * return type  :ADC value
 * Description  : this function is to get ADC value for double channel with common
 * 				  negative edge ADC1
 * **************************************************************************************
 */
u16 ADC_vdGetADC_ValueWithCommon_ADC1(u8 u8channel_id);


/*****************************************************************************************
 * function name: ADC_vdSetADCISR_Callback
 * input        :pointer to function
 * return type  :void
 * Description  : this function is a call back function setter to set ADC ISR function
 * **************************************************************************************
 */
void ADC_vdSetADCISR_Callback(void (*callback)(void));


/*****************************************************************************************
 * function name: ADC_vdSetADCISR_Callback
 * input        :pointer to function
 * return type  :void
 * Description  : this function is a call back function setter to set ADC ISR function
 * **************************************************************************************
 */
void ADC_vdEnableAdcInterrupt(void);


/*****************************************************************************************
 * function name: ADC_vdEnableAdcAutoTriggerMode
 * input        : void
 * return type  :void
 * Description  : this function is to enable auto trigger mode
 * **************************************************************************************
 */
void ADC_vdEnableAdcAutoTriggerMode(void);


/*****************************************************************************************
 * function name: ADC_AutoTrigger
 * input        : void
 * return type  :void
 * Description  : this function is to enable auto trigger mode and select trigger mode
 * **************************************************************************************
 */
void ADC_AutoTrigger(void);

void ADC_vdGetAdcWithInterrupt(u8 u8channel_id);
u16 ADC_u16ReadADCVal(void);
#endif /* ADC_INT_H_ */