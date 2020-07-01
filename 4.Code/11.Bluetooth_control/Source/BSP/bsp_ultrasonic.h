/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_ultrasonic.h
* @author       liusen
* @version      V1.0
* @date         2017.07.21
* @brief        
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/

#ifndef __BSP_ULTRASONIC_H__
#define __BSP_ULTRASONIC_H__	


#define TRIG_RCC		RCC_APB2Periph_GPIOA
#define ECHO_RCC		RCC_APB2Periph_GPIOA

#define TRIG_PIN		GPIO_Pin_4
#define ECHO_PIN		GPIO_Pin_5

#define TRIG_PORT		GPIOA
#define ECHO_PORT		GPIOA


extern float bsp_getUltrasonicDistance(void);
extern void bsp_Ultrasonic_Timer2_Init(void);
void bsp_Ultrasonic_Timer2_Init(void);
void serial_data_postback(void);

#endif



