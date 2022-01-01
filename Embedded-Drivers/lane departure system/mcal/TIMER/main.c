/*
 * main.c
 *
 *  Created on: Oct 29, 2021
 *      Author: Shaban
 */
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\STD_TYPES.h"
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\errorStates.h"


#include "E:\NTI\AVR\ATmeg16_Drivers\MCAL\GIE\GIE_interface.h"


#include "TIMER_Cnfg.h"
#include "TIMER_interface.h"

#define DDRD (*((volatile u8* const)0x31))
#define PORTD (*((volatile u8* const)0x32))


void tog(void* P)
{
	PORTD ^=(1<<0);
}

int main(void)
{


	DDRD |=(1<<0);

	PORTD |=(1<<0);

	GIE_enuEnable(  );

	TIMER_enuInit(TIMRE_AstrCnfg);

	TIMER_enuSetAsyncDelay( TIMER0 ,3000 , tog ,NULL );

	PORTD &=~(1<<0);

	while(1)
	{

	}
}


