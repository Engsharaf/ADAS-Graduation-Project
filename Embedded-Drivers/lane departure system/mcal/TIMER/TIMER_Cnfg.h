/*
 * TIMER_Cnfg.h
 *
 *  Created on: Oct 29, 2021
 *      Author: Shaban
 */

#ifndef TIMER_CNFG_H_
#define TIMER_CNFG_H_

#define TIMER_NUM            1
#define TIMER_F_CPU_KHZ      (1000UL)

typedef struct
{
	u8  TIMER_u8Mode           ;
	u8  TIMER_u8OC0_State      ;
	u16  TIMER_u16Prescaler    ;
	u16 TIMER_u16Freq_in_khz   ;

}TIMER_t;

extern TIMER_t TIMRE_AstrCnfg[];



#endif /* TIMER_CNFG_H_ */
