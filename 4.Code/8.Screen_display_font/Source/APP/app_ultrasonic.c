/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_ultrasonic.c
* @author       liusen
* @version      V1.0
* @date         2015.01.03
* @brief        
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/

#include "app_ultrasonic.h"
#include "bsp_ultrasonic.h"
#include "bsp_servo.h"
#include "sys.h"
#include "app_motor.h"
#include "delay.h"
#include "stdio.h"


float Distance_test(void);


/**
* Function       app_ultrasonic_mode
* @author        sax_john
* @date          2017.07.20    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void app_ultrasonic_mode0(void)
{
	int Len = 0;

	Len = bsp_getUltrasonicDistance(); 
	
	//printf("CSB:%d \r\n", Len);  	

	if(Len < 25) 
    { 
			Angle_J1 = 130;
			MiniCar_Run(300);
			delay_ms(1000);
			Angle_J1 = 90;
    }
  else 
		{
		MiniCar_Run(300); 
		}
	
}

