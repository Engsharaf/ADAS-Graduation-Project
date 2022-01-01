/*****************************************************************************/
/* Title                 :   DIO_interface                                   */
/* Filename              :   DIO_interface.h                                 */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Oct 2, 2021                                     */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw GCC                                       */
/* Target                :   ATmega16 , ATmega32                             */
/* Notes                 :   None                                            */
/*                                                                           */
/*****************************************************************************/


/****************************************************************************/
/**************************   FILE GUARDE  **********************************/
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


/****************************************************************************/
/************************** PUBLIC MACROS. **********************************/


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
#define DIO_INPTU_PORT        0x00
#define DIO_OUTPUT_PORT       0XFF



/****************************************************************************/
/*PINS OPERATIONS.                                                          */
/****************************************************************************/
#define DIO_INPTU_PIN        0
#define DIO_OUTPUT_PIN       1


/****************************************************************************/
/*PIN STATE.                                                                */
/****************************************************************************/
#define DIO_LOW              0
#define DIO_HIGH             1

/****************************************************************************/
/*PINS CONNECTION STATE.                                                    */
/****************************************************************************/
#define DIO_FLOAT_PIN        0
#define DIO_PULL_UP_PIN      1


/****************************************************************************/
/************************* PUBLIC FUNCTIONS. ********************************/

/****************************************************************************/
/* Function Name   : DIO_enuSetPortDirection.                               */
/* Description     : This function used for Setting port direction.         */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                                                          */
/*                 : Arg.2: Copy_u8Dir:                                     */
/*                                        DIO_INPTU_PIN  ,   DIO_OUTPUT_PIN */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuSetPortDirection(u8 Copy_u8PortID, u8 Copy_u8Dir);



/****************************************************************************/
/* Function Name   : DIO_enuSetPortValue.                                   */
/* Description     : This function used for Setting port value.             */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                                                          */
/*                 : Arg.2: Copy_u8Val:                                     */
/*                                        DIO_INPTU_PIN  ,  DIO_OUTPUT_PIN  */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuSetPortValue(u8 Copy_u8PortID, u8 Copy_u8Val);



/****************************************************************************/
/* Function Name   : IO_enuToggelPort.                                      */
/* Description     : This function used for toggling the entire port.       */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuToggelPort(u8  Copy_u8PortID );



/****************************************************************************/
/* Function Name   : DIO_enuGetPortVlaue.                                   */
/* Description     : This function reads a specific port and put the value  */
/*                   in a variable through pointer to unsigned char.        */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                                                          */
/*                 : Arg.2: Address of u8 variable.                         */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuGetPortVlaue(u8 Copy_u8PortID, u8* Copy_pu8PortVal);




/****************************************************************************/
/* Function Name   : DIO_enuSetPinDirection.                                */
/* Description     : This function is used for setting a certain pin in     */
/*                   a certain port.                                        */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                 : Arg.2: Copy_u8PinID:                                   */
/*                                        DIO_PIN0       ,   DIO_PIN4       */
/*                                        DIO_PIN1       ,   DIO_PIN5       */
/*                                        DIO_PIN2       ,   DIO_PIN6       */
/*                                        DIO_PIN3       ,   DIO_PIN7       */
/*                                                                          */
/*                 : Arg.3: Copy_u8Dir.                                     */
/*                                       DIO_INPTU_PIN   ,   DIO_OUTPUT_PIN */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuSetPinDirection(u8 Copy_u8PortID, u8 Copy_u8PinID , u8 Copy_u8Dir);




/****************************************************************************/
/* Function Name   : DIO_enuSetPinValue.                                    */
/* Description     : This function used for Set a specific pin to high level*/
/*                   or low level.                                          */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                 : Arg.2: Copy_u8PinID:                                   */
/*                                        DIO_PIN0       ,   DIO_PIN4       */
/*                                        DIO_PIN1       ,   DIO_PIN5       */
/*                                        DIO_PIN2       ,   DIO_PIN6       */
/*                                        DIO_PIN3       ,   DIO_PIN7       */
/*                 : Arg.3: Copy_u8Val.                                     */
/*                                        DIO_LOW        ,   DIO_HIGH       */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuSetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID ,u8 Copy_u8Val);




/****************************************************************************/
/* Function Name   : DIO_enuToggelPin.                                      */
/* Description     : This function inverse the value of the specific pin.   */
/* Arguments       : Arg.1: Copy_u8PortID:                                  */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                        DIO_PORTA      ,   DIO_PORTA      */
/*                                                                          */
/*                 : Arg.2: Copy_u8PinID:                                   */
/*                                        DIO_PIN0       ,   DIO_PIN4       */
/*                                        DIO_PIN1       ,   DIO_PIN5       */
/*                                        DIO_PIN2       ,   DIO_PIN6       */
/*                                        DIO_PIN3       ,   DIO_PIN7       */
/* Return          : ERROR_STATE eum.                                       */
/****************************************************************************/
ES_t DIO_enuToggelPin(u8  Copy_u8PortID, u8 Copy_u8PinID  );




/*********************************************************************************/
/* Function Name   : DIO_enuGetPinVlaue.                                         */
/* Description     : This function used for getting a specific pin value         */
/*                   and write this value in variable through pointer to u8.     */
/* Arguments       : Arg.1: Copy_u8PortID:                                       */
/*                                        DIO_PORTA      ,   DIO_PORTA           */
/*                                        DIO_PORTA      ,   DIO_PORTA           */
/*                 : Arg.2: Copy_u8PinID:                                        */
/*                                        DIO_PIN0       ,   DIO_PIN4            */
/*                                        DIO_PIN1       ,   DIO_PIN5            */
/*                                        DIO_PIN2       ,   DIO_PIN6            */
/*                                        DIO_PIN3       ,   DIO_PIN7            */
/*                                                                               */
/*                 : Arg.3: Address of u8 variable.                              */
/*                                                                               */
/* Return          : ERROR_STATE eum.                                            */
/*********************************************************************************/
ES_t DIO_enuGetPinVlaue(u8 Copy_u8PortID , u8 Copy_u8PinID , u8* Copy_pu8PinVal);


#endif /* DIO_INTERFACE_H_ */


/***************************** END OF FILE. *********************************/
/****************************************************************************/