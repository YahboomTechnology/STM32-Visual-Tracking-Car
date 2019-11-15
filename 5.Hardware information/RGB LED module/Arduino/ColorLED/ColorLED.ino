/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         ColorLED.c
* @author       Danny
* @version      V1.0
* @date         2017.07.25
* @brief        ColorLED
* @details
* @par History  
*/

#define ON 1     
#define OFF 0    

int LED_R = 11;  //LED_R is connected to the port 11 on the arduino uno
int LED_G = 10;  //LED_G is connected to the port 10 on the arduino uno
int LED_B =  9;  //LED_B is connected to the port 9 on the arduino uno

/**
* Function       setup
* @author        Danny
* @date          2017.07.25
* @brief         initialization configure
* @param[in]     void
* @retval        void
* @par History   
*/
void setup()
{
  //Initialize the IO port of the RGB module as the output mode
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

/**
* Function       color_led
* @author        Danny
* @date          2017.07.25
* @brief         7 different colors formed by different combinations of R,G and B
* @param[in1]    Red
* @param[in2]    Green
* @param[in3]    Blue
* @retval        void
* @par History   
*/
void color_led(int v_iRed, int v_iGreen, int v_iBlue)
{
  if (v_iRed == ON)
  {
    digitalWrite(LED_R, HIGH);
  }
  else
  {
    digitalWrite(LED_R, LOW);
  }

  if (v_iGreen == ON)
  {
    digitalWrite(LED_G, HIGH);
  }
  else
  {
    digitalWrite(LED_G, LOW);
  }

  if (v_iBlue == ON)
  {
    digitalWrite(LED_B, HIGH);
  }
  else
  {
    digitalWrite(LED_B, LOW);
  }
}

/**
* Function       loop
* @author        Danny
* @date          2017.07.25
* @brief         Delay 2s, Display 7 color LED
* @param[in]     void
* @retval        void
* @par History   
*/
void loop()
{
  delay(2000);

  while (1)
  {                          //LED_R    LED_G    LED_B
    color_led(ON, OFF, OFF); //   1        0        0
    delay(1000);
    color_led(OFF, ON, OFF); //   0        1        0
    delay(1000);
    color_led(OFF, OFF, ON); //   0        0        1
    delay(1000);
    color_led(ON, ON, OFF);  //   1        1        0
    delay(1000);
    color_led(ON, OFF, ON);  //   1        0        1
    delay(1000);
    color_led(OFF, ON, ON);  //   0        1        1
    delay(1000);
    color_led(ON, ON, ON);   //   1        1        1
  }
}



