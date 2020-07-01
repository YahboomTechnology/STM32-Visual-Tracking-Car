/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_ultrasonic.c
* @author       liusen
* @version      V1.0
* @date         2015.01.03
* @brief        
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/

#include "app_ultrasonic.h"
#include "bsp_ultrasonic.h"
#include "bsp_servo.h"
#include "sys.h"
#include "app_motor.h"
#include "delay.h"
#include "stdio.h"
#include "oled.h"


float Distance_test(void);


/**
* Function       app_ultrasonic_mode
* @author        liusen
* @date          2017.07.20    
* @brief        
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void app_ultrasonic_modeshow(void)
{
	int Len = 0;
	u8 shi,ge,bai;
	Len = bsp_getUltrasonicDistance(); 
  if(Len>500)
	Len=0;
	bai=Len/100+0x30;
	shi=(Len%100)/10+0x30;
	ge=Len%10+0x30;
	LCD_Print(8, 36,&bai,TYPE16X16,TYPE8X16);
	LCD_Print(16, 36,&shi,TYPE16X16,TYPE8X16);
	LCD_Print(24, 36,&ge,TYPE16X16,TYPE8X16);
	LCD_Print(40, 36,"CM",TYPE16X16,TYPE8X16);
	
	
}

/**
* Function       app_ultrasonic_mode
* @author        liusen
* @date          2017.07.20    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void app_ultrasonic_mode0(void)
{
	int Len = 0;

	Len = bsp_getUltrasonicDistance(); 
	
	//printf("CSB:%d \r\n", Len);  	

	if(Len < 25)
    { 
			Angle_J1 = 130;
			MiniCar_Run(300);
			delay_ms(1000);
			Angle_J1 = 90;
    }
  else 
		{
		MiniCar_Run(300); 
		}
	
}

/**
* Function       app_ultrasonic_servo_mode
* @author        liusen
* @date          2017.07.20    
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void app_ultrasonic_servo_modeaaaa(void)
{
	int Len = 0;
	int LeftDistance = 0, RightDistance = 0;

	//Len = (u16)bsp_getUltrasonicDistance0();

    if(Len <= 50)
    {

	//	Car_Stop();
		
		Angle_J1 = 180;		
		delay_ms(500); 
		Len = bsp_getUltrasonicDistance();			
		LeftDistance = Len;	  
	 
		Angle_J1 = 0;		
		delay_ms(500); 
		Len = bsp_getUltrasonicDistance();					
		RightDistance = Len;


		Angle_J1 = 90;		
		delay_ms(500); 

		if((LeftDistance < 30 ) &&( RightDistance < 30 ))
		{
		//	Car_SpinRight(6000, 5000);
			delay_ms(500); 
		}
		else if(LeftDistance >= RightDistance)
		{      
		//	Car_SpinLeft(6000, 5000);
			delay_ms(500); 
		}
		else
		{
		//	Car_SpinRight(6000, 5000); 
			delay_ms(500); 
		}
    }
    else if(Len > 30)
    {
	//	Car_Run(5000); 	 
    }
}
void app_ultrasonic_mode(void)
{
//	int speeda=4500;
	int Len = 0;
//	int LeftDistance = 0, RightDistance = 0;

	Len = (u16)Distance_test();

//	printf("%d\r\n",Len);
    if(Len <= 40)
    {
		//	Car_Stop();
			Angle_J1 = 55;		
		//	Car_Back(speeda);
			delay_ms(6000); 
			delay_ms(6000); 
			delay_ms(6000); 
		//	Car_Stop();
			Angle_J1 = 120;	
		//	Car_Run(speeda); 
			delay_ms(6000); 
			delay_ms(6000); 
			delay_ms(6000); 
			Angle_J1 = 90;	
			/*Car_Stop();
			
			Angle_J1 = 120;		
			delay_ms(500);
			Len = Distance_test();			
			LeftDistance = Len;	  
		 
			Angle_J1 = 55;	
			delay_ms(500); 
			Len = Distance_test();					
			RightDistance = Len;


			Angle_J1 = 90;	
			delay_ms(500); 

			if((LeftDistance < 35 ) &&( RightDistance < 35 ))
			{
			//	Car_SpinRight(3000, 2000);
				Angle_J1 = 120;
				Car_Back(speeda);
				delay_ms(2500);
				Angle_J1 = 60;
				Car_Run(speeda); 
				delay_ms(3000); 
				Angle_J1 = 90;
				Car_Run(speeda);
				delay_ms(500); 
			}
			else if(LeftDistance >= RightDistance)
			{      
			//	Car_SpinLeft(3000, 2000);
				Angle_J1 = 120;
				Car_Run(speeda); 
				delay_ms(5000); 
				Angle_J1 = 90;
			}
			else
			{
			//	Car_SpinRight(3000, 2000);
				Angle_J1 = 60;
				Car_Run(speeda); 
				delay_ms(5000); 
				Angle_J1 = 90;
			}*/
    }
    else if(Len > 40)
    {
			;
	//	Car_Run(speeda); 	 
    }
}
