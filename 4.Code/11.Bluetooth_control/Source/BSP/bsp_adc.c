/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_adc.c
* @author       liusen
* @version      V1.0
* @date         2017.08.17
* @brief        ADC
* @details      
* @par History  见如下说明
*                 
* version:		liusen_20170817
*/

#include "bsp_adc.h"
#include "stm32f10x_adc.h"
#include "delay.h"
#include "OLED.h"


void ADC_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
		//72M/6=12,ADC 最大时间不能超过 14M
	//PA0 作为模拟通道输入引脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE ); //使能 ADC1 通道时钟

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化 GPIOA.1
}

/**
* Function       Adc_Init
* @author        liusen
* @date          2017.08.17    
* @brief         ADC初始化接口
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   这里我们仅以规则通道为例	 我们默认将开启通道 0~3
*/

void Adc_Init(void)
{ 
	ADC_InitTypeDef ADC_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1 , ENABLE ); //使能 ADC1 通道时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //设置 ADC 分频因子 6

	ADC_GPIO_Init();
	
	ADC_DeInit(ADC1); //复位 ADC1,将外设 ADC1 的全部寄存器重设为缺省值
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC 独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; //单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC 数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1; //顺序进行规则转换的 ADC 通道的数目
	ADC_Init(ADC1, &ADC_InitStructure); //根据指定的参数初始化外设 ADCx
	ADC_Cmd(ADC1, ENABLE); //使能指定的 ADC1
	ADC_ResetCalibration(ADC1); //开启复位校准
	while(ADC_GetResetCalibrationStatus(ADC1)); //等待复位校准结束
	ADC_StartCalibration(ADC1); //开启 AD 校准
	while(ADC_GetCalibrationStatus(ADC1)); //等待校准结束
}
/**
* Function       Get_Adc
* @author        liusen
* @date          2017.08.17     
* @brief         获得 ADC 值
* @param[in]     ch:通道值 0~3
* @param[out]    void
* @retval        void
* @par History   这里我们仅以规则通道为例	 我们默认将开启通道 0~3
*/

static u16 Get_Adc(u8 ch)
{
	//设置指定 ADC 的规则组通道，设置它们的转化顺序和采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );
	//通道 1,规则采样顺序值为 1,采样时间为 239.5 周期
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //使能软件转换功能
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1); //返回最近一次 ADC1 规则组的转换结果
}

/**
* Function       Get_Adc_Average
* @author        liusen
* @date          2017.08.17    
* @brief         获得 ADC 多次测量平均值
* @param[in]     ch:通道值 0~3 ; times:测量次数
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
* @brief         获得测得原始电压值
* @param[in]     ch:通道值 0~3 ; times:测量次数
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
* @brief         获得实际电池分压前电压
* @param[in]     void
* @param[out]    void
* @retval        float 电压值
* @par History   
*/
float Get_Battery_Volotage(void)
{
	float temp;
	ADC_GPIO_Init();
	temp = Get_Measure_Volotage();
	temp = temp * 4.0; //temp*(5+5)/5;  3：误差调节到2.827
	return temp;
}
/**
* Function       Get_Battery_Volotage_show()
* @author        sax_john
* @date          2018.10.24  
* @brief         获得实际电池电压并且显示在OLED上
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
	LCD_Print(0, 0,"亚博智能",TYPE16X16,TYPE8X16);
	LCD_Print(8, 16,&shi,TYPE16X16,TYPE8X16);
	LCD_Print(16, 16,&ge,TYPE16X16,TYPE8X16);
	LCD_Print(24, 16,".",TYPE16X16,TYPE8X16);
	LCD_Print(32, 16,&fen,TYPE16X16,TYPE8X16);
	LCD_Print(40, 16,&shifen,TYPE16X16,TYPE8X16);	
	LCD_Print(48, 16,"伏特",TYPE16X16,TYPE8X16);
	
}
















