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


extern void NVIC_Configuration(void); 


/**
* Function       bsp_init
* @author        liusen
* @date          2015.01.03    
* @brief          Hardware device initialization   
* @param[in]     void
* @param[out]    void
* @retval        void

* @par History   no
*/
void bsp_init(void)
{ 
	MOTOR_GPIO_Init();  				/* motor GPIO initialization*/
	Servo_GPIO_Init();				  /*servo inetrface GPIO initialization*/
	TIM1_Int_Init(9, 72);				/*100Khz Counting frequency,10 times = 10us*/
	Uart1_init(115200);					/*Debug interface serial port initialization*/
	Angle_J1 = 90;						  /*servo  initialization*/
	delay_init();
	NVIC_Configuration(); 	    /*Set NVCI interrupt packet 2, 2 bit preemption priority, 2 bit response priority*/
	GPIO_UserInit();            /*OLED port initialization*/
	LCD_Init0();			          /*OLED port initialization*/
	Start_init();
}
