/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         main.c	
* @author       sax_john
* @version      V1.0
* @date         2018.10.17
* @brief        mian
* @details      
* @par History  
*                 
* version:		sax_john_20181018
*/

#include "stm32f10x.h"
#include "app_motor.h"
#include "bsp.h"
#include "sys.h"
#include <stdio.h>
#include "stm32f10x_fsmc.h"
#include "delay.h"
#include "OLED.h"
#include "bsp_colorful.h"


int speed=0,run;
extern u8 nonside[];


int main(void)
{	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              

	bsp_init();
	
	while (1)
	{ 
		bsp_Colorful_Control(1,0,0);
		delay_ms(1000);
		bsp_Colorful_Control(0,1,0);
		delay_ms(1000);
		bsp_Colorful_Control(0,0,1);
		delay_ms(1000);
		bsp_Colorful_Control(1,1,0);
		delay_ms(1000);
		bsp_Colorful_Control(1,1,1);
		delay_ms(1000);
	} 
	
}
