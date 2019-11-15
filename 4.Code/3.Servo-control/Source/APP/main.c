/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         main.c	
* @author       john
* @version      V1.0
* @date         2018.10.17
* @brief        main
* @details      
* @par History  
*                 
* version:		john_20181018
*/

#include "stm32f10x.h"
#include "app_motor.h"
#include "bsp.h"
#include "sys.h"
#include <stdio.h>
#include "stm32f10x_fsmc.h"
#include "delay.h"


int speed=0,run;


int main(void)
{	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              

	bsp_init();
	
	while (1)
	{ 
		Angle_J1 = 90;			
		MiniCar_Run(200);
		delay_ms(1000);
		
		MiniCar_Back(200);
		delay_ms(1000);
		
		Angle_J1 = 60;
		MiniCar_Run(200);
		delay_ms(1000);
		
		Angle_J1 = 120;
		delay_ms(1000);
		
		MiniCar_Stop();
		delay_ms(1000);
	} 
}
