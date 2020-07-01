/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         main.c	
* @author       john
* @version      V1.0
* @date         2018.10.17
* @brief        
* @details      
* @par History  
*                 
* version:		john_20181018
*/

#include "stm32f10x.h"
#include "app_motor.h"
#include "app_bluetooth.h"
#include "bsp.h"
#include "sys.h"
#include "exti.h"
#include "ov7670.h"
#include "lcd.h"
#include "led.h"
#include <stdio.h>
#include "stm32f10x_fsmc.h"
#include "oled.h"
#include "delay.h"
#include "app_linewalking.h"
#include "bsp_colorful.h"

int nextblack;
void camera_refresh(void);
void  find_line(void);
void dir(void);
void special_line(void);
int speed=0,run;
extern void dis_play_image(void);


int main(void)
{	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              

	bsp_init();
	while (1)
	{  
		//MiniCar_lfRun(400);
		app_bluetooth_deal();
		
	} 
}
