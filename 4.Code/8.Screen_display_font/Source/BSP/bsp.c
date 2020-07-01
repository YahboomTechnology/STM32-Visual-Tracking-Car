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

#include "exti.h"
#include "ov7670.h"
#include "lcd.h"
#include "led.h"
#include "usart.h"
#include "sys.h"
#include "delay.h"
#include "bsp.h"
#include "stdio.h"


extern void NVIC_Configuration(void); 
void LCD_Init0(void);
void GPIO_UserInit(void);


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
	Start_init();
	MOTOR_GPIO_Init();  			
	Servo_GPIO_Init();				  
	TIM1_Int_Init(9, 72);				
	Ultrasonic_GPIO_Init();			
	bsp_Ultrasonic_Timer2_Init();		
	Uart1_init(115200);					
	Angle_J1 = 79;						
	delay_init();
	NVIC_Configuration(); 	 
	while(OV7670_Init());
	EXTI8_Init();						
  OV7670_CS=0;			
	config_ov7670_OutPut(20,60,320,240,1);
	GPIO_UserInit();
	LCD_Init0();
	
}
