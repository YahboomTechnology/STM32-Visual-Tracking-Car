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
	Colorful_GPIO_Init();//�߲ʵƳ�ʼ��
	MOTOR_GPIO_Init();  				/*���GPIO��ʼ��*/
	Servo_GPIO_Init();				    /*����ӿ�GPIO��ʼ��*/	
	TIM1_Int_Init(9, 72);				/*100Khz�ļ���Ƶ�ʣ�������10Ϊ10us  */ 
	Ultrasonic_GPIO_Init();				/*������GPIO��ʼ��*/
	bsp_Ultrasonic_Timer2_Init();		/*������TIM2��ʼ��*/
	Uart1_init(115200);					/*���Խӿڴ��� */
	Angle_J1 = 79;						/*��ʼ������*/
	delay_init();
	ADC_GPIO_Init();
	Adc_Init();
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	  
	while(OV7670_Init());//��ʼ��OV7670		ע���� ��û���õ�����ͷ����˵����ͷû�а�װ��ʱ��������һ��Ҫע�͵�����Ȼ����һֱ�������ʼ��						  
	EXTI8_Init();						//ʹ�ܶ�ʱ������
  OV7670_CS=0;			
	config_ov7670_OutPut(20,60,320,240,1);//��������ͷģʽ�Լ�����ͷ�ɼ���ͼ���С
	GPIO_UserInit();//OLED���ų�ʼ��
	LCD_Init0();//OLED��ʼ��
	Uart2_init(9600);
	Start_init();
}
