/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_colorful.h
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @details      
* @par History 
*                 
* version:		liusen_20170717
*/

#ifndef __BSP_COLORFUL_H__
#define __BSP_COLORFUL_H__

#include "stm32f10x.h"



#define Colorful_Red_PIN	GPIO_Pin_1
#define Colorful_Red_PORT	GPIOB
#define Colorful_Red_RCC	RCC_APB2Periph_GPIOB

#define Colorful_Green_PIN	GPIO_Pin_0
#define Colorful_Green_PORT	GPIOB
#define Colorful_Green_RCC	RCC_APB2Periph_GPIOB

#define Colorful_Blue_PIN	GPIO_Pin_7
#define Colorful_Blue_PORT	GPIOA
#define Colorful_Blue_RCC	RCC_APB2Periph_GPIOA


void bsp_Colorful_Control(int v_RedOnOff, int v_GreenOnOff, int v_BlueOnOff);
void Colorful_PWM_Init(u16 arr, u16 psc, u16 arr2, u16 psc2, u16 arr3, u16 psc3 );
void bsp_Colorful_RGB_PWM(int v_RPWM, int v_GPWM, int v_BPWM);



#endif


