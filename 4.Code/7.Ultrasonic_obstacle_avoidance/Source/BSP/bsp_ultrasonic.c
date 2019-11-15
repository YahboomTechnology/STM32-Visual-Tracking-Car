/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_ultrasonic.C
* @author       liusen
* @version      V1.0
* @date         2017.07.21
* @brief        
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/

#include "bsp_ultrasonic.h"
#include "stm32f10x.h"
#include "delay.h"


/*Record the number of timer overflows*/
unsigned int overcount = 0;


/**
* Function       bsp_getUltrasonicDistance
* @author        liusen
* @date          2017.07.20    
* @brief         Get the distance of the ultrasonic
* @param[in]     void
* @param[out]    void
* @return        Distance floating point value
* @par History   no
*/

float bsp_getUltrasonicDistance0(void)
{
	float length = 0, sum = 0;
	u16 tim;
	unsigned int  i = 0;

	/*Calculate the average value of five times*/
	while(i != 5)
	{
		GPIO_SetBits(TRIG_PORT, TRIG_PIN);  //Pull up the signal as a trigger signal
		delay_us(20);  						//High level signal at least exceeds 10US
		GPIO_ResetBits(TRIG_PORT, TRIG_PIN);

		/*Waiting for the echo signal*/
		while(GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN) == RESET);
		TIM_Cmd(TIM2,ENABLE);//The echo signal arrives and the timer count is turned on.
		
		i+=1; //Every time an echo signal is received, 1 is added, and the average is calculated five times.
		while(GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN) == SET);//Echo signal disappears
		TIM_Cmd(TIM2, DISABLE);//Colse timers
		
		tim = TIM_GetCounter(TIM2);//Get the count value in the TIM2 register and calculate the time of the reverberation signal
		
		length = (tim + overcount * 1000) / 58.0;//count distance
		
		sum = length + sum;
		TIM2->CNT = 0;  //Clear the count value in the TIM2 count register
		overcount = 0;  //Interrupt overflow count is cleared
		delay_ms(1);
	}
	length = sum / 5;
	return length;		
}

/**
* Function       bsp_Ultrasonic_Timer2_Init
* @author        liusen
* @date          2017.07.21    
* @brief         
* @param[in]     void
* @param[out]    void
* @return        
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
* @brief         Ultrasonic measurement of five times of data for bubble sorting
* @param[in1]    a:Ultrasonic array first address
* @param[in2]    n:Size of ultrasonic array 
* @param[out]    void
* @retval        void
* @par History   NO
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
* @brief         Ultrasonic measurement of five times of data, 
                 remove the maximum and minimum values, 
                 and then take the average to improve the accuracy of the test
* @param[in]     void
* @param[out]    void
* @retval        float:distance
* @par History   NO
*/
float Distance_test(void)
{
  float Distance;
  unsigned long ultrasonic[5] = {0};
  int a,num = 0;
	int lastDistance;
  while (num < 5)
  {
     Distance = bsp_getUltrasonicDistance();
			 while(((int)Distance >= 500 || (int)Distance == 0))
	 {
		 Distance = bsp_getUltrasonicDistance();
	 }

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
