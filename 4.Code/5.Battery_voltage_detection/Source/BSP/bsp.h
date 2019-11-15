

#ifndef __BSP_H__
#define __BSP_H__

#include "delay.h"
#include "bsp_gpio.h"
#include "bsp_servo.h"
#include "bsp_timer.h"
#include "usart.h"

void bsp_init(void);


#define USE_SERVO_J1
//#define USE_SERVO_J2
//#define USE_SERVO_J3
//#define USE_SERVO_J4
//#define USE_SERVO_J5
//#define USE_SERVO_J6


#define USE_LINE_L1
#define USE_LINE_L2
#define USE_LINE_R1
#define USE_LINE_R2


#define USE_IRAVOID_L1
#define USE_IRAVOID_R1

#define USE_COLOR_RED
#define USE_COLOR_GREEN
#define USE_COLOR_BLUE


#define USE_LIGHTSEEKING_L1
#define USE_LIGHTSEEKING_R1

#define USE_ULTRASONIC

#define USE_BUZZER


#define USE_FIRE


#define USE_GS


#endif
