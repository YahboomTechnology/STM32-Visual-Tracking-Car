/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_colorful.h
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief        蜂鸣器驱动
* @details      
* @par History  见如下说明
*                 
* version:		liusen_20170717
*/

#ifndef __BSP_BUZZER_H__
#define __BSP_BUZZER_H__

#include "stm32f10x.h"


#define Buzzer_PIN	GPIO_Pin_0
#define Buzzer_PORT	GPIOA
#define Buzzer_RCC	RCC_APB2Periph_GPIOA



void Buzzer_Control(int v_OnOff);



#endif


