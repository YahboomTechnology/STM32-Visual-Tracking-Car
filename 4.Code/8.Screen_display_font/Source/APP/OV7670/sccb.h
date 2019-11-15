#ifndef __SCCB_H
#define __SCCB_H
#include "sys.h"



#define SCCB_SDA_IN()  {GPIOA->CRH&=0XFF0FFFFF;GPIOA->CRH|=0X00800000;}
#define SCCB_SDA_OUT() {GPIOA->CRH&=0XFF0FFFFF;GPIOA->CRH|=0X00300000;}


#define SCCB_SCL    		PAout(12)	 	//SCL
#define SCCB_SDA    		PAout(11) 		//SDA	 

#define SCCB_READ_SDA    	PAin(11)  		//SDA
#define SCCB_ID   			0X42  			//OV7670µÄID

///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);
#endif













