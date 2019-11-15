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


#define M1A PBout(3)// 
#define M2A PCout(12)// 
#define M1B PDout(2)// 	
#define M2B PCout(11)//
void MiniCar_Run(int Speed0);
void MiniCar_Back(int Speed0);
void MiniCar_Stop(void);
#endif


