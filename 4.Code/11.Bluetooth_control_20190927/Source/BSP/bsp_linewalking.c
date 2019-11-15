/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_linewalking.c	
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief       
* @details      
* @par History  
*                 
* version:		liusen_20170717
*/

#include "bsp_linewalking.h"
#include "stm32f10x.h"


/**
* Function       bsp_GetLineWalking
* @author        liusen
* @date          2017.07.20    
* @brief         
* @param[in]     int *p_iL1, int *p_iL2, int *p_iR1, int *p_iR2 
* @param[out]    
* @return        void
* @par History   
*/

void bsp_GetLineWalking(int *p_iL1, int *p_iL2, int *p_iR1, int *p_iR2)
{
	*p_iL1 = GPIO_ReadInputDataBit(LineWalk_L1_PORT, LineWalk_L1_PIN);
	*p_iL2 = GPIO_ReadInputDataBit(LineWalk_L2_PORT, LineWalk_L2_PIN);
	*p_iR1 = GPIO_ReadInputDataBit(LineWalk_R1_PORT, LineWalk_R1_PIN);
	*p_iR2 = GPIO_ReadInputDataBit(LineWalk_R2_PORT, LineWalk_R2_PIN);		
}

/**
* Function       bsp_GetLineWalking_Data
* @author        liusen
* @date          2017.07.20    
* @brief         
* @param[in]     void
* @param[out]    void
* @return        1011,
* @par History  
*/

int bsp_GetLineWalking_Data(void)
{
	int iL1, iL2, iR1, iR2, returnValue;

	iL1 = GPIO_ReadInputDataBit(LineWalk_L1_PORT, LineWalk_L1_PIN);
	iL2 = GPIO_ReadInputDataBit(LineWalk_L2_PORT, LineWalk_L2_PIN);
	iR1 = GPIO_ReadInputDataBit(LineWalk_R1_PORT, LineWalk_R1_PIN);
	iR2 = GPIO_ReadInputDataBit(LineWalk_R2_PORT, LineWalk_R2_PIN);	

	returnValue = (iL1 == 1?0:1000);
	returnValue += (iL2 == 1?0:100);
	returnValue += (iR1 == 1?0:10);
	returnValue += (iR2 == 1?0:1);
	return returnValue;
}

