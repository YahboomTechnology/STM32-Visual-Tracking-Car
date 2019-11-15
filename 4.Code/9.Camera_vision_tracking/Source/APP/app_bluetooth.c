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

#include "stm32f10x.h"
#include "app_bluetooth.h"
#include "bsp_ultrasonic.h"
#include "bsp_servo.h"
#include "sys.h"
#include "app_motor.h"
#include "delay.h"
#include "protocol.h"
#include "bsp.h"
#include "app_linewalking.h"
#include "app_ultrasonic.h"
#include "app_colormode.h"
#include "exti.h"
#include "ov7670.h"
#include "lcd.h"
#include "led.h" 
#include<math.h>


float Distance_test(void);
float bsp_getUltrasonicDistance0();
int g_modeSelect = 0;  
u8 g_Boolfire = 0;	    


void serial_data_postback()
{
	float csbLen=0.0f, power; 
	u16 gs=0, lf=0; 
	u8 hw=0, gm=0;
	int Ll1=0, Rr1=0;

	csbLen= bsp_getUltrasonicDistance0();
	if(csbLen>500)
		csbLen=0;
	//csbLen =(int)Distance_test();
	power = Get_Battery_Volotage();
	//gs = Get_GS_Value();
	//lf = bsp_GetLineWalking_Data();
	//hw = bsp_GetIRavoid_Data();
//	bsp_GetLightSeeking(&Ll1, &Rr1);
	//gm = Ll1 * 10 + Rr1;
	//printf("hhhh");
	printf("$4WD,CSB%.2f,PV%1.2f,GS%d,LF%04d,HW%02d,GM%02d#",csbLen, power, gs, lf, hw, gm);																				
	return;
}

/**
* Function       app_bluetooth_deal
* @author        liusen
* @date          2017.07.20    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void app_bluetooth_deal(void)
{
	if (newLineReceived)
   	{
		Protocol();
	}

	switch (g_modeSelect)
	{
		case 1: break; 								
		case 2: app_LineWalking(); break; 			
		case 3: app_ultrasonic_mode0();  break;  	
		default:break;
	}

	if (g_modeSelect == 0 && g_Boolfire == 0)
	{
		if (g_count >= 100000)
		{ 
			g_count = 0;
			serial_data_postback();
		}		
	}

}
