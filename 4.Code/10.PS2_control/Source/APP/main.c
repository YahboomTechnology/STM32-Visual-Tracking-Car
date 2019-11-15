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
#include "app_bluetooth.h"
#include "bsp_ps2.h"
#include "app_ps2Control.h"


int speed=0,run;
int nextblack,g_readSpeed;
int qianjin=0,houtui=0;
extern u8 nonside[];


int main(void)
{	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
	bsp_init();
	
	while (1)
	{ 
		//MiniCar_Run(500);
		Get_Battery_Volotage_show();
		app_ultrasonic_modeshow();
	//		g_readSpeed++;
	//	if(g_readSpeed >= 2)	     
	//	{
			g_readSpeed = 0;
			app_ps2_deal();	
	//	}
		app_CarstateOutput();
	}
}
