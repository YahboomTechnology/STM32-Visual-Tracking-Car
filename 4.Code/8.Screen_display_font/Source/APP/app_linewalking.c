/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_linewalking.c	
* @author       john
* @version      V1.0
* @date         2018.10.18
* @brief        
* @details      
* @par History  
*                 
* version:		john_20181018
*/

#include "app_motor.h"
#include "delay.h"
#include "protocol.h"
#include "bsp.h"
#include "app_linewalking.h"
#include "app_ultrasonic.h"
#include "app_colormode.h"
#include "exti.h"
#include "ov7670.h"
#include "lcd.h"
#include "led.h" 
#include "app_linewalking.h"
#include "bsp_linewalking.h"
#include "sys.h"
#include "app_motor.h"
#include "delay.h"
#include<math.h>


#define dir_p     0.19 //p   0.2    0.18    //0.19
#define dir_d     0.16//d  0.2       0.16   //0.16


float fla_cha=0;     //
int offset,suducha; //offset is car and center line deviation
extern int speed;  


/**
* Function       app_LineWalking0
* @author        Sax_john
* @date          2018.10.28    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void app_LineWalking0(void)
{
	
}
/*****************OV7670************************/

extern u8 ov_sta;	//Defined in the exit.c file
extern int nextblack;
int t=0;
int fz=120,zhongzhi=80;
u8 date[80][240]={0};
u8 black_line[80]={0};
u8 dis_image[64][128]={0};


void UART1SendByte();
extern void LCD_PrintImage(u8 *pucTable, u16 usRowNum, u16 usColumnNum);


/**
* Function       dis_play_image
* @author        john
* @date          2018.09.26    
* @brief         
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
     for(i=0,m=79;i<64;i++,m--)
     {
       for(j=0,n=0;j<240,n<=127;j++)
          {					
            if(j<=56)
            {
                if(j%2==0)
                {
                   if(date[m][j]>=fz)
                     dis_image[i][n]=1;
                     n++;
                }
            
            }
						else if(j>56&&j<=72)
            {
               if(date[m][j]>=fz)
                  dis_image[i][n]=1;
                   n++; 
            }
            else
            {
             if(j%2==0)
              {
                 if(date[m][j]>=fz)
                    dis_image[i][n]=1;
                    n++;
              }
            }   
          }
      }
   LCD_PrintImage((u8*)dis_image, 64, 128);
}

/**
* Function       dir
* @author        john
* @date          2018.10.8    
* @brief         
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
	speed=(65 -suducha/8);//3500 70
  dir_out+=zhongzhi;
	if(dir_out>110)
		dir_out=110;
	if(dir_out<55)
		dir_out=55;
		Angle_J1=dir_out;
}

/**
* Function       find_line
* @author        john
* @date          2018.10.8    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
 
* @par History   
*/

void find_line()
{
	int i,j,black,line,d,zhijiao,last,a,b,c,q;
	q=0;
	for(i=0;i<80;i++)
		{
			for(j=0;j<240;j++)
				{
					if((j+4) < 240 && date[i][j] < fz && date[i][j+4] < fz)//Think of a black line when two consecutive black dots are found
						{		
							if((j-nextblack > 90)||(nextblack-j > 90))//When the black point found is very different from the previous black point, we need to judge whether it is a clutter.
								{
									last=j;//Record this black dots
									for(j=0;j<236;j++)
										{	
												if( (i+5) < 80 && date[i+5][j] < fz && date[i+5][j+4] < fz)//Determine if the black point in the first five lines deviates from this point
														{		
															if((j-last>90)||(last-j>90))//The difference between the first five lines and this point is very large, 
																                         //which means that it is clutter, then this is filtered out. 
															                           //The x coordinate of this point is consistent with the previous one.
																{
																	black=nextblack;
																	break;
																}
															else 		//Not clutter
																{
																	black=j+1;
																	nextblack=black;
																	t=1;
																	break;
																}
																	
														}
										}
										break;
								}
								else//This is a black line
									{
										black=j+1;
										nextblack=black;
										t=1;
										break;
									}
						}
								
						
						if(j==238)//When the 238 line is found or the black line is not found, 
							        //it means that there is no black line in the this line, 
						          //then, the x coordinate of this point is also used in the previous line.
						{
							q=1;
						}
						
				}
				if(black==1)//When the first point is a black line, we need to find the right side of the black line
					{
					for(j=0;j<236;j++)
						{
						if(date[i][j] > fz && date[i][j+4] > fz)//Find two consecutive white spots	
							{		
									if((j-nextblack>70)||(nextblack-j>70))// When the white point found is very different from the previous black point, we need to judge whether it is a clutter.
										{
											last=j;
											for(j=0;j<236;j++)
												{	
													if((i+5) < 80 && date[i+5][j] > fz && date[i+5][j+4] > fz)//The difference between the first five lines and this point is very large, 
																                                                    //which means that it is clutter, then this is filtered out. 
															                                                      //The x coordinate of this point is consistent with the previous one.
													{		
																	if((j-last>70)||(last-j>70))
																		{
																			black=nextblack;
																			break;
																		}
																	else 
																		{
																			black=j+1;
																			nextblack=black;
																			t=0;
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
												t=0;
												break;
											}
								}
						}
					}		
				if(q==1)
					black=nextblack;
					black_line[i]=black;			
		}		
		line=(black_line[0]+black_line[10]+black_line[20]+black_line[30]+black_line[50])/5;//取中线当中的5个值作为小车的当前位置
		if(t==1)
			{
				offset=(line-zhongzhi);
			}
		else
			{
				
				offset=(line-zhongzhi-60);
			}	
}

/**
* Function       senddate
* @author        john
* @date          2018.10.8    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void senddate()
{
	u16 a, b,c;
	for(a=0;a<80;a++)
		for(b=240;b>0;b--)
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
* @date          2018.10.8    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void camera_refresh()
{
	u32 i,j;
	u8 color;
	if(ov_sta==2)
	{
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
					//	color = (((GPIOB->IDR&0XFFFF)>>12)&0x0f)|(((GPIOC->IDR&0XFFFF)>>2)&0xF0);	
						color = (((GPIOB->IDR&0XFF00)>>8)&0xff);
						OV7670_RCK_H;
						OV7670_RCK_L;
						OV7670_RCK_H;
						if((j>=50 && j<130) && (i>=0 && i<240))//80*240	
						{	
								date[j-50][i-0]=color;
						} 
					}					
				}
		}		
			
		EXTI_ClearITPendingBit(EXTI_Line8);  
		ov_sta=0;					
	} 
}	

/**
* Function       app_LineWalking
* @author        john
* @date          2018.10.8    
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void app_LineWalking(void)
{
		camera_refresh();
		find_line();
		dis_play_image();
		dir();
		MiniCar_Run(speed);
}
