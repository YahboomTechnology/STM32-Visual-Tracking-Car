/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_colorful.c	
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief        Color LED drive
* @details      
* @par History  
*                 
* version:		liusen_20170717
*/

#include "bsp_colorful.h"


/**
* Function       bsp_Colorful_Control
* @author        liusen
* @date          2015.01.03    
* @brief        
* @param[in]     v_RedOnOff,v_GreenOnOff,v_BlueOnOff
* @param[out]    void
* @retval        void
* @par History   Here the clock is chosen twice as much as APB1, and APB1 is 36M.
*/
void bsp_Colorful_Control(int v_RedOnOff, int v_GreenOnOff, int v_BlueOnOff)
{
	if(v_RedOnOff == 1)
	{
		GPIO_SetBits(Colorful_Red_PORT, Colorful_Red_PIN);
	}
	else
	{
		GPIO_ResetBits(Colorful_Red_PORT, Colorful_Red_PIN);
	}

	if(v_GreenOnOff == 1)
	{
		GPIO_SetBits(Colorful_Green_PORT, Colorful_Green_PIN);
	}
	else
	{
		GPIO_ResetBits(Colorful_Green_PORT, Colorful_Green_PIN);
	}

	if(v_BlueOnOff == 1)
	{
		GPIO_SetBits(Colorful_Blue_PORT, Colorful_Blue_PIN);
	}
	else
	{
		GPIO_ResetBits(Colorful_Blue_PORT, Colorful_Blue_PIN);
	}
}


