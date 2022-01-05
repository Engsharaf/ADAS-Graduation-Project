



#ifndef  USART_PRIVATE_H
#define  USART_PRIVATE_H

/* UDR : I/O  Data Register*/ 
#define   UDR          (*(volatile u8* const)0X2C)

/* UDR : USART Baud Rate HIGH Register*/ 
#define   UBRRH          (*(volatile u8* const)0X40)

/* UDR : USART Baud Rate LOW Register*/
#define   UBRRL          (*(volatile u8* const)0X29)

/* UDR : USART Control and Status Register A */
#define   UCSRA          (*(volatile u8* const)0X2B)

/* UDR : USART Control and Status Register B */
#define   UCSRB          *((volatile u8 *) 0X2A)

/* UDR : USART Control and Status Register C */
#define   UCSRC          (*(volatile u8* const)0X40)

#endif