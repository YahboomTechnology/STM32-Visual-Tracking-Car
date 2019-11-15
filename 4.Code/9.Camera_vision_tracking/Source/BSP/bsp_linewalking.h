/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_linewalking.h
* @author       liusen
* @version      V1.0
* @date         2015.01.03
* @brief        
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/



#ifndef __BSP_LINEWALKING_H__
#define __BSP_LINEWALKING_H__	


#define LineWalk_L1_RCC		RCC_APB2Periph_GPIOC
#define LineWalk_L2_RCC		RCC_APB2Periph_GPIOC
#define LineWalk_R1_RCC    	RCC_APB2Periph_GPIOC
#define LineWalk_R2_RCC		RCC_APB2Periph_GPIOB

#define LineWalk_L1_PIN		GPIO_Pin_14
#define LineWalk_L2_PIN		GPIO_Pin_13
#define LineWalk_R1_PIN		GPIO_Pin_15
#define LineWalk_R2_PIN		GPIO_Pin_12

#define LineWalk_L1_PORT	GPIOC
#define LineWalk_L2_PORT	GPIOC
#define LineWalk_R1_PORT	GPIOC
#define LineWalk_R2_PORT	GPIOB


void bsp_GetLineWalking(int *p_iL1, int *p_iL2, int *p_iR1, int *p_iR2);
int bsp_GetLineWalking_Data(void);


#endif
