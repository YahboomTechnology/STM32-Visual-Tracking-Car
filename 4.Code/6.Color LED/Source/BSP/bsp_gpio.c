/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_gpio.c
* @author       liusen
* @version      V1.0
* @date         2017.07.10    
* @brief        drive gpio
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/

#include "stm32f10x.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_bkp.h"
#include "bsp_gpio.h"
#include "bsp_servo.h"
#include "bsp.h"
#include "bsp_colorful.h"

/**
* Function       MOTOR_GPIO_Config
* @author        liusen
* @date          2017.07.10        
* @brief         motor GPIO initialization
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/

void MOTOR_GPIO_Init(void)
{		
		GPIO_InitTypeDef  GPIO_InitStructure;	//Define a structure
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	 //Enable pb, pc.pd port clock
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;           //Define the pins that need to be enabled		
	 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //Push-pull output
	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // speed of port IO is 50Mhz
	
		GPIO_Init(GPIOC, &GPIO_InitStructure);					     //Initialize according to the setting parameters
	
		GPIO_SetBits(GPIOC,GPIO_Pin_11);                     //Set high level to this pin			 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;           //Define the pins that need to be enabled	
	
		GPIO_Init(GPIOC, &GPIO_InitStructure);              //Initialize according to the setting parameters
	
		GPIO_SetBits(GPIOC,GPIO_Pin_12);                    //Set high level to this pin						 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;           //Define the pins that need to be enabled
		
		GPIO_Init(GPIOD, &GPIO_InitStructure);              //Initialize according to the setting parameters
		
		GPIO_SetBits(GPIOD,GPIO_Pin_2); 					 
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 
		
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;           //Define the pins that need to be enabled 	    		
		
		GPIO_Init(GPIOB, &GPIO_InitStructure);              //Initialize according to the setting parameters
		
		GPIO_SetBits(GPIOB,GPIO_Pin_3);                     //Set high level to this pin						  	
		 

}

/**
* Function       Servo_GPIO_Init
* @author        liusen
* @date          2017.07.10        
* @brief         servo inetrface GPIO initialization
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void Servo_GPIO_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;

#ifdef USE_SERVO_J1
	
	   /*Turn on the peripheral clock*/
	   RCC_APB2PeriphClockCmd(Servo_J1_RCC, ENABLE); 
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	   GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	   /*Select the pin to control*/																	   
  	 GPIO_InitStructure.GPIO_Pin = Servo_J1_PIN;	
	   /*Set the pin mode to push-pull output*/
  	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	   /*Set the pin rate is 50Mhz*/  
  	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
      /*PORT initialization*/
  	 GPIO_Init(Servo_J1_PORT, &GPIO_InitStructure);		  
#endif
}
/**
* Function       Colorful_GPIO_Init
* @author        liusen
* @date          2015.01.03    
* @brief         Colorful_GPIO_Init
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void Colorful_GPIO_Init(void)
{


#ifdef USE_COLOR_RED
	  GPIO_InitTypeDef GPIO_InitStructure;
	   /*Turn on the peripheral clock*/
	  RCC_APB2PeriphClockCmd(Colorful_Red_RCC, ENABLE); 
	   /*Select the pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = Colorful_Red_PIN;	
	   /*Set the pin mode to push-pull output*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	   /*Set the pin rate is 50Mhz*/  
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	   /*PORT initialization*/
  	GPIO_Init(Colorful_Red_PORT, &GPIO_InitStructure);		  
#endif

#ifdef USE_COLOR_GREEN

	  /*Turn on the peripheral clock*/
	  RCC_APB2PeriphClockCmd(Colorful_Green_RCC, ENABLE); 
	   /*Select the pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = Colorful_Green_PIN;	
	  /*Set the pin mode to push-pull output*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	  /*Set the pin rate is 50Mhz*/ 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	   /*PORT initialization*/
  	GPIO_Init(Colorful_Green_PORT, &GPIO_InitStructure);
			  
#endif

#ifdef USE_COLOR_BLUE

	  /*Turn on the peripheral clock*/
	  RCC_APB2PeriphClockCmd(Colorful_Blue_RCC, ENABLE); 
	  /*Select the pin to control*/														   
  	GPIO_InitStructure.GPIO_Pin = Colorful_Blue_PIN;	
	   /*Set the pin mode to push-pull output*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	   /*Set the pin rate is 50Mhz*/  
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	  /*PORT initialization*/
  	GPIO_Init(Colorful_Blue_PORT, &GPIO_InitStructure);	
#endif
	  
}

/**
* Function       Start_init
* @author        sax_john
* @date          2015.01.03    
* @brief         button
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void Start_init()
{
		GPIO_InitTypeDef GPIO_InitStructure;
	  /*Turn on the peripheral clock*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
	  /*Select the pin to control*/																		   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	
	  /*Set the pin mode to Pull-up input*/ 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
	  /*Set the pin rate is 50Mhz*/  
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	  /*PORT initialization*/
  	GPIO_Init(GPIOC, &GPIO_InitStructure);		
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13));
	
}






