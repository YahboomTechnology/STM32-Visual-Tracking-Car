/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp.c
* @author       liusen
* @version      V1.0
* @date         2015.01.03
* @brief        
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/

#include "exti.h"
#include "ov7670.h"
#include "lcd.h"
#include "led.h"
#include "usart.h"
#include "sys.h"
#include "delay.h"
#include "bsp.h"
#include "stdio.h"
#include "OLED.h"


extern void NVIC_Configuration(void); 
void LCD_Init0(void);
void GPIO_UserInit(void);


/**
* Function       bsp_init
* @author        liusen
* @date          2015.01.03    
* @brief        
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History  
*/
void bsp_init(void)
{
	Colorful_GPIO_Init();//Æß²ÊµÆ³õÊ¼»¯
	MOTOR_GPIO_Init();  				/*µç»úGPIO³õÊ¼»¯*/
	Servo_GPIO_Init();				    /*¶æ»ú½Ó¿ÚGPIO³õÊ¼»¯*/	
	TIM1_Int_Init(9, 72);				/*100KhzµÄ¼ÆÊıÆµÂÊ£¬¼ÆÊıµ½10Îª10us  */ 
	Ultrasonic_GPIO_Init();				/*³¬Éù²¨GPIO³õÊ¼»¯*/
	bsp_Ultrasonic_Timer2_Init();		/*³¬Éù²¨TIM2³õÊ¼»¯*/
	Uart1_init(115200);					/*µ÷ÊÔ½Ó¿Ú´®¿Ú */
	Angle_J1 = 79;						/*³õÊ¼»¯¶æ»ú°*/
	delay_init();
	ADC_GPIO_Init();
	Adc_Init();
	NVIC_Configuration(); 	 //ÉèÖÃNVICÖĞ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶	  
	while(OV7670_Init());//³õÊ¼»¯OV7670		×¢ÒâÀ² µ±Ã»ÓĞÓÃµ½ÉãÏñÍ·»òÕßËµÉãÏñÍ·Ã»ÓĞ°²×°µÄÊ±ºòÕâ¾ä´úÂëÒ»¶¨Òª×¢ÊÍµô£¬²»È»´úÂëÒ»Ö±ÔÚÕâÀï³õÊ¼»¯						  
	EXTI8_Init();						//Ê¹ÄÜ¶¨Ê±Æ÷²¶»ñ
  OV7670_CS=0;			
	config_ov7670_OutPut(20,60,320,240,1);//ÉèÖÃÉãÏñÍ·Ä£Ê½ÒÔ¼°ÉãÏñÍ·²É¼¯µÄÍ¼Ïñ´óĞ¡
	GPIO_UserInit();//OLEDÒı½Å³õÊ¼»¯
	LCD_Init0();//OLED³õÊ¼»¯
	Uart2_init(9600);
	Start_init();
}
