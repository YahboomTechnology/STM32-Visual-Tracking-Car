
/* Define to prevent recursive inclusion -------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>



//st_systime g_systime = {0, 0};

///*******************************************************************************
//* Function Name   : SYSTICK_init
//* Description     : 
//*                
//* Input            :
//* Output          : None												
//* Return          : None
//*******************************************************************************/
//void SYSTICK_Init(void)
//{

//	/* SysTick end of count event each 1ms with input clock equal to 3MHz (HCLK/8, default) */
//	SysTick_SetReload(3000);
//	#if 0

//	else if(g_mcu_clk == MCU_HCLK_36)
//	{
//		printf("\r\nSysTick_SetReload(4500)");
//		/* SysTick end of count event each 1ms with input clock equal to 3MHz (HCLK/8, default) */
//		SysTick_SetReload(4500);
//	}
//	#endif
//	/* Enable SysTick interrupt */
//	SysTick_ITConfig(ENABLE);
//	/* Enable the SysTick Counter */
//	SysTick_CounterCmd(SysTick_Counter_Enable);
//}

//void SYSTEMTICK_Isr(void)
//{
//	static u16 millisec  = 0;
//	
//	g_systime.millisec++;

//	if(millisec++ >= 1000)
//	{
//		millisec = 0;	
//		g_systime.sec++;
//	} 


//}


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

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void RCC_Configuration(void)
//{
//	ErrorStatus HSEStartUpStatus;
//		
//	/* RCC system reset */
//	RCC_DeInit();

//	/* Enable HSE */
//	RCC_HSEConfig(RCC_HSE_ON);

//	/* Wait till HSE is ready */
//	HSEStartUpStatus = RCC_WaitForHSEStartUp();

//	if (SUCCESS == HSEStartUpStatus)
//	{
//		/* Enable Prefetch Buffer */
//		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

//		/* Flash 2 wait state */
//		FLASH_SetLatency(FLASH_Latency_2);

//		/* HCLK = SYSCLK */
//		RCC_HCLKConfig(RCC_SYSCLK_Div1); 

//		/* PCLK2 = HCLK */
//		RCC_PCLK2Config(RCC_HCLK_Div1); 

//		/* PCLK1 = HCLK */
//		RCC_PCLK1Config(RCC_HCLK_Div1);

//		/* PLLCLK = 8MHz / 2 * 6 = 24 MHz */
//		RCC_PLLConfig(RCC_PLLSource_HSE_Div2, RCC_PLLMul_6);
//		
//		/* Enable PLL */ 
//		RCC_PLLCmd(ENABLE);

//		/* Wait till PLL is ready */
//		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
//		{
//		}

//		/* Select PLL as system clock source */
//		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

//		/* Wait till PLL is used as system clock source */
//		while(RCC_GetSYSCLKSource() != 0x08)					
//		{
//		}
//	}
//		
//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE);
//	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART3, ENABLE);
//	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG, ENABLE);
//	/*Enable  ADC1 */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); 
//}

//void EXTI_Configuration(void)
//{
//    EXTI_InitTypeDef  EXTI_InitStructure;						

//  	
//}

///*******************************************************************************
//* Function Name  : NVIC_Configuration
//* Description    : Configures Vector Table base location.
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void NVIC_Configuration(void)
//{
//	
//	NVIC_InitTypeDef NVIC_InitStructure;
//	#ifdef  VECT_TAB_RAM  							
//	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);  	
//	#else  

//	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0); 
//	#endif
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	  			

//	
//	/* Set SysTick interrupt vector Preemption Priority to 1 */
//	NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 2, 0);
//}

///******************* (C) COPYRIGHT 2009 Hangzhou Hikvision Digital Technology Co.,Ltd *****END OF FILE****/

