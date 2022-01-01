/*
 * TIMER_interface.h
 *
 *  Created on: Oct 29, 2021
 *      Author: Shaban
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_
// Cpy_pstrEXTICnfg

#define TIMER0          0
#define TIMER1          1
#define TIMER2          2


ES_t TIMER_enuInit(TIMER_t* Cpy_pstrtTimerCnfg );

ES_t TIMER_enuSetAsyncDelay( u8 Copy_u8TimerID ,u32 Copy_u32Time ,void (*Copy_pfunApp)(void*) ,void* Copy_pvidParameter );

ES_t TIMER_enuSetSyncDelay(u8 Copy_u8TimerID , u32 Copy_u32Time);



#endif /* TIMER_INTERFACE_H_ */
