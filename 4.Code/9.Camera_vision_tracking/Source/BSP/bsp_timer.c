/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_timer.h	
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief        
* @details      
* @par History  
*                 
* version:		liusen_20170717
*/


#include "bsp_timer.h"
#include "bsp_servo.h"
#include "bsp.h"
#include "app_motor.h"

extern int run;


/**
* Function       TIM1_Int_Init
* @author        liusen
* @date          2015.01.03    
* @brief         
* @param[in]     arr£ºAutomatic reload value¡£psc£ºClock prescaler
* @param[out]    void
* @retval        void
* @par History   
*/
void TIM1_Int_Init(u16 arr,u16 psc)
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler = (psc-1); 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE ); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  


	TIM_Cmd(TIM1, ENABLE); 
}
/**
* Function       TIM1_Int_Init
* @author        liusen
* @date          2015.01.03    
* @brief         
* @param[in]     arr£ºAutomatic reload value¡£psc£ºClock prescaler
* @param[out]    void
* @retval        void
* @par History   
*/
int num = 0;	 
long g_count = 0; 
int speed2=0;
extern int speed;
void TIM1_UP_IRQHandler(void)   
{
	speed2=speed*2;
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  
		num++;
		g_count++;
	
		#ifdef USE_SERVO_J1
		if(num <= (Angle_J1 * 11 + 500)/10)
		{
			GPIO_SetBits(Servo_J1_PORT, Servo_J1_PIN );		
		}
		else
		{
			GPIO_ResetBits(Servo_J1_PORT, Servo_J1_PIN );		
		}
		#endif	   	

		#ifdef USE_SERVO_J2
		if(num <= (Angle_J2 * 11 + 500)/10)
		{
			GPIO_SetBits(Servo_J2_PORT, Servo_J2_PIN );		
		}
		else
		{
			GPIO_ResetBits(Servo_J2_PORT, Servo_J2_PIN );		
		}
		#endif

		#ifdef USE_SERVO_J3

		if(num <= (Angle_J3 * 11 + 500)/10)
		{
			GPIO_SetBits(Servo_J3_PORT, Servo_J3_PIN );		
		}
		else
		{
			GPIO_ResetBits(Servo_J3_PORT, Servo_J3_PIN );		
		}
		#endif

		#ifdef USE_SERVO_J4
		if(num <= (Angle_J4 * 11 + 500)/10)
		{
			GPIO_SetBits(Servo_J4_PORT, Servo_J4_PIN );		
		}
		else
		{
			GPIO_ResetBits(Servo_J4_PORT, Servo_J4_PIN );		
		}
		#endif

		#ifdef USE_SERVO_J5
		if(num <= (Angle_J5 * 11 + 500)/10)
		{
			GPIO_SetBits(Servo_J5_PORT, Servo_J5_PIN );		
		}
		else
		{
			GPIO_ResetBits(Servo_J5_PORT, Servo_J5_PIN );		
		}
		#endif

		#ifdef USE_SERVO_J6
		if(num <= (Angle_J6 * 11 + 500)/10)
		{
			GPIO_SetBits(Servo_J6_PORT, Servo_J6_PIN );		
		}
		else
		{
			GPIO_ResetBits(Servo_J6_PORT, Servo_J6_PIN );		
		}
		#endif
		
		if(run==1)
		{
			if(num <= speed2)
			{
				M1A=0;
				M1B=1;
				M2A=1;
				M2B=0;
			}
			else
			{
				M1A=0;
				M1B=0;
				M2A=0;
				M2B=0;
			}
		}
		if(run==0)
		{
			if(num <= speed2)
			{
				M1A=1;
				M1B=0;
				M2A=0;
				M2B=1;
			}
			else
			{
				M1A=0;
				M1B=0;
				M2A=0;
				M2B=0;
			}
		}
		if(num == 2000) //2000*10us = 20ms 
		{
			num = 0;
		}		
		
	}
	
}



