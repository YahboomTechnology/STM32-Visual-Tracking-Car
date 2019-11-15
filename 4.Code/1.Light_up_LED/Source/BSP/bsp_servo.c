/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_servo.c	
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief        servo control drive
* @details      
* @par History  
*                 
* version:		liusen_20170717
*/

#include "bsp_servo.h"
#include "delay.h"


/*angle range 0~180*/
int Angle_J1 = 0;

/**
* Function       Servo_J1
* @author        liusen
* @date          2017.07.17    
* @brief         servo control 
* @param[in]     v_iAngle:0~180
* @param[out]    void
* @retval        void
* @par History   no
*/
void Servo_J1(int v_iAngle)      /*Define a pulse function to simulate the generation of PWM values*/
{
	int pulsewidth;    						//Define the pulse width variable

	pulsewidth = (v_iAngle * 11) + 500;			//Convert the Angle to 500-2480 pulse width

	GPIO_SetBits(Servo_J1_PORT, Servo_J1_PIN );		//set servo interface level to high
	delay_us(pulsewidth);					

	GPIO_ResetBits(Servo_J1_PORT, Servo_J1_PIN );		//set servo interface level to LOW
	delay_ms(20 - pulsewidth/1000);		//Delay  remaining time in the period
}


/**
* Function       front_detection
* @author        liusen
* @date          2017.07.17    
* @brief         front_servo
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
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
* @brief         servo-left
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
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
* @brief         servo-right
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void right_detection()
{
	int i = 0;
	for(i = 0; i <= 15; i++) 						
	{
		Servo_J1(5);					
	}
}

