/*****************************************************************************/
/* Title                 :   DIO_private                                     */
/* Filename              :   DIO_private.h                                   */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Oct 2, 2021                                     */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw GCC                                       */
/* Target                :   ATmega16 , ATmega32                             */
/* Notes                 :   None                                            */
/*****************************************************************************/

/*****************************************************************************/
/**************************   FILE GUARDE  ***********************************/
#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_



/****************************************************************************/
/*PORT ID's.                                                                */
/****************************************************************************/
#define DIO_PORTA             0
#define DIO_PORTB             1
#define DIO_PORTC             2
#define DIO_PORTD             3


/****************************************************************************/
/*PIS ID's.                                                                 */
/****************************************************************************/
#define DIO_PIN0              0
#define DIO_PIN1              1
#define DIO_PIN2              2
#define DIO_PIN3              3
#define DIO_PIN4              4
#define DIO_PIN5              5
#define DIO_PIN6              6
#define DIO_PIN7              7


/****************************************************************************/
/*PORT OPERATIONS.                                                          */
/****************************************************************************/
#define INPTU_PORT            0x00
#define OUTPUT_PORT           0xFF

/****************************************************************************/
/*PINS OPERATIONS.                                                          */
/****************************************************************************/
#define  INPTU_PIN            0
#define  OUTPUT_PIN           1


/****************************************************************************/
/*PIN STATE.                                                                */
/****************************************************************************/
#define DIO_LOW               0
#define DIO_HIGH              1

/****************************************************************************/
/*PINS CONNECTION STATE.                                                    */
/****************************************************************************/
#define DIO_FLOAT_PIN         0
#define DIO_PULL_UP_PIN       1


/****************************************************************************/
/*DEFINE THE MASK BIT.                                                      */
/****************************************************************************/

#define DIO_MASK_BIT         1

/****************************************************************************/
/* REGISTERS DEFINITION.                                                    */
/****************************************************************************/
#define PORTA (*(volatile u8* const)(0x3B))
#define PORTB (*(volatile u8* const)(0x38))
#define PORTC (*(volatile u8* const)(0x35))
#define PORTD (*(volatile u8* const)(0x32))

#define DDRA  (*(volatile u8* const)(0x3A))
#define DDRB  (*(volatile u8* const)(0x37))
#define DDRC  (*(volatile u8* const)(0x34))
#define DDRD  (*(volatile u8* const)(0x31))

#define PINA  (*(volatile u8 const* const)(0x39))
#define PINB  (*(volatile u8 const* const)(0x36))
#define PINC  (*(volatile u8 const* const)(0x33))
#define PIND  (*(volatile u8 const* const)(0x30))




#endif /* DIO_PRIVATE_H_ */

/***************************** END OF FILE. *********************************/
/****************************************************************************/
