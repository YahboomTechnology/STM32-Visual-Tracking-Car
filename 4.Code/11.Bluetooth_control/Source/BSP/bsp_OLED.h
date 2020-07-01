/******************** (C) COPYRIGHT 2009 Hangzhou Hikvision Digital Technology Co.,Ltd ********************
* File Name              : systime.h
* Author                   : AF Application Team
* Date First Issued  : 02/06/2009
* Description        : This file includes the peripherals header files in the user application.
********************************************************************************
* History:
* 02/06/2009: V0.1
********************************************************************************

*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __GPIO_H
#define __GPIO_H

/*
*********************************************************************************************************
*                                            LOCAL GPIO DEFINES FOR  FASTDOME BOARD
*********************************************************************************************************
*/                                                              /* -------------------- GPIOA PINS -------------------- */


extern void GPIO_Configuration(void);
extern void GPIO_UserInit(void);
/* Private function prototypes -----------------------------------------------*/
//系统时钟初始化函数
extern void RCC_Configuration(void);
//中断向量初始化函数
extern void NVIC_Configuration(void);
//中断配置
extern void EXTI_Configuration(void);
extern void  SYSTICK_Init(void);
extern void SYSTEMTICK_Isr(void);




/**
 *  @brief st_systime 系统时间
 */ 
//typedef struct{
//	u32 millisec;	
//	u32 sec;		
//}st_systime;
//   
/* 全局变量声明*/
//extern st_systime g_systime; //系统时间

#endif

/******************* (C) COPYRIGHT 2009 Hangzhou Hikvision Digital Technology Co.,Ltd *****END OF FILE****/


