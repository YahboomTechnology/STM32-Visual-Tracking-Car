/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         main.c	
* @author       sax_john
* @version      V1.0
* @date         2018.10.17
* @brief        
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
#include "bsp_adc.h"
#include "app_ultrasonic.h"


int speed=0,run;
extern u8 nonside[];


int main(void)
{	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              

	bsp_init();
	
	while (1)
	{ 
		app_ultrasonic_mode0();
		Draw_BMP(32,48,nonside);
		Draw_BMP(48,48,nonside);
		Draw_BMP(64,48,nonside);
	} 
}
