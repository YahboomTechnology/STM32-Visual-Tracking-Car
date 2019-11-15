/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_adc.c
* @author       liusen
* @version      V1.0
* @date         2017.08.17
* @brief        ADC
* @details      
* @par History  
*                 
* version:		liusen_20170817
*/

#include "bsp_gs.h"
#include "stm32f10x_adc.h"
#include "delay.h"




/**
* Function       bsp_GS_Init
* @author        liusen
* @date          2017.08.17    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/

void bsp_GS_Init(void)
{ 
#ifdef USE_GS
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1 , ENABLE ); 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); 

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	ADC_DeInit(ADC1); 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; 
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure); 
	ADC_Cmd(ADC1, ENABLE); 
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1)); 
	ADC_StartCalibration(ADC1); 
	while(ADC_GetCalibrationStatus(ADC1)); 
#endif
}
/**
* Function       Get_Adc
* @author        liusen
* @date          2017.08.17     
* @brief         
* @param[in]     
* @param[out]    void
* @retval        void
* @par History  
*/

static u16 Get_Adc(u8 ch)
{
	
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
	return ADC_GetConversionValue(ADC1); 
}

/**
* Function       Get_Adc_Average
* @author        liusen
* @date          2017.08.17    
* @brief        
* @param[in]     
* @param[out]    void
* @retval        void
* @par History   
*/

static u16 Get_Adc_Average(u8 ch, u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{ 
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
}

/**
* Function       Get_GS_Value
* @author        liusen
* @date          2017.08.17  
* @brief         
* @param[out]    void
* @retval        void
* @par History   
*/
int Get_GS_Value(void)
{
	u16 adcx;

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE ); 

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	adcx = Get_Adc_Average(ADC_Channel_1, 10);
	
	return adcx;
}
