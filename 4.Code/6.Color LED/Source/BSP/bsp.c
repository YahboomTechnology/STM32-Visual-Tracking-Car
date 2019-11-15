/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp.c
* @author       liusen
* @version      V1.0
* @date         2015.01.03
* @brief        Drive total entrance
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
* @brief         Hardware device initialization  
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void bsp_init(void)
{ 

	Colorful_GPIO_Init();	
	Uart1_init(115200);					   /*Debug interface serial port initialization*/
	Angle_J1 = 90;						     /*servo  initialization*/
	delay_init();
	NVIC_Configuration(); 	       /*Set NVCI interrupt packet 2, 2 bit preemption priority, 2 bit response priority*/
	Start_init();
	
}
