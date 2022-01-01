/*****************************************************************************/
/*****************************************************************************/
/* Title                 :   TIMER_Prog                                      */
/* Filename              :   TIMER_Prog.c                                    */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Oct 29, 2021                                    */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw GCC                                       */
/* Target                :   ATmega16 , ATmega32                             */
/* Notes                 :   None                                            */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/*******************************  INCLUDES  **********************************/
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\STD_TYPES.h"
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\errorStates.h"

#include "E:\NTI\AVR\ATmeg16_Drivers\MCAL\interrupt.h"

#include "TIMER_Priv.h"
#include "TIMER_Cnfg.h"

/*****************************************************************************************/
/* Description   : Tow global array of pointers to store the Addresses of the functions  */
/*                 that passed from application layer throw pointer to function and its  */
/*                 arguments for usage in CallBack.                                      */
/*****************************************************************************************/
volatile static void (*TIMER_pvidAppFunc[NUM_OF_TIMER])(void*) = { NULL , NULL , NULL } ;
volatile static void*  TIMER_pvidAppPara[NUM_OF_TIMER]         = { NULL , NULL , NULL } ;


/*****************************************************************************************/
/* Description   : Tow global array of pointers to store the Timers Addresses.           */
/*****************************************************************************************/
static TIMER_t* TIMER_ApenuTIMER[NUM_OF_TIMER]={ NULL , NULL , NULL };


volatile static u32 TIMER_u32NumOfOVF[NUM_OF_TIMER]= { 0 , 0 , 0 };

volatile static u8  TIMER_u8Preload[NUM_OF_TIMER]= { 0 , 0 , 0 };


ES_t TIMER_enuInit(TIMER_t* Cpy_pstrtTimerCnfg )
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( Cpy_pstrtTimerCnfg != NULL )
	{
		u8 Local_u8Iterator = 0 ;

		for( ;Local_u8Iterator < TIMER_NUM ; Local_u8Iterator++ )
		{

			switch( Local_u8Iterator )
			{

			case TIMER0 :
				/*======================== Timer0 ============================*/
				/*======================== Timer0 ============================*/
				/*======================== Timer0 ============================*/
				/*======================== Timer0 ============================*/

				TIMER_ApenuTIMER[TIMER0] = &Cpy_pstrtTimerCnfg[TIMER0];
				/*************************************************************/
				/* Timer0 Waveform Generation Mode Cases Handling.           */
				/*************************************************************/
				switch( Cpy_pstrtTimerCnfg[TIMER0].TIMER_u8Mode )
				{

				case OVF :

					/*************************************************************/
					/*  Clear WGM01 and WGM00 Bits To Engage OVF Mode according  */
					/*  to data sheet.                                           */
					/*************************************************************/
					TCCR0 &=~( (TIMER_MSK_BIT<<WGM00)|(TIMER_MSK_BIT<<WGM01) );

					/*************************************************************/
					/*  Set the Force Output Compare Bit in Non-PWM Mode.        */
					/*************************************************************/
					TCCR0 |=(TIMER_MSK_BIT<<FOC0);



					/*************************************************************/
					/*  OC0 Cases Handling in Over flow (non-PWM) Mode.          */
					/*************************************************************/
					switch( Cpy_pstrtTimerCnfg[TIMER0].TIMER_u8OC0_State )
					{

					TCCR0 &=~( (TIMER_MSK_BIT<<COM00) | (TIMER_MSK_BIT<<COM01) );

					case DISCONNECTED :
						break;

					case TOGGLE_ON_COMP_MATCH:
						TCCR0 |=(TIMER_MSK_BIT<<COM00);
						break;

					case CLAER_ON_COMP_MATCH:
						TCCR0 |=(TIMER_MSK_BIT<<COM01);
						break;

					case SET_ON_COMP_MATCH:
						TCCR0 |=( (TIMER_MSK_BIT<<COM00) | (TIMER_MSK_BIT<<COM01) );
						break;


					}//End of  OC0 Cases Handling in Over flow (non-PWM) Mode.


					/*************************************************************/
					/* Set the initial preload in TCNT0 Register.                */
					/*************************************************************/
					//TCNT0 = Cpy_pstrtTimerCnfg[TIMER0].TIMER_u8SetPreload ;




					break;  // End of OVF Case.

					case PWM :

						TCCR0 |=(TIMER_MSK_BIT<<WGM00);

						//Clear the Force Output Compare Bit.
						TCCR0 &=~(TIMER_MSK_BIT<<FOC0);

						break;

					case CTC :
						TCCR0 |=(TIMER_MSK_BIT<<WGM01);
						break;

					case FAST_PWM :
						TCCR0 |=( (TIMER_MSK_BIT<<WGM00)|(TIMER_MSK_BIT<<WGM01)  );
						break;

				}//End of Generation modes Handling.




				break;
				/*====================== End of Timer0 =========================*/
				/*====================== End of Timer0 =========================*/
				/*====================== End of Timer0 =========================*/
				/*====================== End of Timer0 =========================*/


				case TIMER1 :
					break;

				case TIMER2 :
					break;

			}

			Local_enuErrorState = ES_OK ;

		} // End of for the iterate to initiate timers.
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER ;

	}

	return Local_enuErrorState ;

}// End of TIMER_enuInit .

//static volatile void (*TIMER_pvidAppFunc)(void*) = NULL ;
//static volatile void* TIMER_pvidAppPara           = NULL ;

//TIMER_enuSetAsyncDelay( &Copy_pstrTIMER[TIMER0] , 100 , NULL , NULL)
/*==================================================================================================**/
/*==================================================================================================**/
/*==================================================================================================**/
/*==================================================================================================**/
/*==================================================================================================**/
/*==================================================================================================**/
ES_t TIMER_enuSetAsyncDelay( u8 Copy_u8TimerID ,u32 Copy_u32Time ,void (*Copy_pfunApp)(void*) ,void* Copy_pvidParameter )
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( Copy_u8TimerID <= TIMER2 )
	{

		// void (*TIMER_pvidAppFunc[NUM_OF_TIMER])(void*) = { NULL , NULL , NULL } ;
		//void* TIMER_pvidAppPara[NUM_OF_TIMER]          = { NULL , NULL , NULL } ;

		if( Copy_pfunApp != NULL  )
		{
			switch(Copy_u8TimerID )
			{
			/*=======================================================================*/
			case TIMER0:

				TIMER_pvidAppFunc[TIMER0] = Copy_pfunApp       ;
				TIMER_pvidAppPara[TIMER0] = Copy_pvidParameter ;

				/***********************************************************************************************************************************/
				/* Calculate the time taken by Timer0 to count from 0 to overflow (256).                                                           */
				/***********************************************************************************************************************************/
				f32 Local_f32OVFTime = 256 * ((f32)((TIMER_ApenuTIMER[TIMER0]->TIMER_u16Prescaler))/(TIMER_ApenuTIMER[TIMER0]->TIMER_u16Freq_in_khz));

				/*********************************************************************/
				/* Calculate the number of OVF's that will occur in the desired time.*/
				/*********************************************************************/
				f32 Local_u8NumOfOVF = (Copy_u32Time/Local_f32OVFTime);

				/*********************************************************************/
				/* Fraction number case Handling.                                    */
				/*********************************************************************/
				if( (Local_u8NumOfOVF - ((u32)Local_u8NumOfOVF) ) != 0.0)
				{

					/* Calculate the integer number of overflows.   */
					u32  Local_u32IntNumOfOVF=(u32)(Local_u8NumOfOVF+1);

					/**/TIMER_u32NumOfOVF[TIMER0] = Local_u32IntNumOfOVF ;



					/* Get the Fraction number of overflows.*/
					Local_u8NumOfOVF -= (u32)Local_u8NumOfOVF;

					/* Calculate the Preload or the Offset value.  */
					u8 Local_u8Preload = 256 - ( 256 * Local_u8NumOfOVF );

					/* Push the preload value in TCNT0 register.*/

					/**/TIMER_u8Preload[TIMER0] = Local_u8Preload ;


					TCNT0 = Local_u8Preload ;



					TIMSK |= ( TIMER_MSK_BIT<<TOIE0 );

					//TIMER_enuInit(TIMER_t* Cpy_pstrtTimerCnfg );
					/*******************************************************************/
					/* Set the Clock Select Bits according to init. PRESCALER value.   */
					/*******************************************************************/

					TIMER_vidStaticInline_SetPrescaler(Copy_u8TimerID );

				}
				/***********************************************************************************************************************************/
				/* The number of OVF's is integer value, Hence there is no need to calculate preload value.                                        */
				/***********************************************************************************************************************************/
				else
				{
					u32 Local_u32IntNumOfOVF =(u32)(Local_u8NumOfOVF);

					/*******************************************************************/
					/* Set the Clock Select Bits according to init. PRESCALER value.   */
					/*******************************************************************/
					TIMER_u32NumOfOVF[TIMER0] = Local_u32IntNumOfOVF ;


					TIMSK |= ( TIMER_MSK_BIT<<TOIE0 );

					TIMER_vidStaticInline_SetPrescaler( Copy_u8TimerID );


				}


				break;

				/*=========================================================================*/
			case TIMER1:
				TIMER_pvidAppFunc[TIMER1] = Copy_pfunApp       ;
				TIMER_pvidAppPara[TIMER1] = Copy_pvidParameter ;

				break;

			case TIMER2:
				TIMER_pvidAppFunc[TIMER2] = Copy_pfunApp       ;
				TIMER_pvidAppPara[TIMER2] = Copy_pvidParameter ;

				break;

			}//End of switch().

			Local_enuErrorState = ES_OK;
		}
		else
		{
			Local_enuErrorState = ES_NULL_POINTER ;
		}
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE ;
	}


	return Local_enuErrorState ;
}// End of TIME0_enuSetAsyncDelay .


/*==================================================================================================**/
/*==================================================================================================**/
/*==================================================================================================**/
/*==================================================================================================**/
/*==================================================================================================**/
/*==================================================================================================**/
ES_t TIMER_enuSetSyncDelay(u8 Copy_u8TimerID , u32 Copy_u32Time)
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( Copy_u8TimerID <= TIMER2 )
	{
		if( Copy_u8TimerID == TIMER0 )
		{

			/***********************************************************************************************************************************/
			/* Calculate the time taken by Timer0 to count from 0 to overflow (256).                                                           */
			/***********************************************************************************************************************************/
			f32 Local_f32OVFTime = 256 * ((f32)((TIMER_ApenuTIMER[TIMER0]->TIMER_u16Prescaler))/(TIMER_ApenuTIMER[TIMER0]->TIMER_u16Freq_in_khz));

			/*********************************************************************/
			/* Calculate the number of OVF's that will occur in the desired time.*/
			/*********************************************************************/
			f32 Local_u8NumOfOVF = (Copy_u32Time/Local_f32OVFTime);

			/*********************************************************************/
			/* Fraction number case Handling.                                    */
			/*********************************************************************/
			if( (Local_u8NumOfOVF - ((u32)Local_u8NumOfOVF) ) != 0.0)
			{

				/* Calculate the integer number of overflows.   */
				u32 Local_u32IntNumOfOVF =(u32)(Local_u8NumOfOVF+1);

				/* Get the Fraction number of overflows.*/
				Local_u8NumOfOVF -= (u32)Local_u8NumOfOVF;

				/* Calculate the Preload or the Offset value.  */
				u8 Local_u8Preload = 256 - ( 256 * Local_u8NumOfOVF );

				/* Push the preload value in TCNT0 register.*/
				TCNT0 = Local_u8Preload ;



				//TIMER_enuInit(TIMER_t* Cpy_pstrtTimerCnfg );
				/*******************************************************************/
				/* Set the Clock Select Bits according to init. PRESCALER value.   */
				/*******************************************************************/

				TIMER_vidStaticInline_SetPrescaler(Copy_u8TimerID );


				/********************************************************************************************/
				/* The number of OVF's is integer value, Hence there is no need to calculate preload value. */
				/********************************************************************************************/
				while( Local_u32IntNumOfOVF  > 0 )
				{

					// Stop while the flag is set.
					while( ((TIFR>>TOV0) & TIMER_MSK_BIT) == 0 );

					// Clear the flag.
					TIFR |=(TIMER_MSK_BIT<<TOV0);

					//Decrement the number of OVF's.
					Local_u32IntNumOfOVF-- ;

				}

			}

			/***********************************************************************************************************************************/
			/* The number of OVF's is integer value, Hence there is no need to calculate preload value.                                        */
			/***********************************************************************************************************************************/
			else
			{
				u32 Local_u32IntNumOfOVF =(u32)(Local_u8NumOfOVF);

				/*******************************************************************/
				/* Set the Clock Select Bits according to init. PRESCALER value.   */
				/*******************************************************************/


				TIMER_vidStaticInline_SetPrescaler( Copy_u8TimerID );


				/*******************************************************************/
				/* Count the number of OVF's time to calculate the desired time.   */
				/*******************************************************************/
				while( Local_u32IntNumOfOVF > 0 )
				{

					/* Stuck the code while the flag is not set.     */
					while(  ((TIFR>>TOV0) & TIMER_MSK_BIT)==0 );

					/* Clear the flag.         */
					TIFR |=(TIMER_MSK_BIT<<TOV0);

					/* Increment the number of OVF's*/
					Local_u32IntNumOfOVF-- ;

				}

			}

			Local_enuErrorState = ES_OK ;

		}

		Local_enuErrorState = ES_OK ;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}


	return Local_enuErrorState ;
}// End of TIME0_enuSetSyncDelay .


/*==================================================================================================**/
/*==================================================================================================**/
void static inline TIMER_vidStaticInline_SetPrescaler( u8 Copy_u8TimerID )
{


	/*******************************************************************/
	/* Set the Clock Select Bits according to init. PRESCALER value.   */
	/*******************************************************************/

	/* Clear Clock select Bits at the beginning .                                  */
	TCCR0 &=~(  (TIMER_MSK_BIT<<CS00)|(TIMER_MSK_BIT<<CS01)|(TIMER_MSK_BIT<<CS02)  );

	/* Configure timer to use 1024 prescaler.                   */
	if(TIMER_ApenuTIMER[TIMER0]->TIMER_u16Prescaler == PRES_1024)
	{
		TCCR0 |=( (TIMER_MSK_BIT<<CS00)|(TIMER_MSK_BIT<<CS02) );
	}

	/* Configure timer to use 256 prescaler.                    */
	else if(TIMER_ApenuTIMER[TIMER0]->TIMER_u16Prescaler == PRES_256)
	{
		TCCR0 |=(TIMER_MSK_BIT<<CS02);
	}

	/* Configure timer to use 64 prescaler.                      */
	else if(TIMER_ApenuTIMER[TIMER0]->TIMER_u16Prescaler == PRES_64)
	{
		TCCR0 |=( (TIMER_MSK_BIT<< CS00)|(TIMER_MSK_BIT<< CS01) );
	}

	/* Configure timer to use 8 prescaler.                       */
	else if(TIMER_ApenuTIMER[TIMER0]->TIMER_u16Prescaler == PRES_8)
	{
		TCCR0 |=(TIMER_MSK_BIT<< CS01);
	}

	/* Configure timer to use 1 prescaler (No prescalling) .     */
	else if(TIMER_ApenuTIMER[TIMER0]->TIMER_u16Prescaler == PRES_1)
	{
		TCCR0 |=(TIMER_MSK_BIT<< CS00);
	}
	else
	{
		// Do nothing.
	}
	// End of prescaler cases handling.




}





/*==================================================================================================**/
/*==================================================================================================**/
/*==================================================================================================**/
/*==================================================================================================**/
/*  (*TIMER_pvidAppFunc[NUM_OF_TIMER])(void*) =      */
ISR(VECT_TIMER0_OVF)
{
	if( TIMER_pvidAppFunc[TIMER0] != NULL)
	{
		static u32 Local_u32Conts = 0 ;

		Local_u32Conts++ ;

		if( Local_u32Conts == TIMER_u32NumOfOVF[TIMER0] )
		{

			TCNT0 = TIMER_u8Preload[TIMER0] ;

			TIMER_pvidAppFunc[TIMER0](TIMER_pvidAppPara[TIMER0]);


			Local_u32Conts = 0 ;


		}
		else
		{

		}

	}

}
