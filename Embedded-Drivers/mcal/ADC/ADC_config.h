
/*
 * ADC_config.h
 *
 *  Created on: May 26, 2021
 *      Author: Abdelrahman sharaf
 */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_


/************************************************************************
 * voltage referance selection
 * you should choose one of three choises
 * 1-AREF
 * 2-INTERNAL_VCC
 * 3-INTERNAL_2_VOLT
 * *********************************************************************
 */

#define ADC_VOLATGE_REFERENCE ADC_AREF

/**********************************************************************
 * ADJUSTMENT
 * you should choose ADC result adjustment
 * 1-ADC_RIGHT_ADJUSTMENT
 * 2-ADC_LEFT_ADJUSTMENT
 **********************************************************************
 */
#define ADC_ADJUSTMENT ADC_RIGHT_ADJUSTMENT

/**********************************************************************
 * ADC_PRESCALER_SELECTION
 * These bits determine the division factor between the XTAL frequency
 * and the input clock to the ADC
 * it should be
	 * 1- ADC_DIVIDED_BY_2
	 * 2- ADC_DIVIDED_BY_4
	 * 3- ADC_DIVIDED_BY_8
	 * 4- ADC_DIVIDED_BY_16
	 * 5- ADC_DIVIDED_BY_32
	 * 6- ADC_DIVIDED_BY_64
	 * 7- ADC_DIVIDED_BY_128
 ***********************************************************************
 */
#define ADC_PRESCALER ADC_DIVIDED_BY_128

/**********************************************************************
 * ADC_AUTO_TRIGGER_MODE
 * you should select auto trigger mode
 * it should be :
 *  			1-ADC_Free_Running_Mode
 *  			2-ADC_ANALOG_COMPARATOR
 *  			3-ADC_External_Interrupt_Request 0
 *  			4-ADC_Timer_Counter0_Compare_Match
 *  			5-ADC_Timer_Counter0_Overflow
 *  			6-ADC_Timer_Counter_Compare_Match_B
 *  			7-ADC_Timer_Counter1_Overflow
 *  			8-ADC_Timer_Counter1_Capture Event
 **********************************************************************
 */
#define ADC_AUTO_TRIGGER_MODE ADC_Free_Running_Mode
#endif /* ADC_CFG_H_ */