/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         protcol.c
* @author       liusen
* @version      V1.0
* @date         2017.08.18
* @brief        
* @details      
* @par History  
*                 
* version:	liusen_20170818
*/

#include "protocol.h"
#include "usart.h"
#include "bsp_servo.h"
#include "app_bluetooth.h"
#include <stdlib.h>
#include <string.h>


u8 ProtocolString[80] = {0};
int CarSpeedControl = 200;




enum {

  enSTOP = 0,
  enRUN,
  enBACK,
  enLEFT,
  enRIGHT,
  enTLEFT,
  enTRIGHT

}enCarState;

#define 	run_car     '1'
#define 	back_car    '2'
#define 	left_car    '3'
#define 	right_car   '4'
#define 	stop_car    '0'


int g_CarState = enSTOP; 

/**
* Function       StringFind
* @author        liusen
* @date          2017.08.18    
* @brief         
* @param[in]     pSrc:Source string; pDst:Finded string v_iStartPos:The starting position of the source string
* @param[out]    void
* @retval        void
* @par History   
*/

int StringFind(const char *pSrc, const char *pDst, int v_iStartPos)  
{  
    int i, j;  
    for (i = v_iStartPos; pSrc[i]!='\0'; i++)  
    {  
        if(pSrc[i]!=pDst[0])  
            continue;         
        j = 0;  
        while(pDst[j] !='\0' && pSrc[i+j]!='\0')  
        {  
            j++;  
            if(pDst[j]!=pSrc[i+j])  
            break;  
        }  
        if(pDst[j]=='\0')  
            return i;  
    }  
    return -1;  
} 


/**
* Function       ProtocolCpyData
* @author        liusen
* @date          2017.08.18    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void ProtocolCpyData(void)
{
	memcpy(ProtocolString, inputString, g_packnum + 1);
	memset(inputString, 0x00, sizeof(inputString));
}

/**
* Function       Protocol
* @author        liusen
* @date          2017.08.18    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void Protocol(void)
{
	ProtocolCpyData();


	if(StringFind((const char *)ProtocolString, (const char *)"MODE", 0) > 0 
		&& StringFind((const char *)ProtocolString, (const char *)"4WD", 0) > 0)
	{
		
	    if (ProtocolString[10] == '0') 
	    {
	    	MiniCar_Stop();
			g_CarState = enSTOP;
			g_modeSelect = 0;
			bsp_Colorful_Control(0,0,0);
		//	BeepOnOffMode();
	    }
	    else
	    {
			switch (ProtocolString[9])
			{
				case '0': g_modeSelect = 0; break;
				case '1': g_modeSelect = 1; break;
				case '2': g_modeSelect = 2; break;
				case '3': g_modeSelect = 3; break;
				case '4': g_modeSelect = 4; break;
				case '5': g_modeSelect = 5; break;
				case '6': g_modeSelect = 6; break;
				default: g_modeSelect = 0;  break;
			}
		//	BeepOnOffMode();
	    }
	    newLineReceived = 0;  
		memset(ProtocolString, 0x00, sizeof(ProtocolString));
	    return;
  	}


	if (StringFind((const char *)ProtocolString, (const char *)"PTZ", 0) > 0)
	{
		int m_kp, i, ii;

		i = StringFind((const char *)ProtocolString, (const char *)"PTZ", 0); 
		ii = StringFind((const char *)ProtocolString, (const char *)"#", i);
		if (ii > i)
		{
			char m_skp[5] = {0};
			memcpy(m_skp, ProtocolString + i + 3, ii - i -3);
			
			m_kp = atoi(m_skp);       

			Angle_J1 = (180 - m_kp);

			newLineReceived = 0;  
			memset(ProtocolString, 0x00, sizeof(ProtocolString));
			return;
		}
  }
	

	if (StringFind((const char *)ProtocolString, (const char *)"4WD", 0) == -1)
	{

//		if (ProtocolString[3] == '1')      
//		{
//			g_CarState = enTLEFT;
//		}
//		else if (ProtocolString[3] == '2') 
//		{
//			g_CarState = enTRIGHT;
//		}
//		else
//		{
//			g_CarState = enSTOP;
//		}


		if (ProtocolString[7] == '1')    
		{
			CarSpeedControl += 100;
			if (CarSpeedControl > 1000)
			{
				CarSpeedControl = 1000;
			}
		}
		if (ProtocolString[7] == '2')	
		{
			CarSpeedControl -= 100;
			if (CarSpeedControl < 100)
			{
				CarSpeedControl = 100;
			}
		}

		if (ProtocolString[13] == '1')
		{
			bsp_Colorful_Control(1, 1, 1);
		}
		else if (ProtocolString[13] == '2')
		{
			bsp_Colorful_Control(1, 0, 0);
		}
		else if (ProtocolString[13] == '3')
		{
			bsp_Colorful_Control(0, 0, 1);
		}
		else if (ProtocolString[13] == '4') 
		{
			bsp_Colorful_Control(0, 1, 0);
		}
		else if (ProtocolString[13] == '8') 
		{
			bsp_Colorful_Control(0, 0, 0);
		}

		if (g_CarState != enTLEFT && g_CarState != enTRIGHT)
		{
			switch (ProtocolString[1])
				
			{
				case run_car:   g_CarState = enRUN; Angle_J1 = 90; break;
				case back_car:  g_CarState = enBACK; Angle_J1 = 90; break;
				case left_car:  g_CarState = enRUN; Angle_J1 = 60; break;
				case right_car: g_CarState = enRUN; Angle_J1 = 120; break;
				case stop_car:  g_CarState = enSTOP; Angle_J1 = 90; break;
				default: g_CarState = enSTOP; break;
			}
		}

		newLineReceived = 0;  
		memset(ProtocolString, 0x00, sizeof(ProtocolString));  

		switch (g_CarState)
		{
			case enSTOP: MiniCar_Stop(); break;
			case enRUN: MiniCar_Run(CarSpeedControl); break;
			case enLEFT: Angle_J1 = 50;MiniCar_Run(CarSpeedControl); break;
			case enRIGHT: Angle_J1 = 130; MiniCar_Run(CarSpeedControl); break;
			case enBACK: MiniCar_Back(CarSpeedControl); break;
			case enTLEFT: Angle_J1 = 50;MiniCar_Run(CarSpeedControl); break;
			case enTRIGHT: Angle_J1 = 130; MiniCar_Run(CarSpeedControl); break;
			default: MiniCar_Stop(); break;
		}
	}
	

}

