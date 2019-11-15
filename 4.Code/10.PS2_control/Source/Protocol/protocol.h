

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "delay.h"
#include "bsp_gpio.h"
#include "bsp_servo.h"
#include "bsp_timer.h"
#include "bsp_ultrasonic.h"
#include "usart.h"
#include "bsp_adc.h"

enum{

  enSTOP = 0,
  enRUN,
  enBACK,
  enLEFT,
  enRIGHT,
  enUPLEFT,
  enUPRIGHT,
  enDOWNLEFT,
  enDOWNRIGHT,  
  enTLEFT,
  enTRIGHT

};

extern int g_CarState; 
extern int CarSpeedControl;

void Protocol(void);



#endif
