#include "exti.h"
#include "delay.h"
#include "usart.h"
#include "ov7670.h"

 //ov_sta:0,Start a frame of data collection
u8 ov_sta;
  //  External interrupt 5~9 service program
void EXTI9_5_IRQHandler(void)
{		 		
 
	if(EXTI_GetITStatus(EXTI_Line8)==SET)// 8 interrupt service program
	{     
		if(ov_sta<2)
		{
			if(ov_sta==0)
			{
				
				OV7670_WREN=1;		
				OV7670_WRST=0;	 	 
				OV7670_WRST=1;	
				
			}else 
			{
				OV7670_WREN=0;		
				OV7670_WRST=0;	 	  		 
				OV7670_WRST=1;	
				
			}
			ov_sta++;
		}
	}
 
	EXTI_ClearITPendingBit(EXTI_Line8);  		  
} 
//External interrupt 8 initialization
void EXTI8_Init(void)
{   
	  EXTI_InitTypeDef EXTI_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
 	   	 
	  EXTI_InitStructure.EXTI_Line=EXTI_Line8;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
  	NVIC_Init(&NVIC_InitStructure);  	  
   
}


