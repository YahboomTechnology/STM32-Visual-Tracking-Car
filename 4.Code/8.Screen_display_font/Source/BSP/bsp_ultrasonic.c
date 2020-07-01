/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_ultrasonic.C
* @author       liusen
* @version      V1.0
* @date         2017.07.21
*                 
* version:	liusen_20170717
*/

#include "bsp_ultrasonic.h"
#include "stm32f10x.h"
#include "delay.h"


unsigned int overcount = 0;


/**
* Function       bsp_getUltrasonicDistance
* @author        liusen
* @date          2017.07.20    
* @brief         
* @param[in]     void
* @param[out]    void
* @return        
* @par History   
*/

float bsp_getUltrasonicDistance0(void)
{
	float length = 0, sum = 0;
	u16 tim;
	unsigned int  i = 0;

	while(i != 5)
	{
		GPIO_SetBits(TRIG_PORT, TRIG_PIN);  
		delay_us(20);  					//>10us
		GPIO_ResetBits(TRIG_PORT, TRIG_PIN);

		while(GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN) == RESET);
		TIM_Cmd(TIM2,ENABLE);
		
		i+=1;
		while(GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN) == SET);
		TIM_Cmd(TIM2, DISABLE);
		
		tim = TIM_GetCounter(TIM2);
		
		length = (tim + overcount * 1000) / 58.0;
		
		sum = length + sum;
		TIM2->CNT = 0;  
		overcount = 0; 
		delay_ms(1);
	}
	length = sum / 5;
	return length;		
}

/**
* Function       bsp_Ultrasonic_Timer2_Init
* @author        liusen
* @date          2017.07.21         
* @param[in]     void
* @param[out]    void
* @par History   
*/

void bsp_Ultrasonic_Timer2_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructer;
	NVIC_InitTypeDef NVIC_InitStructer;


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	

	TIM_DeInit(TIM2);
	TIM_TimeBaseInitStructer.TIM_Period = 999;
	TIM_TimeBaseInitStructer.TIM_Prescaler = 71; 
	TIM_TimeBaseInitStructer.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructer.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructer);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructer.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructer.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructer.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructer.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructer);
	TIM_Cmd(TIM2, DISABLE);

}

void TIM2_IRQHandler(void) 
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		overcount++;	
	}
}
float bsp_getUltrasonicDistance(void)
{
	float distance = 0;
	u16 tim;
	GPIO_SetBits(TRIG_PORT, TRIG_PIN);  
	delay_us(20);  					
	GPIO_ResetBits(TRIG_PORT, TRIG_PIN);

	while(GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN) == RESET);
	TIM_Cmd(TIM2,ENABLE);
		
	while(GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN) == SET);
	TIM_Cmd(TIM2, DISABLE);
		
	tim = TIM_GetCounter(TIM2);
		
	distance = (tim + overcount * 1000) / 58.0;
		
	TIM2->CNT = 0; 
	overcount = 0;  
	delay_ms(1);
	return distance;		
}


/**
* Function       bubble
* @author        Danny
* @date          2017.08.16
* @param[out]    void
* @retval        void
* @par History   
*/
void bubble(unsigned long *a, int n)

{
  int i, j, temp;
  for (i = 0; i < n - 1; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if (a[i] > a[j])
      {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
    }
  }
}

/**
* Function       Distane_test
* @author        Danny
* @date          2017.08.16
* @param[in]     void
* @param[out]    void
* @retval        float:distance
* @par History   
*/
float Distance_test(void)
{
  float Distance;
  unsigned long ultrasonic[5] = {0};
  int num = 0;
//	int lastDistance;
  while (num < 5)
  {
     Distance = bsp_getUltrasonicDistance();
			 while(((int)Distance >= 500 || (int)Distance == 0))
	 {
		 Distance = bsp_getUltrasonicDistance();
	 }
//	 
//	 while((int)Distance == -1)
//	 {
//		 Distance = bsp_getUltrasonicDistance();
//	 }
   
   /* while ( (~(Distance >= 500 || (int)Distance == 0)) && a<5)
    {
         Distance = bsp_getUltrasonicDistance();
				 a++;
    }
		if(Distance >= 500 || (int)Distance == 0)
		{
			Distance=lastDistance;
		}*/
//		if(Distance<500&&Distance>0)
//		{
//			lastDistance=Distance;
//		}
//		if(Distance >= 500 || (int)Distance == 0)
//			{
//				Distance = 2;
//				//Distance = bsp_getUltrasonicDistance();
//			}
//		if(Distance >= 500 || (int)Distance == 0)
//		{
//			Distance = bsp_getUltrasonicDistance();
//			if(Distance >= 500 || (int)Distance == 0)
//			{
//				Distance = bsp_getUltrasonicDistance();
//				if(Distance >= 500 || (int)Distance == 0)
//				{
//					//Distance = 2;
//					Distance = bsp_getUltrasonicDistance();
//					if(Distance >= 500 || (int)Distance == 0)
//					{
//						//Distance = 2;
//						Distance = bsp_getUltrasonicDistance();
//						if(Distance >= 500 || (int)Distance == 0)
//						{
//							//Distance = 2;
//							Distance = bsp_getUltrasonicDistance();
//						}
//					}
//				}
//			}
//		}
			if(Distance >0 || (int)Distance <500)
			{
				ultrasonic[num] = Distance;
				//lastDistance=Distance;
				num++;
				delay_ms(10);
			}
  
  }
  num = 0;
  bubble(ultrasonic, 5);
  Distance = (ultrasonic[1] + ultrasonic[2] + ultrasonic[3]) / 3;
  return Distance;
  //printf("Distance=%d\n",Distance);
}
