/*****************************************************************************/
/*****************************************************************************/
/* Title                 :   EXTI_Cnfg.c                                     */
/* Filename              :   EXTI_Cnfg.c                                     */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Oct 8, 2021                                     */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw GCC                                       */
/* Target                :   ATmega16 , ATmega32                             */
/* Notes                 :   None                                            */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/******************************  INCLUDES  ***********************************/
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\STD_TYPES.h"
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\errorStates.h"

#include "EXTI_priv.h"
#include "EXTI_Cnfg.h"



/***************************************************************************************/
/***************************************************************************************/
/* Description   : Array of EXTI_t type Structures to config. External interrupt in    */
/*                 in the System Using tow Structure Members.                          */
/*                                                                                     */
/* Member Nnm.1  : EXTI_u8State                                                        */
/* Valid Options : EXTI_DEACTIVE                                                       */
/*                 EXTI_ACTIVE                                                         */
/*                                                                                     */
/* Member Nnm.2  : EXTI_u8SenceLevel                                                   */
/* Valid Options : EXTI_RISING_EDGE                                                    */
/*                 EXTI_FALLING_EDGE                                                   */
/*                 EXTI_LOGIC_CHANGE                                                   */
/*                 EXTI_LOW_LEVEL                                                      */
/*                                                                                     */
/*............................**********************************************************/
EXTI_t EXTI_AstrCnfg[EXTI_NUM]=
{
		/****************************************************/
		/**************** INT0 Configuration ****************/
		{
				.EXTI_u8State      =        EXTI_ACTIVE         ,
				.EXTI_u8SenceLevel =        EXTI_FALLING_EDGE   ,
		}
		,

		/****************************************************/
		/**************** INT1 Configuration ****************/
//		{
//				.EXTI_u8State      =        EXTI_ACTIVE         ,
//				.EXTI_u8SenceLevel =        EXTI_FALLING_EDGE   ,
//		}
//		,

		/****************************************************/
		/**************** INT2 Configuration ****************/
//		{
//				.EXTI_u8State      =        EXTI_ACTIVE         ,
//				.EXTI_u8SenceLevel =        EXTI_FALLING_EDGE   ,
//		}
//		,

};

/***************************** END OF FILE. **********************************/
/*****************************************************************************/
