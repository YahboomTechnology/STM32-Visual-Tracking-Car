/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_ultrasonic.c
* @author       liusen
* @version      V1.0
* @date         2015.01.03
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
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/

void app_ultrasonic_mode0(void)
{



	float len = 0;
	
	len = bsp_getUltrasonicDistance(); 
	

	serial_data_postback();
	
 

	if(len>500)
		len = 0;
	
	
	
	if(len < 34)
    { 
	
			


			MiniCar_Stop();
			delay_ms(700);
			Angle_J1 = 60;
			MiniCar_Back(100);
			delay_ms(1000);
			Angle_J1 = 85;
    }
  else 
		{
			MiniCar_Run(70); 
		}
		

	
}

