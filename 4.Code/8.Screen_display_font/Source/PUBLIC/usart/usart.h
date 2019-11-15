#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  			200  	
#define EN_USART1_RX 			1		
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; 
extern u16 USART_RX_STA;         		 

extern u8 inputString[80];
extern u8 newLineReceived;
extern int g_packnum;





void Uart1_init(u32 bound);
void Uart2_init(u32 bound);


#endif



