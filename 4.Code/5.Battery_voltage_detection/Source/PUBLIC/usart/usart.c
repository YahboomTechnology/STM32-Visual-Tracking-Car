/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         usart.c	
* @author       liusen
* @version      V1.0
* @date         2015.01.03
* @brief        
* @details      uart_init	USART1_IRQHandler
* @par History  
*                 
* version:		liusen	20150103 20170717
*/


#include "sys.h"
#include "usart.h"
	  


	

u8 newLineReceived = 0;
u8 inputString[80] = {0};  
 
 
#if 1
#pragma import(__use_no_semihosting)             
                
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
   
_sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);
    USART1->DR = (u8) ch;      
	return ch;
}

#endif 

/*
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}

 */
#if EN_USART1_RX   

u8 USART_RX_BUF[USART_REC_LEN];     

u16 USART_RX_STA=0;       

/**
* Function       uart1_init
* @author        liusen
* @date          2015.01.03    
* @brief         
* @param[in]     bound 
* @param[out]    void
* @retval        void
* @par History   
*/
 
 void Uart1_init(u32 bound){
  
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);
   
  //USART1_RX	  GPIOA.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //Usart1 NVIC 
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
  

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART1, &USART_InitStructure); 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART1, ENABLE);                    

}

/**
* Function       Uart2_init
* @author        liusen
* @date          2015.01.03    
* @brief         
* @param[in]     bound 
* @param[out]    void
* @retval        void
* @par History   
*/
 
void Uart2_init(u32 bound){
  	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	 
	//USART2_TX   GPIOA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//USART2_RX	  GPIOA.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Usart1 NVIC 
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	
	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	
	USART_Init(USART2, &USART_InitStructure); 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);                    

}

/**
* Function       USART1_IRQHandler
* @author        liusen
* @date          2015.01.03    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void UART1SendByte(unsigned char SendData)
{
    USART_SendData(USART1, SendData);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}
void USART1_IRQHandler(void)                	
	{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
		{
		Res =USART_ReceiveData(USART1);	
		
		if((USART_RX_STA&0x8000)==0)
			{
			if(USART_RX_STA&0x4000)
				{
				if(Res!=0x0a)USART_RX_STA=0;
				else USART_RX_STA|=0x8000;	
				}
			else 
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;
					}		 
				}
			}   		 
     } 
#if SYSTEM_SUPPORT_OS 	
	OSIntExit();  											 
#endif
} 
#endif	

/**
* Function       USART2_IRQHandler
* @author        liusen
* @date          2015.01.03    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/

int g_num = 0;
u8 startBit = 0;
int g_packnum = 0;

void USART2_IRQHandler(void)
{
	u8 uartvalue = 0;

	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)
    {  
		USART_ClearFlag(USART2, USART_FLAG_ORE); 
       	USART_ReceiveData(USART2);  		
    }
		
	if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE)!=RESET)
	{
    	USART_ClearITPendingBit(USART2, USART_IT_RXNE);

		uartvalue = USART2->DR;
	    if(uartvalue == '$')
	    {
	      	startBit = 1;
		    g_num = 0;
	    }
	    if(startBit == 1)
	    {
	       	inputString[g_num] = uartvalue;     
	    }  
	    if (startBit == 1 && uartvalue == '#') 
	    {
	    	
			newLineReceived = 1; 
			startBit = 0;
			g_packnum = g_num;	
		
	    }
		g_num++;
		if(g_num >= 80)
		{
			g_num = 0;
			startBit = 0;
			newLineReceived	= 0;
		}	 
	
	}

} 
	
