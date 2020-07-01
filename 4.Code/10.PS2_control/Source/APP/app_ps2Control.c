/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_ps2Control.c
* @author       xiaozhen
* @version      V1.0
* @date         2018.03.11
* @brief        
* @details      
* @par History  
*                 
* version:		liusen_20170717
*/

#include "app_ps2Control.h"
#include "protocol.h"
#include "delay.h"
#include "app_motor.h"
#include "bsp_servo.h"
#include "bsp_timer.h"
#include "bsp_colorful.h"
#include "usart.h"
#include "bsp_ps2.h"
extern int g_CarState,CarSpeedControl;
/**
* Function       app_ps2_deal
* @author        xiaozhen
* @date          2018.03.11    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/


void app_ps2_deal(void)
{
	u8 PS2_KEY = 0, X1=0,Y1=0;//,X2=0,Y2=0;

	
	__set_PRIMASK(1);                
	PS2_KEY = PS2_DataKey();	 
	__set_PRIMASK(0);            
//printf("%d",PS2_KEY);
	switch(PS2_KEY)
	{
		case PSB_SELECT: 	 break;
		case PSB_L3:     	g_CarState = enSTOP;   break;  	
		case PSB_R3:     	g_CarState = enSTOP;  break;  		
		case PSB_START:  	  break;  
		case PSB_PAD_UP: 	g_CarState = enRUN;    break;  	
		case PSB_PAD_RIGHT:	g_CarState = enRIGHT;   break;	
		case PSB_PAD_DOWN:	g_CarState = enBACK;    break;    
		case PSB_PAD_LEFT:	g_CarState = enLEFT;  break; 	
		case PSB_L2:      	
		{
			CarSpeedControl += 100;					
			if (CarSpeedControl > 1000)
			{
				CarSpeedControl = 1000;
			}
			 
//			printf("PSB_L2 \n");  	

		}break; 
		case PSB_R2:      	
		{											  
			CarSpeedControl -= 100;
			if (CarSpeedControl < 100)
			{
				CarSpeedControl = 100;
			} 
		//	printf("PSB_R2 \n");

		}  break; 
		case PSB_L1:    	break; 
		case PSB_R1:    break;     
		case PSB_TRIANGLE:	  break; 							
		case PSB_CIRCLE:  	g_CarState = enTLEFT;   break;  	
	//	case PSB_CROSS:   	whistle(); printf("PSB_CROSS \n");  break; 					
		case PSB_SQUARE:  	g_CarState = enTRIGHT;  break;  	
		default: g_CarState = enSTOP; break; 
	}


	if(PS2_KEY == PSB_L1 || PS2_KEY == PSB_R1)
	{
		X1 = PS2_AnologData(PSS_LX);
		Y1 = PS2_AnologData(PSS_LY);
//		X2 = PS2_AnologData(PSS_RX);
//		Y2 = PS2_AnologData(PSS_RY);
	//	printf("%d  %d  %d  %d\r\n",X1,X2,Y1,Y2);

	    if (Y1 < 5 && X1 > 80 && X1 < 180) 
	    {
	      g_CarState = enRUN;
	    }
	    else if (Y1 > 230 && X1 > 80 && X1 < 180) 
	    {
	      g_CarState = enBACK;
		  
	    }
	    else if (X1 < 5 && Y1 > 80 && Y1 < 180) 
	    {
	      g_CarState = enLEFT;

	    }
	    else if (Y1 > 80 && Y1 < 180 && X1 > 230)
	    {
	      g_CarState = enRIGHT;

	    }
	    else if (Y1 <= 80 && X1 <= 80) 
	    {
	      g_CarState = enUPLEFT;

	    }
	    else if (Y1 <= 80 && X1 >= 180) 
	    {
	      g_CarState = enUPRIGHT;
	
	    }
	    else if (X1 <= 80 && Y1 >= 180) 
	    {
	      g_CarState = enDOWNLEFT;
	
	    }
	    else if (Y1 >= 180 && X1 >= 180) 
	    {
	      g_CarState = enDOWNRIGHT;
		  
	    }
	    else
	    {
	      g_CarState = enSTOP;
	    }

	}	
}

void app_CarstateOutput(void)						
{
	Angle_J1 = 90;
//	printf("%d ",g_CarState);

	switch (g_CarState)
	{
		case enSTOP: MiniCar_Stop();Angle_J1 = 100; break;
		case enRUN: Angle_J1 = 100; MiniCar_Run(CarSpeedControl); break;						   
		case enLEFT: Angle_J1 = 65; MiniCar_Run(CarSpeedControl); break;						   
		case enRIGHT: Angle_J1 = 135; MiniCar_Run(CarSpeedControl); break;						  
		case enBACK: Angle_J1 = 100; MiniCar_Back(CarSpeedControl); break;						   
		case enTLEFT:  bsp_Colorful_Control(1, 1, 1); break; 
		case enTRIGHT:  bsp_Colorful_Control(0, 0, 0);  break;  

		case enUPLEFT:break;          
		case enDOWNLEFT: Angle_J1 = 65; MiniCar_Back(CarSpeedControl);  break;       
		case enUPRIGHT: break;        
		case enDOWNRIGHT: Angle_J1 = 135; MiniCar_Back(CarSpeedControl); break;      
		default: MiniCar_Stop();Angle_J1 = 100; break;
	}

}
