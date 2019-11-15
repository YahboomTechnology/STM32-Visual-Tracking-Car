/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         main.c	
* @author       sax_john
* @version      V1.0
* @date         2018.10.17
* @brief        main function
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


int speed=0,run;
extern u8 nonside[];


int main(void)
{	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
	/*Peripheral initialization*/
	bsp_init();
	
	while (1)
	{ 
		LCD_Print(0, 0,"亚博智能123",TYPE16X16,TYPE8X16);
		LCD_Print(0, 16,"创客教育123",TYPE16X16,TYPE8X16);
		LCD_Print(0, 32,"创客abc12",TYPE16X16,TYPE6X8);
		Draw_BMP(32,48,nonside);
		Draw_BMP(48,48,nonside);
		Draw_BMP(64,48,nonside);		
	} 
	
}
