/*
 * GIE_prog.c
 *
 *  Created on: Oct 13, 2021
 *      Author: Shaban
 */

#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\STD_TYPES.h"
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\errorStates.h"

#include "E:\NTI\AVR\ATmeg16_Drivers\MCAL\GIE\GIE_priv.h"


ES_t GIE_enuEnable( void )
{
	ES_t Local_enuErrorState = ES_NOK ;

	SREG  |=(GIE_MASK_BIT<<I);


	return Local_enuErrorState ;
}
ES_t GIE_enuDisable( void )
{
	ES_t Local_enuErrorState = ES_NOK ;

	SREG  &=~(GIE_MASK_BIT<<I);



	return Local_enuErrorState ;
}
