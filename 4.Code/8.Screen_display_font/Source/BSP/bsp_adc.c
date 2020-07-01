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

#include "bsp_adc.h"
#include "stm32f10x_adc.h"
#include "delay.h"
#include "OLED.h"


void ADC_GPIO_Init()
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE ); 

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
}

/**
* Function       Adc_Init
* @author        liusen
* @date          2017.08.17    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/

void Adc_Init(void)
{ 
	ADC_InitTypeDef ADC_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1 , ENABLE ); 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); 

	ADC_GPIO_Init();
	
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
}
/**
* Function       Get_Adc
* @author        liusen
* @date          2017.08.17     
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
* Function       Get_Measure_Volotage
* @author        liusen
* @date          2017.08.17  
* @param[out]    void
* @retval        void
* @par History   
*/
static float Get_Measure_Volotage(void)
{
	u16 adcx;
	float temp;

	adcx=Get_Adc_Average(ADC_Channel_14, 10);
	temp=(float)adcx*(3.3/4096);
	return temp;
}

/**
* Function       Get_Battery_Volotage
* @author        liusen
* @date          2017.08.18    
* @param[in]     void
* @param[out]    void
* @retval        float 
* @par History   
*/
float Get_Battery_Volotage(void)
{
	float temp;
	ADC_GPIO_Init();
	temp = Get_Measure_Volotage();
	temp = temp * 4.0; //temp*(5+5)/5; 
	return temp;
}
/**
* Function       Get_Battery_Volotage_show()
* @author        sax_john
* @date          2018.10.24  
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void Get_Battery_Volotage_show()
{
	float Battery_Volotage;
	u8 shi,ge,fen,shifen;
	Battery_Volotage=Get_Battery_Volotage();
	shi=(int)Battery_Volotage/10+0x30;
	ge=(int)Battery_Volotage%10+0x30;
	fen=((int)((Battery_Volotage-(int)Battery_Volotage)*10))%10+0x30;
	shifen=((int)((Battery_Volotage-(int)Battery_Volotage)*100))%10+0x30;
	LCD_Print(0, 0,"ÑÇ²©ÖÇÄÜ",TYPE16X16,TYPE8X16);
	LCD_Print(8, 16,&shi,TYPE16X16,TYPE8X16);
	LCD_Print(16, 16,&ge,TYPE16X16,TYPE8X16);
	LCD_Print(24, 16,".",TYPE16X16,TYPE8X16);
	LCD_Print(32, 16,&fen,TYPE16X16,TYPE8X16);
	LCD_Print(40, 16,&shifen,TYPE16X16,TYPE8X16);	
	LCD_Print(48, 16,"·üÌØ",TYPE16X16,TYPE8X16);
	
}
















