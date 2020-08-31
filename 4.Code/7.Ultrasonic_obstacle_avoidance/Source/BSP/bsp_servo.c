/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_servo.c	
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief        
* @details      
* @par History  
*                 
* version:		liusen_20170717
*/

#include "bsp_servo.h"
#include "delay.h"



int Angle_J1 = 0;
int Angle_J2 = 0;
int Angle_J3 = 0;
int Angle_J4 = 0;
int Angle_J5 = 0;
int Angle_J6 = 0;


/**
* Function       Servo_J1
* @author        liusen
* @date          2017.07.17    
* @brief     
* @param[in]     v_iAngle 
* @param[out]    void
* @retval        void
* @par History   
*/
void Servo_J1(int v_iAngle)
{
	int pulsewidth;    						

	pulsewidth = (v_iAngle * 11) + 500;		

	GPIO_SetBits(Servo_J1_PORT, Servo_J1_PIN );		
	delay_us(pulsewidth);				

	GPIO_ResetBits(Servo_J1_PORT, Servo_J1_PIN );	
	delay_ms(20 - pulsewidth/1000);			
}

/**
* Function       Servo_J2
* @author        liusen
* @date          2017.07.17    
* @brief       
* @param[in]     v_iAngle 
* @param[out]    void
* @retval        void
* @par History   
*/
void Servo_J2(int v_iAngle)
{
	int pulsewidth;    					

	pulsewidth = (v_iAngle * 11) + 500;			

	GPIO_SetBits(Servo_J2_PORT, Servo_J2_PIN );		
	delay_us(pulsewidth);				

	GPIO_ResetBits(Servo_J2_PORT, Servo_J2_PIN );	
	delay_ms(20 - pulsewidth/1000);			
}

/**
* Function       Servo_J3
* @author        liusen
* @date          2017.07.17    
* @brief        
* @param[in]     v_iAngle 
* @param[out]    void
* @retval        void
* @par History   
*/
void Servo_J3(int v_iAngle)
{
	int pulsewidth;    						

	pulsewidth = (v_iAngle * 11) + 500;			

	GPIO_SetBits(Servo_J3_PORT, Servo_J3_PIN );	
	delay_us(pulsewidth);					

	GPIO_ResetBits(Servo_J3_PORT, Servo_J3_PIN );	
	delay_ms(20 - pulsewidth/1000);		
}

/**
* Function       Servo_J4
* @author        liusen
* @date          2017.07.17    
* @brief        
* @param[in]     v_iAngle 
* @param[out]    void
* @retval        void
* @par History   
*/
void Servo_J4(int v_iAngle)
{
	int pulsewidth;    						

	pulsewidth = (v_iAngle * 11) + 500;			

	GPIO_SetBits(Servo_J4_PORT, Servo_J4_PIN );		
	delay_us(pulsewidth);					

	GPIO_ResetBits(Servo_J4_PORT, Servo_J4_PIN );	
	delay_ms(20 - pulsewidth/1000);			
}

/**
* Function       Servo_J5
* @author        liusen
* @date          2017.07.17    
* @brief        
* @param[in]     v_iAngle 
* @param[out]    void
* @retval        void
* @par History   
*/
void Servo_J5(int v_iAngle)
{
	int pulsewidth;    					

	pulsewidth = (v_iAngle * 11) + 500;			

	GPIO_SetBits(Servo_J5_PORT, Servo_J5_PIN );		
	delay_us(pulsewidth);					

	GPIO_ResetBits(Servo_J5_PORT, Servo_J5_PIN );	
	delay_ms(20 - pulsewidth/1000);			
}

/**
* Function       Servo_J6
* @author        liusen
* @date          2017.07.17    
* @brief         
* @param[in]     v_iAngle 
* @param[out]    void
* @retval        void
* @par History   
*/
void Servo_J6(int v_iAngle)
{
	int pulsewidth;    						

	pulsewidth = (v_iAngle * 11) + 500;			

	GPIO_SetBits(Servo_J6_PORT, Servo_J6_PIN );		
	delay_us(pulsewidth);					

	GPIO_ResetBits(Servo_J6_PORT, Servo_J6_PIN );	
	delay_ms(20 - pulsewidth/1000);			
}

/**
* Function       front_detection
* @author        liusen
* @date          2017.07.17    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void front_detection()
{
	int i = 0;

  	for(i=0; i <= 15; i++) 					
  	{
    	Servo_J1(90);						
  	}
}

/**
* Function       left_detection
* @author        liusen
* @date          2017.07.17    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void left_detection()
{
	int i = 0;
	for(i = 0; i <= 15; i++) 						
	{
		Servo_J1(175);					
	}
}

/**
* Function       right_detection
* @author        liusen
* @date          2017.07.17    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void right_detection()
{
	int i = 0;
	for(i = 0; i <= 15; i++) 						
	{
		Servo_J1(5);					
	}
}

