/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_servo.h	
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief        
* @details      
* @par History  
*                 
* version:		liusen_20170717
*/

#ifndef __BSP_SERVO_H__
#define __BSP_SERVO_H__

#include "stm32f10x.h"



extern int Angle_J1;
extern int Angle_J2;
extern int Angle_J3;
extern int Angle_J4;
extern int Angle_J5;
extern int Angle_J6;

#define Servo_J1_PIN	GPIO_Pin_4

#define Servo_J1_PORT	GPIOB


#define Servo_J1_RCC	RCC_APB2Periph_GPIOB


void Servo_J1(int v_iAngle);



void front_detection(void);
void left_detection(void);
void right_detection(void);



#endif

