/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_lightseeking.c	
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief        
* @details      
* @par History 
*                 
* version:		liusen_20170717
*/

#include "app_colormode.h"
#include "bsp_colorful.h"
#include "bsp_servo.h"
#include "sys.h"
#include "app_motor.h"
#include "delay.h"

int position = 0;

/**
* Function       app_colorMode
* @author        liusen
* @date          2017.07.20    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History  
*/
void app_colorMode(void)
{
	Angle_J1 = position;
	if(position <= 10)
	{
		bsp_Colorful_RGB_PWM(255,0,0);
	}
	else if(position <= 20)
	{
		bsp_Colorful_RGB_PWM(0,255,0);	
	}
	else if(position <= 30)
	{
		bsp_Colorful_RGB_PWM(0,0,255);	
	}
	else if(position <= 40)
	{
		bsp_Colorful_RGB_PWM(255,255,0);	
	}
	else if(position <= 50)
	{
		bsp_Colorful_RGB_PWM(0,255,255);	
	}
	else if(position <= 60)
	{
		bsp_Colorful_RGB_PWM(255,0,255);	
	}
	else if(position <= 70)
	{
		bsp_Colorful_RGB_PWM(255,255,255);	
	}
	else if(position <= 80)
	{
		bsp_Colorful_RGB_PWM(125,255,0);	
	}
 	else if(position <= 90)
	{
		bsp_Colorful_RGB_PWM(125,255,0);	
	}
	else if(position <= 100)
	{
		bsp_Colorful_RGB_PWM(15,255,0);	
	}
	else if(position <= 110)
	{
		bsp_Colorful_RGB_PWM(58,255,58);	
	}
	else if(position <= 120)
	{
		bsp_Colorful_RGB_PWM(125,12,255);	
	}
	else if(position <= 130)
	{
		bsp_Colorful_RGB_PWM(10,255,0);	
	}
	else if(position <= 140)
	{
		bsp_Colorful_RGB_PWM(255,12,125);	
	}
	else if(position <= 150)
	{
		bsp_Colorful_RGB_PWM(125,125,255);	
	}
	else if(position <= 160)
	{
		bsp_Colorful_RGB_PWM(190,15,210);	
	}
	position += 10;
	if(position > 180)
	{
		position = 0;
	}
	delay_ms(1000);	
}
