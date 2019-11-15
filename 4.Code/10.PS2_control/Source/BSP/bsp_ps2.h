
#ifndef __BSP_PS2_H__
#define __BSP_PS2_H__

#include "stm32f10x.h"
#include "sys.h"

#define PS2_MOSI_PIN	GPIO_Pin_1
#define PS2_MOSI_PORT	GPIOC
#define PS2_MOSI_RCC	RCC_APB2Periph_GPIOC

#define PS2_MISO_PIN	GPIO_Pin_2
#define PS2_MISO_PORT	GPIOC
#define PS2_MISO_RCC	RCC_APB2Periph_GPIOC


#define PS2_CS_PIN		GPIO_Pin_3
#define PS2_CS_PORT		GPIOC
#define PS2_CS_RCC		RCC_APB2Periph_GPIOC


#define PS2_SCK_PIN		GPIO_Pin_0
#define PS2_SCK_PORT	GPIOA
#define PS2_SCK_RCC		RCC_APB2Periph_GPIOA




#define DI   PCin(1)           

#define DO_H PCout(2)=1        
#define DO_L PCout(2)=0        

#define CS_H PCout(3)=1       
#define CS_L PCout(3)=0       

#define CLC_H PAout(0)=1      
#define CLC_L PAout(0)=0      



//These are our button constants
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16
#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      16



//These are stick values
#define PSS_RX 5               
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8



extern u8 Data[9];
extern u16 MASK[16];
extern u16 Handkey;

void PS2_Init(void);
u8 PS2_DataKey(void);		  
u8 PS2_AnologData(u8 button); 
void PS2_ClearData(void);	  


#endif
