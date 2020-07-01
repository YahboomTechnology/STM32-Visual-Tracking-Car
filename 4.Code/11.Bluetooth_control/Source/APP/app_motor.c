/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_motor.c
* @author       liusen
* @version      V1.0
* @date         2015.01.03
* @brief        
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/
#include "app_motor.h"
#include "sys.h"
#include "bsp_motor.h"	
extern int speed,run;


/**
* Function       MiniCar_Run
* @author        john
* @date          2018.10.9    
* @param[in]     Speed  £¨0~1000£© 
* @param[out]    void
* @retval        void
* @par History   
*/
void MiniCar_Run(int Speed0)
{
		speed=Speed0;
		run=1;
}


/**
* Function       MiniCar_Back
* @author        john
* @date          2018.10.9    
* @param[out]    void
* @retval        void
* @par History   
*/
void MiniCar_Back(int Speed0)
{
		speed=Speed0;
		run=0;
}

void MiniCar_rfRun(int Speed0)
{
		speed=Speed0;
		run=2;
}

void MiniCar_lfRun(int Speed0)
{
		speed=Speed0;
		run=3;
}
/**
* Function       MiniCar_Back
* @author        john
* @date          2018.10.9    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void MiniCar_Stop(void)
{
		speed=0;
}
