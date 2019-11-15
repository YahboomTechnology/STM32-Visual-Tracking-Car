/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_motor.h
* @author       liusen
* @version      V1.0
* @date         2015.01.03
* @brief        
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/

#ifndef __APP_MOTOR_H__
#define __APP_MOTOR_H__


#include "bsp_motor.h"

void MiniCar_Run(int Speed0);
void MiniCar_Back(int Speed0);
void MiniCar_Stop();

void Car_Run(int Speed);
void Car_Back(int Speed);
void Car_Left(int Speed);
void Car_Right(int Speed);
void Car_Stop(void);
void Car_SpinStop(void);
void Car_SpinLeft(int LeftSpeed, int RightSpeed);
void Car_SpinRight(int LeftSpeed, int RightSpeed);


#endif


