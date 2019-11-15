/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_ps2.c	
* @author       xiaozhen
* @version      V1.0
* @date         2018.03.11
* @brief        
* @details      
* @par History  
*                 
* version:		xiaozhen_20180311
*/

#include "bsp_ps2.h"
#include "sys.h"

/*
#define DO_H         GPIOA->BSRR = GPIO_Pin_9
#define DO_L         GPIOA->BRR  = GPIO_Pin_9
#define CLC_H        GPIOA->BSRR = GPIO_Pin_11
#define CLC_L        GPIOA->BRR  = GPIO_Pin_11
#define CS_H         GPIOA->BSRR = GPIO_Pin_8
#define CS_L         GPIOA->BRR  = GPIO_Pin_8


#define DI      GPIOA->IDR  & GPIO_Pin_8	
*/


u16 Handkey;
u8 Comd[2]={0x01,0x42};	
u8 scan[9]={0x01,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//{0x01,0x42,0x00,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A};	// ¿‡–Õ∂¡»°

u8 Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; 
u16 MASK[]={
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
};	

/**
* Function       delay_1us
* @author        xiaozhen
* @date          2018.03.11
* @brief         
* @param         xms£∫£®ms£©
* @retval        void
* @par History   no
*/	
void delay_1us(u32 n)
{
	u8 j;
	while(n--)
	for(j=0;j<10;j++);
}

/**
* Function       PS2_Init
* @author        Danny
* @date          2017.08.16
* @brief         PS2
* @param         void
* @retval        void
* @par History   
*/	
void PS2_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);  	
	
  	GPIO_InitStructure.GPIO_Pin = PS2_SCK_PIN;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                              
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  	GPIO_Init(PS2_SCK_PORT, &GPIO_InitStructure);	

	  	GPIO_InitStructure.GPIO_Pin = PS2_MISO_PIN;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                               
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  	GPIO_Init(PS2_MOSI_PORT, &GPIO_InitStructure);	
	
	
	GPIO_InitStructure.GPIO_Pin = PS2_CS_PIN ;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                               
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  	GPIO_Init(PS2_CS_PORT, &GPIO_InitStructure);	


	GPIO_InitStructure.GPIO_Pin = PS2_MOSI_PIN;	//DI
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(PS2_MOSI_PORT, &GPIO_InitStructure);
	
	DO_H;
	CLC_H;
	CS_H;

}

/**
* Function       PS2_ReadData
* @author        xiaozhen
* @date          2018.03.11
* @brief         
* @param         void
* @retval        void
* @par History   
*/

u8 PS2_ReadData(u8 command)
{
	u8 i,j=1;
	u8 res=0; 
    for(i=0; i<=7; i++)          
    {
		if(command&0x01)	       
			DO_H;
		else
			DO_L;
		command = command >> 1;	   
		delay_1us(10);			   
		CLC_L;
		delay_1us(10);
		if(DI) 					   
			res = res + j;
		j = j << 1; 
		CLC_H;
		delay_1us(10);	 
    }
    DO_H;
	delay_1us(50);
    return res;					   
}

/**
* Function       PS2_DataKey
* @author        Danny
* @date          2017.08.16
* @brief         
* @param         void
* @retval        void
* @par History   
*/	

unsigned char PS2_DataKey()
{
	u8 index = 0, i = 0;

	PS2_ClearData();
	CS_L;
	for(i=0;i<9;i++)	            
	{
		Data[i] = PS2_ReadData(scan[i]);	
	} 
	CS_H;
	

	Handkey=(Data[4]<<8)|Data[3];     
	for(index=0;index<16;index++)
	{	    
		if((Handkey&(1<<(MASK[index]-1)))==0)
			return index+1;
	}
	return 0;                         
}

/**
* Function       PS2_AnologData
* @author        xiaozhen
* @date          2018.03.11
* @brief         range:0~256
* @param         void
* @retval        void
* @par History   
*/	
	 
u8 PS2_AnologData(u8 button)
{
	return Data[button];
}

/**
* Function       PS2_ClearData
* @author        xiaozhen
* @date          2018.03.11
* @brief         
* @param         void
* @retval        void
* @par History   
*/
void PS2_ClearData()
{
	u8 a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}
