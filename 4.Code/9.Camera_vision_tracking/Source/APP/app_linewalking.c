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
//If the linewalking effect is not good, you can modify dir_p and dir_d appropriately.
#define dir_d     0.16//d  0.2       0.16   //0.16


float fla_cha=0;    
int offset,suducha;//offset is the current car has a deviation from the center line
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
extern u8 ov_sta;	//It is defined in the exit.c
extern int nextblack;
int t=0;
int fz=120,zhongzhi=80;
//fz is image binarization threshold, zhongzhi is Median value of the car
////If the linewalking effect is not good, you can modify fz and zhongzhi appropriately.
u8 date[80][240]={0};//This array is the pixel point taken by the camera.
u8 black_line[80]={0};
//After processing the data captured by the camera, find the black line on the ground and store it in this array.
u8 dis_image[64][128]={0};////This array is the OLED display
void UART1SendByte();
extern void LCD_PrintImage(u8 *pucTable, u16 usRowNum, u16 usColumnNum);
//Display the image captured by the camera
/**
* Function       dis_play_image
* @author        john
* @date          2018.09.26    
* @brief         //The image taken by the camera is 240*80 pixels, 
*                //only 128*64 points are displayed here, we need to compress the data.
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void dis_play_image()
{
  
    int i=0,j=0,n=0,m=0;
		for(i=0;i<64;i++)
			for(j=0;j<128;j++)//Clear the array
			{
				dis_image[i][j]=0;
			}
     for(i=0,m=79;i<64;i++,m--) 
			//The image captured by the camera uses only the first 80 lines in the code, 
			//but the OLED can only display 64 lines, so here we need to extract 64 lines.
     {
       for(j=0,n=0;j<240,n<=127;j++)
          {					
            if(j<=56)//Show one point every two points in the first 112 pixels
            {
                if(j%2==0)
                {
                   if(date[m][j]>=fz)
                     dis_image[i][n]=1;
                     n++;
                }
            
            }
						else if(j>56&&j<=72)//16 pixels in the middle are displayed in the last 112 pixels
            {
               if(date[m][j]>=fz)
                  dis_image[i][n]=1;
                   n++; 
            }
            else
            {
             if(j%2==0)//Show one point every two points
              {
                 if(date[m][j]>=fz)
                    dis_image[i][n]=1;
                    n++;
              }
            }   
          }
      }
   LCD_PrintImage((u8*)dis_image, 64, 128);//Data display on the OLED
}
/**
* Function       dir
* @author        john
* @date          2018.10.8    
* @brief         servo steering
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   NO
*/
void dir()
{	
  float dir_out=0;
  float fla_cha_old=0;
  fla_cha_old=fla_cha;
  fla_cha=offset;
  dir_out=fla_cha*dir_p;                 //p
  dir_out+=(fla_cha-fla_cha_old)*dir_d;  //d 
	suducha=abs(offset);//Adjust the speed according to the steering size of the servo (the size of the curve)
	speed=(65 -suducha/8);//Speed can be modified by yourself
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
 
* @par History   no
*/
void find_line()
{
	int i,j,black,line,d,zhijiao,last,a,b,c,q;
	q=0;
	for(i=0;i<80;i++)//Search center line of track
		{
			for(j=0;j<240;j++)//Search black line from left to right 
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
															else 		////Not clutter
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
									if((j-nextblack>70)||(nextblack-j>70))// When the white point found is very different from the previous black point,
										                                    //we need to judge whether it is a clutter.
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
				if(q==1)//If no line is found, take the value of the previous line
					black=nextblack;
					black_line[i]=black;			
		}		
		line=(black_line[0]+black_line[10]+black_line[20]+black_line[30]+black_line[50])/5;
		                          //Take the 5 values in the center line as the current position of the car
		if(t==1)
			{
				offset=(line-zhongzhi);//The line found is the left side of the ground black tape
			}
		else
			{
				
				offset=(line-zhongzhi-60);
				//The line found is the right side of the ground black tape, so you need to subtract 690, 
				//60 is the width of the tape, and the left side of the tape is taken as the benchmark.
			}	
}
/**
* Function       senddate
* @author        john
* @date          2018.10.8    
* @brief         Send the data to the host computer and display it
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void senddate()
{
	u16 a, b,c;
	for(a=0;a<80;a++)
		for(b=240;b>0;b--)
		{
			UART1SendByte(date[a][b]);
		}	
		UART1SendByte(0xff);//The data in the host computer protocol ends with 0xFF
}

//Setting frequency
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
* @brief         Camera image acquisition
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
		OV7670_RRST=0;				//Start resetting the read pointer
		OV7670_RCK_L;
		OV7670_RCK_H;
		OV7670_RCK_L;
		OV7670_RRST=1;				//Reset read pointer end
		OV7670_RCK_H;  
		if(ov7670_config.mode)
		{
				for(i=240; i>0; i--)//ov7670_config.height
				{
					for(j=0; j<320; j++)//ov7670_config.width
					{
						OV7670_RCK_L;
					   //color = (((GPIOB->IDR&0XFFFF)>>12)&0x0f)|(((GPIOC->IDR&0XFFFF)>>2)&0xF0);	//Read data
						color = (((GPIOB->IDR&0XFF00)>>8)&0xff);
						OV7670_RCK_H;
						OV7670_RCK_L;// YUYV is set OUT,The second byte is not used, so there is no need to read
						OV7670_RCK_H;
						if((j>=50 && j<130) && (i>=0 && i<240))//80*240	
						{	
								date[j-50][i-0]=color;
						} 
					}					
				}
		}		
			
		EXTI_ClearITPendingBit(EXTI_Line8);  //Clear interrupt flag of LINE8
		ov_sta=0;					                   //Start next acquisition
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
* @par History   no
*/
void app_LineWalking(void)
{
		camera_refresh();//Update camera information
		find_line();     //Processing camera data
		dis_play_image();//Display image on the OLED
		dir();           //SERVO
		MiniCar_Run(speed);
}
