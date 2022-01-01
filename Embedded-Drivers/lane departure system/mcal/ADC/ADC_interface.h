
/*
 * ACD_interface.h
 *
 *  Created on: Oct 13, 2021
 *      Author: Shaban
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_
/*******************************************************************************/
/*****************************     PUBLIC MACROS     ***************************/
#define ADC_FREE_RUNNING             0
#define ADC_ANALOG_COMPARATOR        1
#define ADC_EXTI0                    2
#define ADC_EXTI0_CTC                3
#define ADC_EXTI0_OVF                4
#define ADC_EXTI0_CTC_B              5
#define ADC_EXTI1_OVF                6
#define ADC_EXTI1_CAP_EVNT           7

// Single Ended Mode.
#define ADC_CHANNEL_0               0
#define ADC_CHANNEL_1               1
#define ADC_CHANNEL_2               2
#define ADC_CHANNEL_3               3
#define ADC_CHANNEL_4               4
#define ADC_CHANNEL_5               5
#define ADC_CHANNEL_6               6
#define ADC_CHANNEL_7               7

// Double Ended Mode.
// #define ADC_CHANNEL_0_0           8    // Gain:  *10
// #define ADC_CHANNEL_1_0           9    // Gain:  *10
// #define ADC_CHANNEL_0_0           10   // Gain:  *200
// #define ADC_CHANNEL_1_0           11   // Gain:  *200
// #define ADC_CHANNEL_2_2           12   // Gain:  *10
// #define ADC_CHANNEL_3_2           13   // Gain:  *10
// #define ADC_CHANNEL_2_2           14   // Gain:  *200
// #define ADC_CHANNEL_3_2           15   // Gain:  *200
// #define ADC_CHANNEL_0_1           16   // Gain:  *1
// #define ADC_CHANNEL_1_1           17   // Gain:  *1
// #define ADC_CHANNEL_2_1           18   // Gain:  *1
// #define ADC_CHANNEL_3_1           19   // Gain:  *1
// #define ADC_CHANNEL_4_1           20   // Gain:  *1
// #define ADC_CHANNEL_5_1           21   // Gain:  *1
// #define ADC_CHANNEL_6_1           22   // Gain:  *1
// #define ADC_CHANNEL_7_1           23   // Gain:  *1
// #define ADC_CHANNEL_0_2           24   // Gain:  *1
// #define ADC_CHANNEL_1_2           25   // Gain:  *1
// #define ADC_CHANNEL_2_2           26   // Gain:  *1
// #define ADC_CHANNEL_3_2           27   // Gain:  *1
#define  ADC_CHANNEL_4_2           28   // Gain:  *1


/*******************************************************************************/
/****************************    PUBLIC FUNCTIONS    ***************************/


/*****************************************************************************/
/*****************************************************************************/
/* Function Name   : ADC_enuInit.                                            */
/* Description     : Utility function to initialize the ADC .                */
/* Argument        : None .                                                  */
/* Return          : Error state of type ES_t.                               */
/**.............**************************************************************/
ES_t ADC_enuInit(void);
/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuEnable.                                           */
/* Description     : Utility function to Enable ADC .                         */
/* Argument        : None .                                                   */
/* Return          : Error state of type ES_t.                                */
/**.....................*******************************************************/
ES_t ADC_enuEnable(void);



/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuDisable.                                          */
/* Description     : Utility function to Disable ADC .                        */
/* Argument        : None .                                                   */
/* Return          : Error state of type ES_t.                                */
/**.....................*******************************************************/
ES_t ADC_enuDisable(void);




/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuStartConversion.                                  */
/* Description     : Utility function to Trigger ADC Start Conversion.        */
/* Argument        : None .                                                   */
/* Return          : Error state of type ES_t.                                */
/**.................***********************************************************/
ES_t ADC_enuStartConversion(void);




/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuPollingSys.                                       */
/* Description     : This Function Stuck the execution of the program By      */
/*                   using polling Technique.                                 */
/* Argument        : None .                                                   */
/* Return          : Error state of type ES_t.                                */
/**.................***********************************************************/
ES_t ADC_enuPollingSys(void);




/********************************************************************************/
/********************************************************************************/
/* Function Name   : ADC_enuRead.                                               */
/* Description     : Utility Function Read whole ten bits of ADC Data Register. */
/* Argument        : Address Variable of u8 Type .                              */
/* Return          : Error state of type ES_t.                                  */
/**.................*************************************************************/
ES_t ADC_enuRead(u16* Cpy_pu16Value );



/********************************************************************************/
/********************************************************************************/
/* Function Name   : ADC_enuReadHighValue.                                               */
/* Description     : Utility Function Read whole ten bits of ADC Data Register. */
/* Argument        : Address Variable of u8 Type .                              */
/* Return          : Error state of type ES_t.                                  */
/**.................*************************************************************/
ES_t ADC_enuReadHighValue(u8 * Copy_pu8Value);





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
ES_t ADC_enuSelectChannel(u8 Cpy_u8ChannelID );




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
ES_t ADC_enuEnableTriggeringMode(u8 Cpy_u8TriggingSource);



/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuDisableTriggeringMode.                            */
/* Description     : Utility Fuction to Disable the AutoTriggerring mode.     */
/* Argument        : None.                                                    */
/* Return          : Error state of type ES_t.                                */
/**..............................**********************************************/
ES_t ADC_enuDisableTriggeringMode(void) ;




/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuEnableInterruptMode.                              */
/* Description     : Utility Function to Enable the ADC interrupt when the    */
/*                   Conversion is compolet.                                  */
/* Argument        : None.                                                    */
/* Return          : Error state of type ES_t.                                */
/**............................************************************************/
ES_t ADC_enuEnableInterruptMode(void);




/******************************************************************************/
/******************************************************************************/
/* Function Name   : ADC_enuDisableInterruptMode.                             */
/* Description     : Utility Function to Disable the ADC.                     */
/* Argument        : None.                                                    */
/* Return          : Error state of type ES_t.                                */
/**.................***********************************************************/
ES_t ADC_enuDisableInterruptMode(void);





ES_t ADC_enuCallBack(volatile void(*Cpy_pfunAppFunc)(void*) ,  void* Cpy_pvidAppPara);




#endif /* ADC_INTERFACE_H_ */
