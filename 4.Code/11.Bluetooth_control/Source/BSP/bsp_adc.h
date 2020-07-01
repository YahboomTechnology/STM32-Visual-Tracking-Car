/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_adc.h	
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief        ADC
* @details      
* @par History 
*                 
* version:		liusen_20170717
*/

#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "stm32f10x.h"

void Adc_Init(void);
void ADC_GPIO_Init(void);
float Get_Meassure_Volotage(void);
float Get_Battery_Volotage(void);
void Get_Battery_Volotage_show(void);



#endif

