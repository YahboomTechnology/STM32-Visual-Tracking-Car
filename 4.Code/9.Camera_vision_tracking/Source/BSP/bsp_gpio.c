/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_gpio.c
* @author       liusen
* @version      V1.0
* @date         2017.07.10    
* @details      
* @par History 
*                 
* version:	liusen_20170717
*/

#include "stm32f10x.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_bkp.h"
#include "bsp_gpio.h"
#include "bsp_motor.h"
#include "bsp_servo.h"
#include "bsp_colorful.h"
#include "bsp_linewalking.h"
#include "bsp.h"


/**
* Function       MOTOR_GPIO_Config
* @author        liusen
* @date          2017.07.10        
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/

void MOTOR_GPIO_Init(void)
{		
		GPIO_InitTypeDef  GPIO_InitStructure;	
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			
	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	
		GPIO_Init(GPIOC, &GPIO_InitStructure);				
	
		GPIO_SetBits(GPIOC,GPIO_Pin_11);	 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		GPIO_SetBits(GPIOC,GPIO_Pin_12);				 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		
		GPIO_SetBits(GPIOD,GPIO_Pin_2); 				 
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 
		
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		GPIO_SetBits(GPIOB,GPIO_Pin_3); 					  	
		 

}

/**
* Function       Servo_GPIO_Init
* @author        liusen
* @date          2017.07.10        
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/

void Servo_GPIO_Init(void)
{		

	GPIO_InitTypeDef GPIO_InitStructure;

#ifdef USE_SERVO_J1

	RCC_APB2PeriphClockCmd(Servo_J1_RCC, ENABLE); 
														   
  	GPIO_InitStructure.GPIO_Pin = Servo_J1_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

  	GPIO_Init(Servo_J1_PORT, &GPIO_InitStructure);		  
#endif

#ifdef USE_SERVO_J2

	RCC_APB2PeriphClockCmd(Servo_J2_RCC, ENABLE); 
													   
  	GPIO_InitStructure.GPIO_Pin = Servo_J2_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

  	GPIO_Init(Servo_J2_PORT, &GPIO_InitStructure);		  
#endif

#ifdef USE_SERVO_J3


	RCC_APB2PeriphClockCmd(Servo_J3_RCC, ENABLE); 
													   
  	GPIO_InitStructure.GPIO_Pin = Servo_J3_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	  
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

  	GPIO_Init(Servo_J3_PORT, &GPIO_InitStructure);		  
#endif

#ifdef USE_SERVO_J4


	RCC_APB2PeriphClockCmd(Servo_J4_RCC, ENABLE); 
															   
  	GPIO_InitStructure.GPIO_Pin = Servo_J4_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

  	GPIO_Init(Servo_J4_PORT, &GPIO_InitStructure);		  
#endif

#ifdef USE_SERVO_J5

	RCC_APB2PeriphClockCmd(Servo_J5_RCC, ENABLE); 
													   
  	GPIO_InitStructure.GPIO_Pin = Servo_J5_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

  	GPIO_Init(Servo_J5_PORT, &GPIO_InitStructure);		  
#endif

#ifdef USE_SERVO_J6

	RCC_APB2PeriphClockCmd(Servo_J6_RCC, ENABLE); 
														   
  	GPIO_InitStructure.GPIO_Pin = Servo_J6_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

  	GPIO_Init(Servo_J6_PORT, &GPIO_InitStructure);		  
#endif
 
}

/**
* Function       Colorful_GPIO_Init
* @author        liusen
* @date          2015.01.03    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void Colorful_GPIO_Init(void)
{


#ifdef USE_COLOR_RED

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(Colorful_Red_RCC, ENABLE); 
													   
  	GPIO_InitStructure.GPIO_Pin = Colorful_Red_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

  	GPIO_Init(Colorful_Red_PORT, &GPIO_InitStructure);		  
#endif

#ifdef USE_COLOR_GREEN


	RCC_APB2PeriphClockCmd(Colorful_Green_RCC, ENABLE); 
													   
  	GPIO_InitStructure.GPIO_Pin = Colorful_Green_PIN;	
	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

  	GPIO_Init(Colorful_Green_PORT, &GPIO_InitStructure);
			  
#endif

#ifdef USE_COLOR_BLUE


	RCC_APB2PeriphClockCmd(Colorful_Blue_RCC, ENABLE); 
													   
  	GPIO_InitStructure.GPIO_Pin = Colorful_Blue_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
  	GPIO_Init(Colorful_Blue_PORT, &GPIO_InitStructure);	
#endif
	  
}

/**
* Function       LineWalking_GPIO_Init
* @author        liusen
* @date          2017.07.10    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void LineWalking_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	PWR_BackupAccessCmd(ENABLE);	
	RCC_LSEConfig(RCC_LSE_OFF);		
	BKP_TamperPinCmd(DISABLE);		
	PWR_BackupAccessCmd(DISABLE);	

#ifdef USE_LINE_L1


	RCC_APB2PeriphClockCmd(LineWalk_L1_RCC | RCC_APB2Periph_AFIO, ENABLE); 
														   
  	GPIO_InitStructure.GPIO_Pin = LineWalk_L1_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

  	GPIO_Init(LineWalk_L1_PORT, &GPIO_InitStructure);		 
#endif

#ifdef USE_LINE_L2


	RCC_APB2PeriphClockCmd(LineWalk_L2_RCC | RCC_APB2Periph_AFIO, ENABLE); 
													   
  	GPIO_InitStructure.GPIO_Pin = LineWalk_L2_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   

  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

  	GPIO_Init(LineWalk_L2_PORT, &GPIO_InitStructure);	
#endif

#ifdef USE_LINE_R1


	RCC_APB2PeriphClockCmd(LineWalk_R1_RCC | RCC_APB2Periph_AFIO, ENABLE); 
														   
  	GPIO_InitStructure.GPIO_Pin = LineWalk_R1_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   

  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

  	GPIO_Init(LineWalk_R1_PORT, &GPIO_InitStructure);	
#endif
	
#ifdef USE_LINE_R2


	RCC_APB2PeriphClockCmd(LineWalk_R2_RCC, ENABLE); 
														   
  	GPIO_InitStructure.GPIO_Pin = LineWalk_R2_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
  
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

  	GPIO_Init(LineWalk_R2_PORT, &GPIO_InitStructure);	
#endif

}


/**
* Function       Ultrasonic_GPIO_Init
* @author        liusen
* @date          2017.07.20    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void Ultrasonic_GPIO_Init(void)
{

#ifdef USE_ULTRASONIC


	GPIO_InitTypeDef GPIO_InitStructure;


	RCC_APB2PeriphClockCmd(TRIG_RCC, ENABLE); //RCC_APB2Periph_AFIO

											   
  	GPIO_InitStructure.GPIO_Pin = TRIG_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

  	GPIO_Init(TRIG_PORT, &GPIO_InitStructure);		 


	RCC_APB2PeriphClockCmd(ECHO_RCC, ENABLE); 
														   
  	GPIO_InitStructure.GPIO_Pin = ECHO_PIN;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

  	GPIO_Init(ECHO_PORT, &GPIO_InitStructure);
		
#endif

}

/**
* Function       Start_init
* @author        liusen
* @date          2017.07.20    
* @brief        
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void Start_init()
{
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
														   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

  	GPIO_Init(GPIOC, &GPIO_InitStructure);		
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13));
}





