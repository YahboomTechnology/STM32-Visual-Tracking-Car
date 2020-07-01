/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_ultrasonic.c
* @author       liusen
* @version      V1.0
* @date         2015.01.03
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/

#include "stm32f10x.h"
#include "app_bluetooth.h"
#include "bsp_ultrasonic.h"
#include "bsp_servo.h"
#include "sys.h"
#include "app_motor.h"
#include "delay.h"
#include "protocol.h"
#include "bsp.h"
#include "app_ultrasonic.h"
//#include "app_colormode.h"
#include "exti.h"
#include "ov7670.h"
#include "bsp_colorful.h"
#include<math.h>
#include<stdlib.h>
#define dir_p     0.2 //p   0.2    0.18
#define dir_d     0.16//d  0.2       0.16

float Distance_test(void);
float bsp_getUltrasonicDistance0(void);
int g_modeSelect = 0;  
u8 g_Boolfire = 0;	    
float fla_cha=0;    //

int offset,suducha;
extern int speed;
u8 youzhijiao=0,zuozhijiao=0;
/*****************OV7670************************/
extern u8 ov_sta;	
extern int nextblack;
int fz=120,zhongzhi=100;
u8 date[80][240]={0};
u8 black_line[5]={0};
u8 dis_image[64][128]={0};//  64   128
void UART1SendByte(unsigned char SendData);
extern void LCD_PrintImage(u8 *pucTable, u16 usRowNum, u16 usColumnNum);

/**
* Function       dis_play_image
* @author        john
* @date          2018.09.26    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History  
*/
void dis_play_image()
{
  
    int i=0,j=0,n=0,m=0;
		for(i=0;i<64;i++)
			for(j=0;j<128;j++)
			{
				dis_image[i][j]=0;
			}
     for(i=0,m=79;i<64;i++,m--)   //
     {
       for(j=0,n=0;j<220;j++)
          {					
            if(j<=92)
            {
                if(j%2==0)
                {
                   if(date[m][j]>=fz)
                     dis_image[i][n]=1;
									 if(n<=127)
										{
											n++;
										}	
                }
            
            }
						else if(j>92&&j<=128)
            {
               if(date[m][j]>=fz)
                  dis_image[i][n]=1;
							 if(n<=127)
								{
									n++;
								}	
            }
            else
            {
             if(j%2==0)
              {
                 if(date[m][j]>=fz)
                    dis_image[i][n]=1;
								 if(n<=127)
									{
										n++;
									}	
              }
            }   
          }
      }
   LCD_PrintImage((u8*)dis_image, 64, 128);
}

/**
* Function       dir
* @author        john
* @date          2017.07.20    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void dir()
{
	
  float dir_out=0;
  float fla_cha_old=0;
  fla_cha_old=fla_cha;
  fla_cha=offset;
  dir_out=fla_cha*dir_p;                 //p
  dir_out+=(fla_cha-fla_cha_old)*dir_d;  //d 
	suducha=abs(offset);
	speed=(3200-suducha*8);//3500
  dir_out+=zhongzhi;
	if(dir_out>130)
			dir_out=130;
		if(dir_out<55)
			dir_out=55;
				Angle_J1=dir_out;
}

/**
* Function       find_line
* @author        john
* @date          2017.07.20    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void find_line()
{
	int i,j,black,line,last,t;//d,zhijiao,a,b,c,
	for(i=0;i<5;i++)
		{
			for(j=0;j<240;j++)
				{
					//if((date[i][j]>fz&&date[i][j+3]>fz&&date[i][j+5]<fz&&date[i][j+7]<fz)||(date[i][j]<fz&&date[i][j+3]<fz&&date[i][j+5]>fz&&date[i][j+7]>fz))
					if(date[i][j]<fz&&date[i][j+4]<fz)
						{		
							if((j-nextblack>90)||(nextblack-j>90))//70
								{
						//  black=nextblack;
						//	break;
									last=j;
									for(j=0;j<240;j++)
										{	
											//	if((date[i+5][j]>fz&&date[i+5][j+3]>fz&&date[i+5][j+5]<fz&&date[i+5][j+7]<fz)||(date[i+5][j]<fz&&date[i+5][j+3]<fz&&date[i+5][j+5]>fz&&date[i+5][j+7]>fz))
												if(date[i][j]<fz&&date[i][j+4]<fz)
														{		
															if((j-last>90)||(last-j>90))//70
																{
																	black=nextblack;
																	break;
																}
															else 
																{
																	black=j+1;
																	break;
																}
																	
														}
										}
										break;
								}
								else
									{
										black=j+1;
										nextblack=black;
										break;
									}
						}
								
						
						if(j==238)
						{
							black=nextblack;
							//printf("%d  %d\r\n",i,nextblack);
						}
					t=1;
				}
		//	printf("%d  %d\r\n",i,black);
				if(black<3)
					{
					for(j=0;j<240;j++)
						{
							//if((date[i][j]>fz&&date[i][j+3]>fz&&date[i][j+5]<fz&&date[i][j+7]<fz)||(date[i][j]<fz&&date[i][j+3]<fz&&date[i][j+5]>fz&&date[i][j+7]>fz))
							if(date[i][j]<fz&&date[i][j+4]<fz&&date[i][6]>fz&&date[i][j+8]>fz)
								{		
									if((j-nextblack>70)||(nextblack-j>70))
										{
								//  black=nextblack;
								//	break;
											last=j;
											for(j=0;j<240;j++)
												{	
													//	if((date[i+5][j]>fz&&date[i+5][j+3]>fz&&date[i+5][j+5]<fz&&date[i+5][j+7]<fz)||(date[i+5][j]<fz&&date[i+5][j+3]<fz&&date[i+5][j+5]>fz&&date[i+5][j+7]>fz))
														if(date[i][j]<fz&&date[i][j+4]<fz&&date[i][6]>fz&&date[i][j+8]>fz)
																{		
																	if((j-last>70)||(last-j>70))
																		{
																			black=nextblack;
																			break;
																		}
																	else 
																		{
																			black=j+1;
																			break;
																		}
																			
																}
												}
												break;
										}
										else
											{
												black=j+1;
												nextblack=black;
												break;
											}
								}
										
								
								if(j==238)
								{
									black=nextblack;
									//printf("%d  %d\r\n",i,nextblack);
								}
						}
						t=0;
					}				
					black_line[i]=black;			
		}		
		line=(black_line[0]+black_line[1]+black_line[2]+black_line[3]+black_line[4])/5;
		if(t==1)
			{
				offset=(zhongzhi-line);//zhongzhi-line;Angle_J1
			}
		else
			{
				
				offset=(zhongzhi-line-50);//zhongzhi-line;Angle_J1
			}

}

/**
* Function       senddate
* @author        john
* @date          2017.07.20    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void senddate()
{
	u16 a, b;//,c;
	for(a=0;a<80;a++)
		for(b=220;b>0;b--)
			{
				UART1SendByte(date[a][b]);
			}	
		UART1SendByte(0xff);
}

void ov7670_clock_set(u8 PLL) 
{ 
	u8 temp=0;	  
	RCC->CFGR&=0XFFFFFFFC;	
	RCC->CR&=~0x01000000;  	  
	RCC->CFGR&=~(0XF<<18);	
	PLL-=2; 
	RCC->CFGR|=PLL<<18;   	
	RCC->CFGR|=1<<16;	  	//PLLSRC ON  
	FLASH->ACR|=0x12;	   
	RCC->CR|=0x01000000;  	//PLLON 
	while(!(RCC->CR>>25));	
	RCC->CFGR|=0x02;	
	while(temp!=0x02)     
	{    
		temp=RCC->CFGR>>2; 
		temp&=0x03; 
	}   
}

/**
* Function       camera_refresh
* @author        john
* @date          2017.07.20     
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/

void camera_refresh()
{
	u32 i,j;
	u8 color;
//	u8 A0=0,A1=0,A2=0,A3=0,A4=0,A5=0,A6=0,A7=0;
	if(ov_sta==2)
	{
//		LCD_Scan_Dir(U2D_L2R);		
//		LCD_SetCursor(0x00,0x0000);	
//		LCD_WriteRAM_Prepare();     
		OV7670_RRST=0;				
		OV7670_RCK_L;
		OV7670_RCK_H;
		OV7670_RCK_L;
		OV7670_RRST=1;				
		OV7670_RCK_H;  
		if(ov7670_config.mode)
			{
				for(i=240; i>0; i--)//ov7670_config.height
				{
					for(j=0; j<320; j++)//ov7670_config.width
					{
						OV7670_RCK_L;
						color = (((GPIOB->IDR&0XFFFF)>>12)&0x0f)|(((GPIOC->IDR&0XFFFF)>>2)&0xF0);	//¶ÁÊý¾Ý
						OV7670_RCK_H;
						OV7670_RCK_L;
						OV7670_RCK_H;
						//LCD->LCD_RAM=GRAY_2_RGB565(color); 
						if((j>=50&&j<130)&&(i>=1&&i<240))//100*100		//110   210    70    170    /////////220
							{	
								if(color>fz) 
									color=0xfe;
								else
									color=0x00;
								date[j-50][i-0]=color;
							} 
					}
					
				}
			}		
			
		EXTI_ClearITPendingBit(EXTI_Line8);  
		ov_sta=0;				
	} 
	
}	
void serial_data_postback()
{
	//$4WD,CSB120,PV8.3,GS214,LF1011,HW11,GM11#
	float csbLen=0.0f, power; 
	u16 gs=0, lf=0; 
	u8 hw=0, gm=0;
//	int Ll1, Rr1;
	csbLen= bsp_getUltrasonicDistance0();
	//csbLen =(int)Distance_test();
	power = Get_Battery_Volotage();
	//gs = Get_GS_Value();
	//lf = bsp_GetLineWalking_Data();
	//hw = bsp_GetIRavoid_Data();
	//bsp_GetLightSeeking(&Ll1, &Rr1);
	//gm = Ll1 * 10 + Rr1;
	//printf("hhhh");
	printf("$4WD,CSB%.2f,PV%1.2f,GS%d,LF%04d,HW%02d,GM%02d#",csbLen, power, gs, lf, hw, gm);																				
	return;
}

/**
* Function       app_bluetooth_deal
* @author        liusen
* @date          2017.07.20    
* @brief       
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History  
*/
void app_bluetooth_deal(void)
{
	if (newLineReceived)
   	{
		Protocol();
  	}
	switch (g_modeSelect)
	{
		case 1: break; 								
		case 2: ; break; 		
		case 3: ;app_ultrasonic_mode0();  break;  	
		case 4: bsp_Colorful_Control(1, 1, 1); break; 
	//	case 5: app_LightSeeking(); break;  	
	//	case 6: app_IRFollow(); break;  		
		default:break;
	}
	
	if (g_modeSelect == 0 && g_Boolfire == 0)
	{
		if (g_count >= 100000)
		{ 
			g_count = 0;
			//printf("shijiandao ");
			serial_data_postback();
		}		
	}

}
