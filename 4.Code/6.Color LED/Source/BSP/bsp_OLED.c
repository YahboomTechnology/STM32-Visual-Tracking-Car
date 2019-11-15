/******************** (C) COPYRIGHT 2009 Hangzhou Hikvision Digital Technology Co.,Ltd ********************
* File Name              : gpio.c
* Author                 : AF Application Team
* Date First Issued  : 02/06/2009
* Description        : This file includes the peripherals header files in the user application.
********************************************************************************
* History:
* 02/06/2009: V0.1
********************************************************************************
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC , ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	//OLED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9 |GPIO_Pin_0;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);	  
	GPIO_ResetBits(GPIOC,GPIO_Pin_0); 
} ;

/*******************************************************************************
* Function Name  : void GPIO_UserInit(void)
* Description    : Init  The IO PORT
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_UserInit(void)
{
   GPIO_Configuration();
}


