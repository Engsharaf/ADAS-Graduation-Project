
/*****************************************************************************/
/*****************************************************************************/
/* Title                 :   EXTI_priv                                       */
/* Filename              :   EXTI_priv.h                                     */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Oct 8, 2021                                     */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw GCC                                       */
/* Target                :   ATmega16 , ATmega32                             */
/* Notes                 :   None                                            */
/*****************************************************************************/

/*****************************************************************************/
/****************************   FILE GUARDE  *********************************/
#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_

/*****************************************************************************/
/**************************** PRIVATE MACROS *********************************/

/****************************************************************************/
/*EXTI ID's.                                                                */
/****************************************************************************/
#define   EXTI0                         0
#define   EXTI1                         1
#define   EXTI2                         2


/****************************************************************************/
/*EXTI MASKING PURPUSES MACRO.                                              */
/****************************************************************************/
#define   EXTI_MASK_BIT                 1


/****************************************************************************/
/*EXTI STATUS.                                                              */
/****************************************************************************/
#define   EXTI_DEACTIVE                 0
#define   EXTI_ACTIVE                   1


/****************************************************************************/
/*EXTI EDGES DETECTION LEVEL.                                               */
/****************************************************************************/
#define   EXTI_RISING_EDGE              0
#define   EXTI_FALLING_EDGE             1
#define   EXTI_LOGIC_CHANGE             2
#define   EXTI_LOW_LEVEL                3


/****************************************************************************/
/* REGISTERS DEFINITION.                                                    */
/****************************************************************************/
#define   MCUCR            (*(volatile u8* const)0x55)
#define   MCUCSR           (*(volatile u8* const)0x54)
#define   GICR             (*(volatile u8* const)0x5B)
#define   GIFR             (*(volatile u8* const)0x5A)

//GICR Bits configuration.
#define   INT1                          7
#define   INT0                          6
#define   INT2                          5

//MCUCR Bits configuration.
#define   ISC11                         3
#define   ISC10                         2
#define   ISC01                         1
#define   ISC00                         0


//MCUCSR Bits configuration.
#define  ISC2                           6


//GIFR Bits configuration.
#define  INTF1                          7
#define  INTF0                          6
#define  INTF2                          5


#endif /* EXTI_PRIV_H_ */
/***************************** END OF FILE. *********************************/
/****************************************************************************/

