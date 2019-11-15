/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_colorful.c	
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief        
* @details      
* @par History  
*                 
* version:		liusen_20170717
*/

#include "bsp_colorful.h"




/**
* Function       bsp_Colorful_Control
* @author        liusen
* @date          2015.01.03    
* @brief         
* @param[in]     v_RedOnOff ,	v_GreenOnOff, v_BlueOnOff
* @param[out]    void
* @retval        void
* @par History   
*/
void bsp_Colorful_Control(int v_RedOnOff, int v_GreenOnOff, int v_BlueOnOff)
{
	if(v_RedOnOff == 1)
	{
		GPIO_SetBits(Colorful_Red_PORT, Colorful_Red_PIN);
	}
	else
	{
		GPIO_ResetBits(Colorful_Red_PORT, Colorful_Red_PIN);
	}

	if(v_GreenOnOff == 1)
	{
		GPIO_SetBits(Colorful_Green_PORT, Colorful_Green_PIN);
	}
	else
	{
		GPIO_ResetBits(Colorful_Green_PORT, Colorful_Green_PIN);
	}

	if(v_BlueOnOff == 1)
	{
		GPIO_SetBits(Colorful_Blue_PORT, Colorful_Blue_PIN);
	}
	else
	{
		GPIO_ResetBits(Colorful_Blue_PORT, Colorful_Blue_PIN);
	}
}


/**
* Function       Motor_PWM_Init
* @author        liusen
* @date          2017.07.17    
* @brief        
* @param[in]     left motor arr£ºAutomatic reload value, psc:Clock prescaler ,right motor arr2£ºAutomatic reload value, psc2:Clock prescaler
* @param[out]    void
* @retval        void
* @par History   no
*/
void Colorful_PWM_Init(u16 arr, u16 psc, u16 arr2, u16 psc2, u16 arr3, u16 psc3 )
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	//Red  PWM1  PB1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM3_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	TIM_Cmd(TIM3, ENABLE); 
	
	//Green  PWM2  PB0
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM4_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = arr2;
	TIM_TimeBaseStructure.TIM_Prescaler = psc2; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	TIM_Cmd(TIM3, ENABLE);  

	//Blue  PWM3  PA7
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM4_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = arr3; 
	TIM_TimeBaseStructure.TIM_Prescaler = psc3; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	TIM_Cmd(TIM3, ENABLE);  
}

/**
* Function       bsp_Colorful_RGB_PWM
* @author        liusen
* @date          2017.08.15    
* @brief         color setting :256*256*256, Converted to 0-1000
* @param[in]     v_RPWM : 0-255 
* @param[out]    void
* @retval        void
* @par History   no
*/
void  bsp_Colorful_RGB_PWM(int v_RPWM, int v_GPWM, int v_BPWM)
{
	float fR = 	v_RPWM * 3.9215f;
	float fG = 	v_GPWM * 3.9215f;
	float fB = 	v_BPWM * 3.9215f;

	TIM_SetCompare4(TIM3, (int)fR); 
	TIM_SetCompare3(TIM3, (int)fG); 
	TIM_SetCompare2(TIM3, (int)fB);
}

