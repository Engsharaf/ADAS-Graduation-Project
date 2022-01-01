/*
 * TIMER_Cnfg.c
 *
 *  Created on: Oct 29, 2021
 *      Author: Shaban
 */
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\STD_TYPES.h"
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\errorStates.h"

#include "TIMER_Priv.h"
#include "TIMER_Cnfg.h"

TIMER_t TIMRE_AstrCnfg[TIMER_NUM]=
{
		{
				/* Timer0 configurations. */
				.TIMER_u8Mode         = OVF           ,  //init. func.
				.TIMER_u8OC0_State    = DISCONNECTED  ,  // init .
				.TIMER_u16Prescaler   = PRES_256      ,  // Start.
				.TIMER_u16Freq_in_khz = 1000          ,   // Start

		}
		,
		{
				/* Timer1 configurations. */
				//	.TIMER_u8Mode         = ?? ,
				//	.TIMER_u8OC0_State    = ?? ,
				//	.TIMER_u16Prescaler   = ?? ,
				//	.TIMER_u16Freq_in_khz = ?? ,
		}
		,
		{
				/* Timer2 configurations. */
				//	.TIMER_u8Mode         = ??  ,
				//	.TIMER_u8OC0_State    = ??  ,
				//	.TIMER_u16Prescaler   = ??  ,
				//	.TIMER_u16Freq_in_khz = ??  ,
		}


};
