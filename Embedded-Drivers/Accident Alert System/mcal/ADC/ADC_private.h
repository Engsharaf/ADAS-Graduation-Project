
/*
 * ADC_private.h
 *  Created on: Oct 13, 2021
 *      Author: Shaban
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/*******************************************************************************/
/*****************************    PRIVATE MACROS     ***************************/



#define RIGHT_ADJ              0
#define LEFT_ADJ               1

#define AREF_REF               0
#define AVCC_REF               1
#define INTERNAL_AREF          2


#define PRES_2                 2
#define PRES_4                 4
#define PRES_8                 8
#define PRES_16                16
#define PRES_32                32
#define PRES_64                64
#define PRES_128               128


#define CHANNEL_0              0
#define CHANNEL_1              1
#define CHANNEL_2              2
#define CHANNEL_3              3
#define CHANNEL_4              4
#define CHANNEL_5              5
#define CHANNEL_6              6
#define CHANNEL_7              7

// Double Ended Mode.
//#define CHANNEL_0_0           8    // Gain:  *10
//#define CHANNEL_1_0           9    // Gain:  *10
//#define CHANNEL_0_0           10   // Gain:  *200
//#define CHANNEL_1_0           11   // Gain:  *200
//#define CHANNEL_2_2           12   // Gain:  *10
//#define CHANNEL_3_2           13   // Gain:  *10
//#define CHANNEL_2_2           14   // Gain:  *200
//#define CHANNEL_3_2           15   // Gain:  *200
//#define CHANNEL_0_1           16   // Gain:  *1
//#define CHANNEL_1_1           17   // Gain:  *1
//#define CHANNEL_2_1           18   // Gain:  *1
//#define CHANNEL_3_1           19   // Gain:  *1
//#define CHANNEL_4_1           20   // Gain:  *1
//#define CHANNEL_5_1           21   // Gain:  *1
//#define CHANNEL_6_1           22   // Gain:  *1
//#define CHANNEL_7_1           23   // Gain:  *1
//#define CHANNEL_0_2           24   // Gain:  *1
//#define CHANNEL_1_2           25   // Gain:  *1
//#define CHANNEL_2_2           26   // Gain:  *1
//#define CHANNEL_3_2           27   // Gain:  *1
 #define CHANNEL_4_2           28   // Gain:  *1




#define FREE_RUNNING           0
#define ANALOG_COMPARATOR      1
#define EXTI0                  2
#define EXTI0_CTC              3
#define EXTI0_OVF              4
#define EXTI0_CTC_B            5
#define EXTI1_OVF              6
#define EXTI1_CAP_EVNT         7







/*******************************************************************************/
/* ADC Register Definition.                                                    */
/*******************************************************************************/
#define ADMUX          (*((volatile u8* const)0x27))
#define ADCSRA         (*((volatile u8* const)0x26))
#define SFIOR          (*((volatile u8* const)0x50))
#define ADCH           (*((volatile u8* const)0x25))
#define ADCL           (*((volatile u8* const)0x24))


//ADMUX BITs DEFINITIONS.
#define    REFS1       7
#define    REFS0       6
#define    ADLAR       5
#define    MUX4        4
#define    MUX3        3
#define    MUX2        2
#define    MUX1        1
#define    MUX0        0



//ADCSRA BITs DEFINITIONS.
#define     ADEN       7
#define     ADSC       6
#define     ADATE      5
#define     ADIF       4
#define     ADIE       3
#define     ADPS2      2
#define     ADPS1      1
#define     ADPS0      0


//SFIOR BITs DEFINITIONS.
#define     ADTS2      7
#define     ADTS1      6
#define     ADTS0      5


#define SHIFT_EIGHT_BIT     8

#define ADC_MSK_BIT         1


#define GET_HIGH_BITS_RIGHT_ADJ  ( (ADCL>>2) | (ADCH<<6 )  )

















#endif /* ADC_PRIVATE_H_ */
