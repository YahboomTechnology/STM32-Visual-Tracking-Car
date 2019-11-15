/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp.c
* @author       liusen
* @version      V1.0
* @date         2015.01.03
* @brief       
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/

#include "bsp.h"
#include "usart.h"
#include "sys.h"
#include "delay.h"
#include "stdio.h"
#include "bsp_oled.h"
#include "OLED.h"
#include "bsp_adc.h"
#include "bsp_ultrasonic.h"


extern void NVIC_Configuration(void); 


/**
* Function       bsp_init
* @author        liusen
* @date          2015.01.03    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void bsp_init(void)
{ 

	MOTOR_GPIO_Init();  				
	Servo_GPIO_Init();				    
	TIM1_Int_Init(9, 72);				
	Uart1_init(115200);					
	Angle_J1 = 90;						
	delay_init();
	NVIC_Configuration(); 	 
	GPIO_UserInit();  
	LCD_Init0();			
	ADC_GPIO_Init();
	Adc_Init();
	Ultrasonic_GPIO_Init();
	bsp_Ultrasonic_Timer2_Init();
	Start_init();
	
}
