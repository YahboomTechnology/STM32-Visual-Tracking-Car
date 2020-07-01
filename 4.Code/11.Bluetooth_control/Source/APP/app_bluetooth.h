/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_bluetooth.h
* @author       liusen
* @version      V1.0
* @date         2017.08.18
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/

#ifndef __APP_BLUETOOTH_H__
#define __APP_BLUETOOTH_H__


#include "app_ultrasonic.h"
#include "bsp_ultrasonic.h"
#include "bsp_servo.h"
#include "sys.h"
#include "app_motor.h"
#include "delay.h"

extern int g_modeSelect;  
extern u8 g_Boolfire;	   

void serial_data_postback(void);
void app_bluetooth_deal(void);

#endif
