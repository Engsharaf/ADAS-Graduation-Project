/*****************************************************************************/
/* Title                 :   EXTI_interface                                  */
/* Filename              :   EXTI_interface.h                                */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Oct 8, 2021                                     */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw GCC                                       */
/* Target                :   ATmega16 , ATmega32                             */
/* Notes                 :   None                                            */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/**************************   FILE GUARDE  ***********************************/
#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


/****************************************************************************/
/****************************  PUBLIC MACROS  *******************************/
#define   EXTI_0                              0
#define   EXTI_1                              1
#define   EXTI_2                              2


#define   EXTI_DEACTIVE                       0
#define   EXTI_ACTIVE                         1


#define   EXTI_RISING_EDGE                    0
#define   EXTI_FALLING_EDGE                   1
#define   EXTI_LOGIC_CHANGE                   2
#define   EXTI_LOW_LEVEL                      3



/****************************************************************************/
/***************************  PUBLIC FUNCTIONS  *****************************/

/****************************************************************************/
/****************************************************************************/
/* Function Name   : EXTI_enuInit.                                          */
/* Description     : Utility function to initialize the Enabled interrupts. */
/* Argument        : Address array of interrupts .                          */
/* Return          : Error state of type ES_t.                              */
/**............................................******************************/
ES_t   EXTI_enuInit( EXTI_t*  Cpy_pstrEXTICnfg );


/****************************************************************************/
/****************************************************************************/
/*Function Name   : EXTI_enuSetSenceMode.                                   */
/*Description     : Utility function to Set the State of a certain interrupt*/
/*                  during run time .                                       */
/*Argument        : Arg_1:  Interrupt ID that you want to change it state.  */
/*                  =====                                                   */
/*                                                                          */
/*                          Range:                                          */
/*                                 EXTI_0 --->for interrupt_0               */
/*                                 EXTI_1 --->for interrupt_1               */
/*                                 EXTI_2 --->for interrupt_2               */
/*                                                                          */
/*                : Arg_2:  Interrupt Sense level .                         */
/*                  =====                                                   */
/*                          Range:                                          */
/*                                  ->For interrupt 0 & 1                   */
/*                                   RISING_EDGE                            */
/*                                   FALLING_EDGE                           */
/*                                   LOGIC_CHANGE                           */
/*                                   LOW_LEVEL                              */
/*                                                                          */
/*                                 ->For interrupt 2                        */
/*                                  RISING_EDGE                             */
/*                                  FALLING_EDGE                            */
/*                                                                          */
/* Return          : Error state of type ES_t.                              */
/*..........................*************************************************/
ES_t   EXTI_enuSetSenceMode( u8 Cpy_u8EXTI_ID  , u8 Cpy_u8SenceLevel );



/*****************************************************************************/
/*****************************************************************************/
/*Function Name   : EXTI_enuEnableINT.                                       */
/*Description     : Utility function to Enable a certain interrupt           */
/*                  during run time .                                        */
/*Argument        : Arg_1:  Interrupt ID that you want to Enable.            */
/*                  =====                                                    */
/*                                                                           */
/*                          Range:                                           */
/*                                 EXTI_0 --->for interrupt_0                */
/*                                 EXTI_1 --->for interrupt_1                */
/*                                 EXTI_2 --->for interrupt_2                */
/*                                                                           */
/* Return          : Error state of type ES_t.                               */
/*.......................*****************************************************/
ES_t   EXTI_enuEnableINT( u8 Cpy_u8EXTI_ID  );



/*****************************************************************************/
/*****************************************************************************/
/*Function Name   : EXTI_enuDisableINT.                                      */
/*Description     : Utility function to Disable a certain interrupt          */
/*                  during run time .                                        */
/*Argument        : Arg_1:  Interrupt ID that you want to Disable.           */
/*                  =====                                                    */
/*                                                                           */
/*                          Range:                                           */
/*                                 EXTI_0 --->for interrupt_0                */
/*                                 EXTI_1 --->for interrupt_1                */
/*                                 EXTI_2 --->for interrupt_2                */
/*                                                                           */
/* Return          : Error state of type ES_t.                               */
/*.......................*****************************************************/
ES_t   EXTI_enuDisableINT( u8 Cpy_u8EXTI_ID  );



/********************************************************************************************************/
/********************************************************************************************************/
/*Function Name   : EXTI_enuCallBack.                                                                   */
/*Description     : Utility function to initiate the callback.                                          */
/*                                                                                                      */
/*Argument        : Arg_1:  Address function that return void and accept                                */
/*                  =====   pointer or void as argument.                                                */
/*                                                                                                      */
/*                : Arg_2:  Address of the parameter of the passed function.                            */
/*                  =====                                                                               */
/*                                                                                                      */
/*                : Arg_3:  Interrupt ID                                                                */
/*                                                                                                      */
/*                           Range:                                                                     */
/*                                  EXTI_0 --->for interrupt_0                                          */
/*                                  EXTI_1 --->for interrupt_1                                          */
/*                                  EXTI_2 --->for interrupt_2                                          */
/*                                                                                                      */
/*                                                                                                      */
/*                                                                                                      */
/* Return          : Error state of type ES_t.                                                          */
/*.......................********************************************************************************/
ES_t   EXTI_enuCallBack( void (*Cpy_pfunAppFunc)(void) , void* Cpy_pvidParameter ,  u8 Cpy_u8EXTI_ID  );


#endif  //EXTI_INTERFACE_H_

/***************************** END OF FILE. *********************************/
/****************************************************************************/


