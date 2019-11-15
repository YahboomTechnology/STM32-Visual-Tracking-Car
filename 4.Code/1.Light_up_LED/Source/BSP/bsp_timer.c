/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_timer.c
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief        Timer
* @details      
* @par History  
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
* @brief         Timer 1 initialization interface
* @param[in]     arr£ºAutomatic reload value sc£ºClock prescaler
* @param[out]    void
* @retval        void
* @par History   Clock selection is twice that of APB1,  APB1 is 36M   
*/
void TIM1_Int_Init(u16 arr,u16 psc)
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
	
	//  TIM1_Int_Init
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler = (psc-1);   //Set the prescaler value is used to the TIMx clock frequency divisor
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //TDTS = Tck_tim   //36Mhz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;    //Turn off repeat count
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE ); 

	//Interrupt priority NVIC settings
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
* @brief         Timer1 interrupt service program: mainly controls the servo, 10khz counting frequency, counting to 10 means 10us.
* @param[in]     arr£ºAutomatic reload value  £psc£ºClock prescaler
* @param[out]    void
* @retval        void
* @par History   Clock selection is twice that of APB1,  APB1 is 36M   
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
			GPIO_SetBits(Servo_J1_PORT, Servo_J1_PIN );		//Give the servo interface a high level
		}
		else
		{
			GPIO_ResetBits(Servo_J1_PORT, Servo_J1_PIN );		 //Give the servo interface a low level
		}
		#endif	   	


		if(run==1)
		{
			if(num <= speed2)//motor forward
			{
				M1A=0;
				M1B=1;
				M2A=1;
				M2B=0;
			}
			else
			{
				M1A=0;//motor stop
				M1B=0;
				M2A=0;
				M2B=0;
			}
		}
		
		if(run==0)
		{
			if(num <= speed2)//motor  reverse
			{
				M1A=1;
				M1B=0;
				M2A=0;
				M2B=1;
			}
			else
			{
				M1A=0;//motor stop
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




