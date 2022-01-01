/*
 * TIMER_Priv.h
 *
 *  Created on: Oct 29, 2021
 *      Author: Shaban
 */

#ifndef TIMER_PRIV_H_
#define TIMER_PRIV_H_

//*******************************************************************************/
/* TIMER Registers Definitions.                                                    */
/*******************************************************************************/
#define TCCR0   (*((volatile u8* const)0x53))
#define TCNT0   (*((volatile u8* const)0x52))
#define TIMSK   (*((volatile u8* const)0x59))
#define TIFR    (*((volatile u8* const)0x58))

#define TCCR2   (*((volatile u8* const)0x45))

// Define TCCR0 Bits
#define    FOC0                 7
#define    WGM00                6
#define    COM01                5
#define    COM00                4
#define    WGM01                3
#define    CS02                 2
#define    CS01                 1
#define    CS00                 0

// Define TIMSK Bits
#define    OCIE0                1
#define    TOIE0                0



// Define TCCR2 Bits
#define    FOC2                 7
#define    WGM20                6
#define    COM21                5
#define    COM20                4
#define    WGM21                3
#define    CS22                 2
#define    CS21                 1
#define    CS20                 0

// Define TIFR Register Bits.
#define    OCF0                 1
#define    TOV0                 0


/*******************************************************************************/
/********************************* PRIVATE MACROS ******************************/
// TIMER MODES.
#define    OVF                   0
#define    PWM                   1
#define    CTC                   2
#define    FAST_PWM              3

// TIMER PRESCALER
#define    PRES_NONE             (0)
#define    PRES_1                (1)
#define    PRES_8                (8)
#define    PRES_64               (64)
#define    PRES_256              (256UL)
#define    PRES_1024             (1024UL)



#define DISCONNECTED             0
#define TOGGLE_ON_COMP_MATCH     1
#define CLAER_ON_COMP_MATCH      2
#define SET_ON_COMP_MATCH        3




#define TIMER0                   0
#define TIMER1                   1
#define TIMER2                   2

#define TIMER_MSK_BIT            1

#define NUM_OF_TIMER             3

/**********************************************************************/
/***************************** PRIVATE FUNCTION ******************/
void static inline TIMER_vidStaticInline_SetPrescaler( u8 Copy_u8TimerID );
#endif /* TIMER_PRIV_H_ */
