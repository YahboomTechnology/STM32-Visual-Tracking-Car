#include "sys.h"
#include "ov7670.h"
#include "ov7670config.h"	  
#include "delay.h"
#include "usart.h"			 
#include "sccb.h"	
#include "lcd.h"

		    			    
u8 OV7670_Init(void)
{
	u8 temp;
	u16 i=0;
	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 
 

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8; 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);


	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOC,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);	


	GPIO_InitStructure.GPIO_Pin  = 0xff00; //PC0~7 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1);

	   
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	//SWD

 	SCCB_Init();        		 	  
 	if(SCCB_WR_Reg(0x12,0x80))return 1;	
	delay_ms(50); 

 	temp=SCCB_RD_Reg(0x0b);   
	if(temp!=0x73)return 2;  
 	temp=SCCB_RD_Reg(0x0a);   
	if(temp!=0x76)return 2;
	  
	for(i=0;i<sizeof(ov7670_init_reg_tbl_RGB565)/sizeof(ov7670_init_reg_tbl_RGB565[0])/2;i++)
	{
	   	SCCB_WR_Reg(ov7670_init_reg_tbl_RGB565[i][0],ov7670_init_reg_tbl_RGB565[i][1]);
		delay_ms(2);
 	}
   	return 0x00; 	//ok
} 

OV7670_CONFIG ov7670_config;


void config_ov7670_OutPut(u16 xsta,u16 ysta,u16 width,u16 height,u8 ouput_mode){
	int i=0;
	ov7670_config.xsta = xsta;
	ov7670_config.ysta = ysta;
	ov7670_config.width = width;
	ov7670_config.height = height;
	ov7670_config.mode = ouput_mode;
	
  
	if(ouput_mode){		
		for(i=0;i<sizeof(ov7670_init_reg_tbl_YUV)/sizeof(ov7670_init_reg_tbl_YUV[0])/2;i++)
		{
			SCCB_WR_Reg(ov7670_init_reg_tbl_YUV[i][0],ov7670_init_reg_tbl_YUV[i][1]);
			delay_ms(2);
		}

	}else{				
		for(i=0;i<sizeof(ov7670_init_reg_tbl_RGB565)/sizeof(ov7670_init_reg_tbl_RGB565[0])/2;i++)
		{
			SCCB_WR_Reg(ov7670_init_reg_tbl_RGB565[i][0],ov7670_init_reg_tbl_RGB565[i][1]);
			delay_ms(2);
		}
	}
	OV7670_Window_Set(176,10,width,height);	
	LCD_Clear(WHITE);	
}

void OV7670_Light_Mode(u8 mode)
{
	u8 reg13val=0XE7;
	u8 reg01val=0;
	u8 reg02val=0;
	switch(mode)
	{
		case 1://sunny
			reg13val=0XE5;
			reg01val=0X5A;
			reg02val=0X5C;
			break;	
		case 2://cloudy
			reg13val=0XE5;
			reg01val=0X58;
			reg02val=0X60;
			break;	
		case 3://office
			reg13val=0XE5;
			reg01val=0X84;
			reg02val=0X4c;
			break;	
		case 4://home
			reg13val=0XE5;
			reg01val=0X96;
			reg02val=0X40;
			break;	
	}
	SCCB_WR_Reg(0X13,reg13val);
	SCCB_WR_Reg(0X01,reg01val);
	SCCB_WR_Reg(0X02,reg02val);
}				  

//0:-2
//1:-1
//2,0
//3,1
//4,2
void OV7670_Color_Saturation(u8 sat)
{
	u8 reg4f5054val=0X80;
 	u8 reg52val=0X22;
	u8 reg53val=0X5E;
 	switch(sat)
	{
		case 0://-2
			reg4f5054val=0X40;  	 
			reg52val=0X11;
			reg53val=0X2F;	 	 
			break;	
		case 1://-1
			reg4f5054val=0X66;	    
			reg52val=0X1B;
			reg53val=0X4B;	  
			break;	
		case 3://1
			reg4f5054val=0X99;	   
			reg52val=0X28;
			reg53val=0X71;	   
			break;	
		case 4://2
			reg4f5054val=0XC0;	   
			reg52val=0X33;
			reg53val=0X8D;	   
			break;	
	}
	SCCB_WR_Reg(0X4F,reg4f5054val);	
	SCCB_WR_Reg(0X50,reg4f5054val);	
	SCCB_WR_Reg(0X51,0X00);			
	SCCB_WR_Reg(0X52,reg52val);		
	SCCB_WR_Reg(0X53,reg53val);		
	SCCB_WR_Reg(0X54,reg4f5054val);	
	SCCB_WR_Reg(0X58,0X9E);			//MTXS 
}

//0:-2
//1:-1
//2,0
//3,1
//4,2
void OV7670_Brightness(u8 bright)
{
	u8 reg55val=0X00;
  	switch(bright)
	{
		case 0://-2
			reg55val=0XB0;	 	 
			break;	
		case 1://-1
			reg55val=0X98;	 	 
			break;	
		case 3://1
			reg55val=0X18;	 	 
			break;	
		case 4://2
			reg55val=0X30;	 	 
			break;	
	}
	SCCB_WR_Reg(0X55,reg55val);	
}

//0:-2
//1:-1
//2,0
//3,1
//4,2
void OV7670_Contrast(u8 contrast)
{
	u8 reg56val=0X40;//default  contrast=2
  	switch(contrast)
	{
		case 0://-2
			reg56val=0X30;	 	 
			break;	
		case 1://-1
			reg56val=0X38;	 	 
			break;	
		case 3://1
			reg56val=0X50;	 	 
			break;	
		case 4://2
			reg56val=0X60;	 	 
			break;	
	}
	SCCB_WR_Reg(0X56,reg56val);	
}
	    
void OV7670_Special_Effects(u8 eft)
{
	u8 reg3aval=0X04;
	u8 reg67val=0XC0;
	u8 reg68val=0X80;
	switch(eft)
	{
		case 1:
			reg3aval=0X24;
			reg67val=0X80;
			reg68val=0X80;
			break;	
		case 2:
			reg3aval=0X14;
			reg67val=0X80;
			reg68val=0X80;
			break;	
		case 3:
			reg3aval=0X14;
			reg67val=0Xc0;
			reg68val=0X80;
			break;	
		case 4:
			reg3aval=0X14;
			reg67val=0X40;
			reg68val=0X40;
			break;	
		case 5:
			reg3aval=0X14;
			reg67val=0X80;
			reg68val=0XC0;
			break;	
		case 6:
			reg3aval=0X14;
			reg67val=0XA0;
			reg68val=0X40;
			break;	 
	}
	SCCB_WR_Reg(0X3A,reg3aval);
	SCCB_WR_Reg(0X68,reg67val);
	SCCB_WR_Reg(0X67,reg68val);
}	

void OV7670_Window_Set(u16 sx,u16 sy,u16 width,u16 height)
{
	u16 endx;
	u16 endy;
	u8 temp; 
	
	
	endx=(sx+width*2)%784;	//   sx:HSTART endx:HSTOP    
 	endy=sy+height*2;		//   sy:VSTRT endy:VSTOP		
	
	temp=SCCB_RD_Reg(0X32);				
	temp&=0XC0;
	temp|=((endx&0X07)<<3)|(sx&0X07);	
	SCCB_WR_Reg(0X032,temp);
	SCCB_WR_Reg(0X17,sx>>3);			
	SCCB_WR_Reg(0X18,endx>>3);			

	temp=SCCB_RD_Reg(0X03);				
	temp&=0XF0;
	temp|=((endy&0X03)<<2)|(sy&0X03);
	SCCB_WR_Reg(0X03,temp);				
	SCCB_WR_Reg(0X19,sy>>2);			
	SCCB_WR_Reg(0X1A,endy>>2);			


}


























