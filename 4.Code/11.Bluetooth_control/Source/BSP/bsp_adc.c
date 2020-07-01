/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_adc.c
* @author       liusen
* @version      V1.0
* @date         2017.08.17
* @brief        ADC
* @details      
* @par History  ������˵��
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
		//72M/6=12,ADC ���ʱ�䲻�ܳ��� 14M
	//PA0 ��Ϊģ��ͨ����������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE ); //ʹ�� ADC1 ͨ��ʱ��

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ������
	GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ�� GPIOA.1
}

/**
* Function       Adc_Init
* @author        liusen
* @date          2017.08.17    
* @brief         ADC��ʼ���ӿ�
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   �������ǽ��Թ���ͨ��Ϊ��	 ����Ĭ�Ͻ�����ͨ�� 0~3
*/

void Adc_Init(void)
{ 
	ADC_InitTypeDef ADC_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1 , ENABLE ); //ʹ�� ADC1 ͨ��ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //���� ADC ��Ƶ���� 6

	ADC_GPIO_Init();
	
	ADC_DeInit(ADC1); //��λ ADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC ����ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; //��ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC �����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1; //˳����й���ת���� ADC ͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure); //����ָ���Ĳ�����ʼ������ ADCx
	ADC_Cmd(ADC1, ENABLE); //ʹ��ָ���� ADC1
	ADC_ResetCalibration(ADC1); //������λУ׼
	while(ADC_GetResetCalibrationStatus(ADC1)); //�ȴ���λУ׼����
	ADC_StartCalibration(ADC1); //���� AD У׼
	while(ADC_GetCalibrationStatus(ADC1)); //�ȴ�У׼����
}
/**
* Function       Get_Adc
* @author        liusen
* @date          2017.08.17     
* @brief         ��� ADC ֵ
* @param[in]     ch:ͨ��ֵ 0~3
* @param[out]    void
* @retval        void
* @par History   �������ǽ��Թ���ͨ��Ϊ��	 ����Ĭ�Ͻ�����ͨ�� 0~3
*/

static u16 Get_Adc(u8 ch)
{
	//����ָ�� ADC �Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );
	//ͨ�� 1,�������˳��ֵΪ 1,����ʱ��Ϊ 239.5 ����
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //ʹ�����ת������
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1); //�������һ�� ADC1 �������ת�����
}

/**
* Function       Get_Adc_Average
* @author        liusen
* @date          2017.08.17    
* @brief         ��� ADC ��β���ƽ��ֵ
* @param[in]     ch:ͨ��ֵ 0~3 ; times:��������
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
* @brief         ��ò��ԭʼ��ѹֵ
* @param[in]     ch:ͨ��ֵ 0~3 ; times:��������
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
* @brief         ���ʵ�ʵ�ط�ѹǰ��ѹ
* @param[in]     void
* @param[out]    void
* @retval        float ��ѹֵ
* @par History   
*/
float Get_Battery_Volotage(void)
{
	float temp;
	ADC_GPIO_Init();
	temp = Get_Measure_Volotage();
	temp = temp * 4.0; //temp*(5+5)/5;  3�������ڵ�2.827
	return temp;
}
/**
* Function       Get_Battery_Volotage_show()
* @author        sax_john
* @date          2018.10.24  
* @brief         ���ʵ�ʵ�ص�ѹ������ʾ��OLED��
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
	LCD_Print(0, 0,"�ǲ�����",TYPE16X16,TYPE8X16);
	LCD_Print(8, 16,&shi,TYPE16X16,TYPE8X16);
	LCD_Print(16, 16,&ge,TYPE16X16,TYPE8X16);
	LCD_Print(24, 16,".",TYPE16X16,TYPE8X16);
	LCD_Print(32, 16,&fen,TYPE16X16,TYPE8X16);
	LCD_Print(40, 16,&shifen,TYPE16X16,TYPE8X16);	
	LCD_Print(48, 16,"����",TYPE16X16,TYPE8X16);
	
}
















