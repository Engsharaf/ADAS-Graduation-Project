/*
 * ADC_Config.h
 *
 *  Created on: Oct 13, 2021
 *      Author: Shaban
 */

#ifndef ACD_CONFIG_H_
#define ACD_CONFIG_H_
/*******************************************************************************/
/*****************************     PUBLIC MACROS     ***************************/

/*******************************************************************************/
/*******************************************************************************/
/* Description :          Macro to Configure the ADC prescaler:                */
/* Options     :          PRES_2           ,             PRES_32               */
/*                        PRES_4           ,             PRES_64               */
/*                        PRES_8           ,             PRES_128              */
/*                        PRES_16                                              */
/*
 * Hint        :     50 kHz and 200 kHz                                       */
/*******************************************************************************/
#define ADC_PRES     PRES_8



/*******************************************************************************/
/*******************************************************************************/
/* Description :          Macro to Configure the ADC Voltage Reference:
 *         */
/* Options     :           AREF_REF                                            */
/*                         AVCC_REF                                            */
/*                         INTERNAL_AREF     '2.56 volt'                           */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
#define ADC_REF_VOLT    AVCC_REF





#endif /* ACD_CONFIG_H_ */
