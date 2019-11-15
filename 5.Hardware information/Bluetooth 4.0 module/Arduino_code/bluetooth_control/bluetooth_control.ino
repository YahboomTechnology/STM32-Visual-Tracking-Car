/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bluetooth_control.c
* @author       Danny
* @version      V1.0
* @date         2017.07.25
* @brief        Bluetooth intelligent vehicle control experiment (no tracking)
* @details
* @par History  See the following instructions
*
*/
#define run_car     '1'
#define back_car    '2'
#define left_car    '3'
#define right_car   '4'
#define stop_car    '0'

#define ON 1           //enableLED
#define OFF 0          //prohibitLED

/*Enumeration of car motion state*/
enum {
  enSTOP = 0,
  enRUN,
  enBACK,
  enLEFT,
  enRIGHT,
  enTLEFT,
  enTRIGHT
} enCarState;

//Define pin
int Left_motor_go = 8;    //(AIN1)
int Left_motor_back = 7;  //(AIN2)
int Right_motor_go = 2;   //(BIN1)
int Right_motor_back = 4; //(BIN2)
int Left_motor_pwm = 6;   //PWMA
int Right_motor_pwm = 5;  // PWMB

//Define infrared tracking pin
//TrackSensorLeftPin1 TrackSensorLeftPin2 TrackSensorRightPin1 TrackSensorRightPin2
//      A2                  A1                  A3                   A4
const int TrackSensorLeftPin1  =  A2;  //Define the left first infrared tracking sensor pin A2
const int TrackSensorLeftPin2  =  A1;  //Define the left second  infrared tracking sensor pin 1
const int TrackSensorRightPin1 =  A3;  //Define the right first  infrared tracking sensor pin A3
const int TrackSensorRightPin2 =  A4;  //Define the right second  infrared tracking sensor pin A4

//Define variables to store data collected by infrared tracking sensors
bool TrackSensorLeftValue1;
bool TrackSensorLeftValue2;
bool TrackSensorRightValue1;
bool TrackSensorRightValue2;

String infrared_track_value = "0000";

/*Define obstacle avoidance sensor pin and variables*/
const int AvoidSensorLeft =  A3;   //Define left infrared obstacle avoidance sensor pin A3
const int AvoidSensorRight = A1;   //Define right infrared obstacle avoidance sensor pin A1
const int FollowSensorLeft =  A3;   //Define left infrared following sensor pin A3
const int FollowSensorRight = A1;   //Define left infrared following sensor pin A3

int LeftSensorValue ;              //Define variables to store data collected by infrared sensors
int RightSensorValue ;
String infrared_avoid_value = "00";

/*Define photosensitive resistor pin and variables*/
const int LdrSensorLeft =  A4;   //Define left photosensitive resistor pin A4
const int LdrSensorRight = A2;   //Define right photosensitive resistor pin A2

int LdrSersorLeftValue ;         //Define variables to store data collected by photosensitive resistor

int LdrSersorRightValue ;
String LDR_value = "00";


int buzzer = A0;                //Set the control buzzer pin to A0

/*Color recognition pin and variable settings*/
int LDR_pin = A5;
int position = 0; //colorful searchlight

/*Voltage pin and its variable settings*/
int VoltagePin = A0;
int VoltageValue = 0;


int CarSpeedControl = 150;

int ServoPin = 3;

int EchoPin = 12;       
int TrigPin = 13;        
float distance = 0;

//Define pin
int LED_R = 11;     //LED_R connect interface 11 on the arduino
int LED_G = 10;     //LED_G connect interface 10 on the arduino
int LED_B = 9;      //LED_B connect interface 9 on the arduino

int OutfirePin = A5;

/*color value*/
int red, green, blue;

/*Time variable for delay*/
int time = 20000;
int count = 10;

/*Serial data setting*/
int IncomingByte = 0;            
String InputString = "";        
boolean NewLineReceived = false; 
boolean StartBit  = false;       
String ReturnTemp = ""; 

/*State machine state*/
int g_CarState = enSTOP;         //1run 2back 3left 4right 0stop
int g_modeSelect = 0;  //0:Default state;  1:infrared remote control
                      //2:Tracking module  3:Ultrasonic obstacle avoidance 
                      //4: Colorful searchlight  5: seek light module 6:Infrared following 
boolean g_motor = false;

/*Voltage detection look-up table defines array (voltage value, analog value read by A0 port)*/
float voltage_table[21][2] =
{
  {6.46, 676}, {6.51, 678}, {6.61, 683}, {6.72, 687}, {6.82, 691}, {6.91, 695}, {7.01, 700}, {7.11, 703},
  {7.20, 707}, {7.31, 712}, {7.4, 715}, {7.5, 719}, {7.6, 723}, {7.7, 728}, {7.81, 733}, {7.91, 740},
  {8.02, 741}, {8.1, 745}, {8.22, 749}, {8.30, 753}, {8.4, 758}
};

int serial_putc( char c, struct __file * )
{
  Serial.write( c );
  return c;
}
void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}

/**
* Function       setup
* @author        Danny
* @date          2017.07.25
* @brief         Initialization configuration
* @param[in]     void
* @retval        void
* @par History   no
*/
void setup()
{
  //Serial baud rate setting
  Serial.begin(9600);
  printf_begin();
  //Initialize the motor PIN IO 
  pinMode(Left_motor_go, OUTPUT);
  pinMode(Left_motor_back, OUTPUT);
  pinMode(Right_motor_go, OUTPUT);
  pinMode(Right_motor_back, OUTPUT);

  //Define four road tracking infrared sensor as input interface
  pinMode(TrackSensorLeftPin1, INPUT);
  pinMode(TrackSensorLeftPin2, INPUT);
  pinMode(TrackSensorRightPin1, INPUT);
  pinMode(TrackSensorRightPin2, INPUT);

  //Define infrared pin as input mode
  pinMode(AvoidSensorLeft, INPUT);
  pinMode(AvoidSensorRight, INPUT);
  pinMode(FollowSensorLeft, INPUT);
  pinMode(FollowSensorRight, INPUT);
  pinMode(LdrSensorLeft, INPUT);
  pinMode(LdrSensorRight, INPUT);

  //Define buzzer IO as output mode
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);

  //Define Ultrasonic pin
  pinMode(EchoPin, INPUT);   
  pinMode(TrigPin, OUTPUT);  

  //Define the outfire IO port as the output mode and initialize it
  pinMode(OutfirePin, OUTPUT);
  digitalWrite(OutfirePin, HIGH);

  //Initialize RGB pin as output interface
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);

  //Initialize the rudder pin as output mode
  pinMode(ServoPin, OUTPUT);
  
  randomSeed(analogRead(0));   //Set up a random number of student simulation mouth 0
}

/**
* Function       servo_pulse
* @author        Danny
* @date          2017.07.26
* @brief         A pulse function is defined to generate PWM values by simulation
*                the time base pulse is 20ms, and the high pulse level is at 0.5-2.5ms
*                control 0-180 degrees
* @param[in1]    ServPin
* @param[in2]    myangle
* @param[out]    void
* @retval        void
* @par History   no
*/
void servo_pulse(int ServoPin, int myangle)
{
  int PulseWidth;                   
  PulseWidth = (myangle * 11) + 500; 
  digitalWrite(ServoPin, HIGH);      
  delayMicroseconds(PulseWidth);     
  digitalWrite(ServoPin, LOW);       
  delay(20 - PulseWidth / 1000);     
  return;
}

/**
* Function       Distance_test
* @author        Danny
* @date          2017.07.26
* @brief         Ultrasonic ranging
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void Distance_test()
{
 digitalWrite(TrigPin, LOW);               //Give trigger pin low level 2 s
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);              //Give trigger pin high level 10us，Here is at least 10 us
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  float Fdistance = pulseIn(EchoPin, HIGH); // Read high level time (unit: ms)
  Fdistance = Fdistance / 58;
  //  Serial.print("Distance:");            //output distance (uint:cm)
  //  Serial.print(Fdistance);              //display distance
  //  Serial.println("cm");
  distance = Fdistance;
  return;
}

/**
* Function       voltage_test
* @author        Danny
* @date          2017.07.26
* @brief          voltage detection
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
float voltage_test()
{
  pinMode(VoltagePin, INPUT);           //Voltage sensing pin and buzzer pin A5 adjust pin mode to time-sharing multiplexing
  VoltageValue = analogRead(VoltagePin);//Read A0 port value and convert it to voltage value

  //Method 1: the voltage value is simulated by the circuit schematic and the A0 port
  //Serial.println(VoltageValue);
  //VoltageValue = (VoltageValue / 1023) * 5.02 * 1.75  ;
  //Voltage is port A0 collect value of ad（0-1023），
  //（R14+R15）/R15=1.75，R14=15K,R15=20K）。

/*Look-up table record open*/  
//  float voltage = 0;
//  voltage = VoltageValue;
//  return voltage;


  //Method 2: by measuring the analog value of A0 corresponding to 6.4-8.4v in advance, and then by look-up table method to determine its value
  //The error of this method is less than 0.1V
  int i = 0;
  float voltage = 0;
  if (VoltageValue > voltage_table[20][1])
  {
    voltage = 8.4;
    return voltage;
  }
  if (VoltageValue < voltage_table[0][1])
  {
    voltage = 6.4;
    return voltage;
  }
  for (i = 0; i < 20; i++)
  {
    if (VoltageValue >= voltage_table[i][1] && VoltageValue <= voltage_table[i + 1][1])
    {
      voltage =  voltage_table[i][0] + (VoltageValue - voltage_table[i][1]) * ((voltage_table[i + 1][0]
                 - voltage_table[i][0]) / (voltage_table[i + 1][1] - voltage_table[i][1]));
      return voltage;
    }
  }
  pinMode(VoltagePin, OUTPUT);
  digitalWrite(buzzer, HIGH);
  return 0;
}

/**
* Function       color_test
* @author        Danny
* @date          2017.07.26
* @brief        Color recognition test
* @param[in]     void
* @param[out]    void
* @retval        iIntensity
* @par History   no
*/
int color_test()
{
  int iIntensity;
  pinMode(LDR_pin, INPUT_PULLUP);   //The fire extinguishing pin and the gray level sensor pin are multiplexed with A5 ports, 
                                   // and the time division multiplexing is required by pin setting
  iIntensity = analogRead(LDR_pin); 
  //  Serial.print("Intensity = "); 
  //  Serial.println(iIntensity);
  pinMode(LDR_pin, OUTPUT);
  return iIntensity;
}

/**
* Function       color_dis
* @author        liusen
* @date          2017.08.26
* @brief         Color recognition test
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void color_dis()
{
  int Color = 0;
  Color = color_test();

  if (Color >= 370 && Color <= 410)
  {
    color_led_pwm(0, 0, 255);
  }
  else if (Color >= 300 && Color <= 320)
  {
    color_led_pwm(0, 255, 0);
  }
  else if (Color >= 345 && Color <= 365)
  {
    color_led_pwm(255, 0, 0);
  }
  else if (Color >= 330 && Color < 345)
  {
    color_led_pwm(255, 0, 255);
  }
  else if (Color >= 270 && Color <= 290)
  {
    color_led_pwm(0, 255, 255);
  }
  else if (Color >= 250 && Color < 270)
  {
    color_led_pwm(255, 255, 0);
  }
  else
  {
    color_led_pwm(0, 0, 0);
  }
}

/**
* Function       track_test
* @author        Danny
* @date          2017.07.26
* @brief        Tracking mode pin test
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
 // tracking and infrared obstacle avoidance module, search light multiplexing of A1, A2, A3, A4
 // acquisition of infrared obstacle avoidance and light seeking to disable tracking data acquisition
void track_test()
{
  //Check the black line tracking module light up, port LOW
  //Not check the black line tracking module light out, port LOW
  TrackSensorLeftValue1 = digitalRead(TrackSensorLeftPin1);
  TrackSensorLeftValue2 = digitalRead(TrackSensorLeftPin2);
  TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
  TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);

  (TrackSensorLeftValue1 == LOW) ? infrared_track_value[0] = '1' : infrared_track_value[0] = '0';
  (TrackSensorLeftValue2 == LOW) ? infrared_track_value[1] = '1' : infrared_track_value[1] = '0';
  (TrackSensorRightValue1 == LOW) ? infrared_track_value[2] = '1' : infrared_track_value[2] = '0';
  (TrackSensorRightValue2 == LOW) ? infrared_track_value[3] = '1' : infrared_track_value[3] = '0';
  //infrared_track_value = "0000";
  return;
}
/**
* Function       track_get_value
* @author        liusen
* @date          2017.07.26
* @brief        Tracking mode pin test
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void track_get_value()
{
  TrackSensorLeftValue1  = digitalRead(TrackSensorLeftPin1);
  TrackSensorLeftValue2  = digitalRead(TrackSensorLeftPin2);
  TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
  TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
}

/**
* Function       infrared_avoid_test
* @author        Danny
* @date          2017.07.26
* @brief         Infrared pin test for obstacle avoidance
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void infrared_avoid_test()
{
   //When the obstacle is encountered, the infrared obstacle avoidance module light up,the port level is LOW
    //When no obstacle, the infrared obstacle avoidance module light out, the port level is HIGH
  LeftSensorValue  = digitalRead(AvoidSensorLeft);
  RightSensorValue = digitalRead(AvoidSensorRight);
  (LeftSensorValue == LOW) ? infrared_avoid_value[0] = '1' : infrared_avoid_value[0] = '0';
  (RightSensorValue == LOW) ? infrared_avoid_value[1] = '1' : infrared_avoid_value[1] = '0';
  return;
}

/**
* Function       follow_light_test
* @author        Danny
* @date          2017.07.26
* @brief         seek light pin test
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void follow_light_test()
{
  //When the light is encountered, the indicator of the optical module is turned off and the port level is HIGH
  //When the light is not encountered, the indicator of the optical module is turned off and the port level is LOW
  LdrSersorRightValue = digitalRead(LdrSensorRight);
  LdrSersorLeftValue  = digitalRead(LdrSensorLeft);

  (LdrSersorLeftValue == LOW) ? LDR_value[0] = '0' : LDR_value[0] = '1';
  (LdrSersorRightValue == LOW) ? LDR_value[1] = '0' : LDR_value[1] = '1';
  return;
}

/**
* Function       run
* @author        Danny
* @date          2017.07.25
* @brief         car run
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void run()
{
   //left motor go
  digitalWrite(Left_motor_go, HIGH);   //enable left motor go
  digitalWrite(Left_motor_back, LOW);  //prohibit left motro back
  analogWrite(Left_motor_pwm, CarSpeedControl);

   //right motor go
  digitalWrite(Right_motor_go, HIGH);  //enable right motor go
  digitalWrite(Right_motor_back, LOW); //prohibit right motor back
  analogWrite(Right_motor_pwm, CarSpeedControl);
}

/**
* Function       brake
* @author        Danny
* @date          2017.07.25
* @brief         car brake
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void brake()
{
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, LOW);
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);
}

/**
* Function       left
* @author        Danny
* @date          2017.07.25
* @brief         Turn left (left wheel stop, right wheel go)
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void left()
{
  //left motor stop
  digitalWrite(Left_motor_go, LOW);    //prohibit left motor go
  digitalWrite(Left_motor_back, LOW);  //prohibit left motor back
  analogWrite(Left_motor_pwm, 0);

  //right motor go
  digitalWrite(Right_motor_go, HIGH);  //enable right motor go
  digitalWrite(Right_motor_back, LOW); //prohibit right motor back
  analogWrite(Right_motor_pwm, CarSpeedControl);
}

/**
* Function       spin_left
* @author        Danny
* @date          2017.07.25
* @brief          Turn left in place(left wheel back,right wheel go)
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void spin_left()
{
  //left motor back
  digitalWrite(Left_motor_go, HIGH);   //enable left motor go
  digitalWrite(Left_motor_back, LOW);  //prohibit left motor back
  analogWrite(Left_motor_pwm, CarSpeedControl);

 //right motor go
  digitalWrite(Right_motor_go, HIGH);  //enable right motor go
  digitalWrite(Right_motor_back, LOW); //prohibit right motor back
  analogWrite(Right_motor_pwm, CarSpeedControl);
}

/**
* Function       right
* @author        Danny
* @date          2017.07.25
* @brief         Turn right (right wheel stop, left wheel go)
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void right()
{
  //left motor go
  digitalWrite(Left_motor_go, HIGH);   //enable left motor go
  digitalWrite(Left_motor_back, LOW);  //prohibit left motor back
  analogWrite(Left_motor_pwm, CarSpeedControl);

  //right motor stop
  digitalWrite(Right_motor_go, LOW);   //prohibit right motor go
  digitalWrite(Right_motor_back, LOW); //prohibit right motor back
  analogWrite(Right_motor_pwm, 0);
}

/**
* Function       spin_right
* @author        Danny
* @date          2017.07.25
* @brief         Turn right in place(right wheel back,left wheel go)
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void spin_right()
{
  //left motor go
  digitalWrite(Left_motor_go, HIGH);    //enable left motor go
  digitalWrite(Left_motor_back, LOW);   //prohibit left motor back
  analogWrite(Left_motor_pwm, CarSpeedControl);

  //right motor back
  digitalWrite(Right_motor_go, LOW);    //prohibit right motor go
  digitalWrite(Right_motor_back, HIGH); //enable right motor back
  analogWrite(Right_motor_pwm, CarSpeedControl);
}

/**
* Function       back
* @author        Danny
* @date          2017.07.25
* @brief        car back
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void back()
{
  //left motor back
  digitalWrite(Left_motor_go, LOW);     //prohibit left motor go
  digitalWrite(Left_motor_back, HIGH);  //enable lef tmotor back
  analogWrite(Left_motor_pwm, CarSpeedControl);

  //right motor back
  digitalWrite(Right_motor_go, LOW);     //prohibit right motor go
  digitalWrite(Right_motor_back, HIGH);  //enable right motor back
  analogWrite(Right_motor_pwm, CarSpeedControl);
}

/**
* Function       whistle
* @author        Danny
* @date          2017.07.25
* @brief         whistle
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void whistle()
{
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);   //sound
  delay(100);                  
  digitalWrite(buzzer, HIGH);  //no sound
  delay(1);                    

  digitalWrite(buzzer, LOW);   //sound
  delay(200);                  
  digitalWrite(buzzer, HIGH);  //no sound
  delay(2);                    
  return;
}

/**
* Function       servo_appointed_detection
* @author        Danny
* @date          2017.07.25
* @brief         The steering engine rotates to a specified angle
* @param[in]     pos
* @param[out]    void
* @retval        void
* @par History   no
*/
void servo_appointed_detection(int pos)
{
  int i = 0;
  for (i = 0; i <= 15; i++)    //The number of PWM is generated, 
                               //and the equivalent delay is guaranteed to go to the response angle
  {
    servo_pulse(ServoPin, pos); //Analog generates PWM
  }
}

/**
* Function       color_led_pwm
* @author        Danny
* @date          2017.07.25
* @brief         The color of the colorful light is specified
* @param[in1]    v_iRed:（0-255）
* @param[in2]    v_iGreen:（0-255）
* @param[in3]    v_iBlue:（0-255）
* @param[out]    void
* @retval        void
* @par History   no
*/
void color_led_pwm(int v_iRed, int v_iGreen, int v_iBlue)
{
  analogWrite(LED_R, v_iRed);
  analogWrite(LED_G, v_iGreen);
  analogWrite(LED_B, v_iBlue);
  delay(100);
  return;
}
/**
* Function       color_led
* @author        Danny
* @date          2017.07.25
* @brief         The different combinations of R, G, B tricolor form 7 different colors
* @param[in1]    Red ON/OFF
* @param[in2]    Green ON/OFF
* @param[in3]    Blue ON/OFF
* @retval        void
* @par History   no
*/

void corlor_led(int v_iRed, int v_iGreen, int v_iBlue)
{
  //红色LED
  if (v_iRed == ON)
  {
    digitalWrite(LED_R, HIGH);
  }
  else
  {
    digitalWrite(LED_R, LOW);
  }
  //绿色LED
  if (v_iGreen == ON)
  {
    digitalWrite(LED_G, HIGH);
  }
  else
  {
    digitalWrite(LED_G, LOW);
  }
  //蓝色LED
  if (v_iBlue == ON)
  {
    digitalWrite(LED_B, HIGH);
  }
  else
  {
    digitalWrite(LED_B, LOW);
  }
}
/********************************************************************************************************/
/*模式2 巡线*/
/**
* Function       Tracking_Mode
* @author        Danny
* @date          2017.07.25
* @brief         tracking
* @param[in1]    void
* @param[out]    void
* @retval        void
* @par History   no
*/
void Tracking_Mode()
{
  //Check the black line tracking module light up, port LOW
  //Not check the black line tracking module light out, port HIGH
  TrackSensorLeftValue1  = digitalRead(TrackSensorLeftPin1);
  TrackSensorLeftValue2  = digitalRead(TrackSensorLeftPin2);
  TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
  TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
  
  //Send the line sensor effect during the inspection process
  time--;
  if (time == 0)
  {
    count--;
    time = 2000;
    if (count == 0)
    {
      printf("$4WD,CSB0,PV8,GS0,LF%d%d%d%d,HW00,GM00#", !TrackSensorLeftValue1, !TrackSensorLeftValue2, !TrackSensorRightValue1, !TrackSensorRightValue2);
      time = 2000;
      count = 1;
    }
  }


  //four road tracking pin level state
  // 0 0 X 0
  // 1 0 X 0
  // 0 1 X 0
  //When the above 6 level states, the car turn right in place, the speed is 250, delay 80ms
  //Handling the rotation of the right acute angles and right angles
  if ( (TrackSensorLeftValue1 == LOW || TrackSensorLeftValue2 == LOW) &&  TrackSensorRightValue2 == LOW)
  {
    CarSpeedControl = 250;
    spin_right();
    delay(80);
  }
   //four road tracking pin level state
  // 0 X 0 0       
  // 0 X 0 1 
  // 0 X 1 0       
  //Handling the rotation of the right acute angles and right angles
  else if ( TrackSensorLeftValue1 == LOW && (TrackSensorRightValue1 == LOW ||  TrackSensorRightValue2 == LOW))
  {
    CarSpeedControl = 250;
    spin_left();
    delay(80);
  }
  // X X X 0
  //rightmost check
  else if ( TrackSensorLeftValue1 == LOW)
  {
    CarSpeedControl = 150;
    spin_left();
    //delay(10);
  }
  // X X X 0
  //Handling left bend
  else if ( TrackSensorRightValue2 == LOW )
  {
    CarSpeedControl = 150;
    spin_right();
    //delay(10);
  }
   //four road tracking pin level state
  // X 0 0 X
  //Handling straight line
  else if ( TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == HIGH)
  {
    CarSpeedControl = 220;
    left();
  }
   //four road tracking pin level state
  // X 1 0 X  
  //Handling right bend
  else if (TrackSensorLeftValue2 == HIGH && TrackSensorRightValue1 == LOW)
  {
    CarSpeedControl = 220;
    right();
  }
  //four road tracking pin level state
  // X 0 0 X
  //Handling straight line
  else if (TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW)
  {
    CarSpeedControl = 250;
    run();
  }
}
/********************************************************************************************************/
/* Mode3:Ultrasonic obstacle avoidance mode*/
/**
* Function       servo_color_carstate
* @author        Danny
* @date          2017.07.26
* @brief         Steering engine steering turn ultrasonic obstacle avoidance, 
*                led according to the status of the car to display the corresponding color
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void servo_color_carstate()
{
  //Define the position variables of the steering gear and the front, left and right distances of the car
  int iServoPos = 0;
  int LeftDistance = 0;    
  int RightDistance = 0;   
  int FrontDistance = 0;   /
  corlor_led(ON, OFF, OFF);
  CarSpeedControl= 80;
  back();                //Avoid a sudden stop, can not brake the car
  delay(80);
  brake();

   //The steering gear rotates to 0 degrees,is right, ranging
  servo_appointed_detection(0);
  delay(500);
  Distance();         
  RightDistance = distance;

 //The steering gear rotates to 180 degrees,is backside, ranging
  servo_appointed_detection(180);
  delay(500);
  Distance();        
  LeftDistance = distance;

  //The steering gear rotates to 90 degrees,is left, ranging
  servo_appointed_detection(90);
  delay(500);
  Distance();
  FrontDistance = distance;

  if (LeftDistance < 10 && RightDistance < 10 && FrontDistance < 10  )
  {
    //light_R,turn around
    corlor_led(ON, OFF, ON);
    CarSpeedControl= 200;
    spin_right();
    delay(560);
    brake();
  }
  else if ( LeftDistance >= RightDistance) //When the left distance is greater than the right, turn left in place
{
  {
    //light_B
    corlor_led(OFF, OFF, ON);
    CarSpeedControl= 200;
    spin_left();
    delay(280);
    brake();
  }
  else if (LeftDistance < RightDistance ) //When the right distance is greater than the left, the turn right is in place
  {
    //light_R,turn right
    corlor_led(ON, OFF, ON);
    CarSpeedControl= 200;
    spin_right();
    delay(280);
    brake();
  }
}
/**
* Function       bubble
* @author        Danny
* @date          2017.07.26
* @brief         Five times of ultrasonic data for bubble sorting
* @param[in1]    a:The first address of ultrasonic array
* @param[in2]    n:Size of ultrasonic array 
* @param[out]    void
* @retval        void
* @par History   no
*/
void bubble(unsigned long *a, int n)

{
  int i, j, temp;
  for (i = 0; i < n - 1; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if (a[i] > a[j])
      {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
    }
  }
}
/**
* Function       Distance
* @author        Danny
* @date          2017.07.26
* @brief         Ultrasonic measurement five times, remove the maximum value, the minimum value,
*                Taking average value to improve test accuracy
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void Distance()
{
  unsigned long ultrasonic[5] = {0};
  int num = 0;
  while (num < 5)
  {
    Distance_test();
     //Filter out the error data in the test distance is greater than 500
    while (distance >= 500 || distance == 0)
    {
      brake();
      Distance_test();
    }
    ultrasonic[num] = distance;
    //printf("L%d:%d\r\n", num, (int)distance);
    num++;
    delay(10);
  }
  num = 0;
  bubble(ultrasonic, 5);
  distance = (ultrasonic[1] + ultrasonic[2] + ultrasonic[3]) / 3;
  return;
}
/**
* Function       Ultrasonic_avoidMode
* @author        Danny
* @date          2017.07.26
* @brief         Ultrasonic obstacle avoidance mode
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void Ultrasonic_avoidMode()
{
  Distance();        
   //printf("D:%d\r\n", (int)distance);
 if (distance > 30  )    //When the obstacle distance is greater than 30,
                          // the left and right infrared rays are used to assist the obstacle avoidance
  {
    //When the obstacle is encountered, the infrared obstacle avoidance module light up,the port level is LOW
    //When no obstacle, the infrared obstacle avoidance module light out, the port level is HIGH
    LeftSensorValue = digitalRead(AvoidSensorLeft);
    RightSensorValue = digitalRead(AvoidSensorRight);

    if (LeftSensorValue == HIGH && RightSensorValue == LOW)
    {
      CarSpeedControl= 200;
      spin_left(); //There's an obstacle on the right.There's a signal to go back and turn left
    }
      delay(200);
    }
    else if (RightSensorValue == HIGH && LeftSensorValue == LOW)
    {
       CarSpeedControl= 200;
       spin_right();//There's an obstacle on the left.There's a signal to go back and turn right
       delay(200);
    }
    else if (RightSensorValue == LOW && LeftSensorValue == LOW)
    {
       CarSpeedControl= 200;
      spin_right();//When the obstacle is detected on both sides, 
                  //the obstacle avoidance in the fixed direction is called(turn right in place)
      delay(200);
    }
    //When the distance is greater than 50, go ahead and turn on the green light
    CarSpeedControl= 200;
    run();
    corlor_led(OFF, ON, OFF);
  }
  else if ((distance >= 20 && distance <= 30))
  {
    //When the obstacle is encountered, the infrared obstacle avoidance module light up,the port level is LOW
    //When no obstacle, the infrared obstacle avoidance module light out, the port level is HIGH
    LeftSensorValue = digitalRead(AvoidSensorLeft);
    RightSensorValue = digitalRead(AvoidSensorRight);

    if (LeftSensorValue == HIGH && RightSensorValue == LOW)
    {
       CarSpeedControl= 200;
      spin_left();  //There's an obstacle on the right.There's a signal to go back and turn left
    }
      delay(200);
    }
    else if (RightSensorValue == HIGH && LeftSensorValue == LOW)
    {
       CarSpeedControl= 200;
      spin_right();//There's an obstacle on the left.There's a signal to go back and turn right
    }
      delay(200);
    }
    else if (RightSensorValue == LOW && LeftSensorValue == LOW)
    {
       CarSpeedControl= 200;
      spin_right();////When the obstacle is detected on both sides, 
                    //the obstacle avoidance in the fixed direction is called(turn right in place)
      delay(200);
    }
     //When distance is between 30-50,run slowly
     CarSpeedControl= 100;
     run();
    
  }
  else if (  distance < 20  )//When the distance is less than 30, call the servo color control program
  {
    servo_color_carstate();
  }
}
/********************************************************************************************************/
/*模式:4  七彩颜色*/

void FindColor_Mode()
{

     servo_appointed_detection(position);
     color_led_pwm( random(0,255), random(0,255), random(0,255));
     position += 10;
     if(position > 180)
     {
       position = 0;
     }
}



/********************************************************************************************************/
/*Mode5:seek light mode*/
void LightSeeking_Mode()
{
  //When the light is encountered, the indicator of the optical module is turned off and the port level is HIGH
  //When the light is not encountered, the indicator of the optical module is turned off and the port level is LOW
  LdrSersorRightValue = digitalRead(LdrSensorRight);
  LdrSersorLeftValue  = digitalRead(LdrSensorLeft);
  CarSpeedControl = 200;
  time--;
  if (time == 0)
  {
    count--;
    time = 2000;
    if (count == 0)
    {
      printf("$4WD,CSB120,PV8.3,GS000,LF0000,HW00,GM%d%d#", LdrSersorLeftValue, LdrSersorRightValue);
      time = 2000;
      count = 1;
    }
  }
  
  if (LdrSersorLeftValue == HIGH && LdrSersorRightValue == HIGH)
  {
    run();   //When both sides have light, the signal is HIGH,
             // the photosensitive resistor light out, and the car run
  }
  else if (LdrSersorLeftValue == HIGH && LdrSersorRightValue == LOW)
  {
    left(); //There's light on the left.There's a signal to go back and turn left
  }
  else if (LdrSersorRightValue == HIGH && LdrSersorLeftValue == LOW)
  {
    right();//There's light on the right.There's a signal to go back and turn right
  }
  else
  {
    brake();//There's not light,car brake
  }
}
/********************************************************************************************************/
/*Mode6: Infrared following mode*/

void Ir_flow_Mode()
{
   //Follow the object, the infrared follow module light up, port level is LOW
    //No follow object, the infrared follow module  light out, port level is HIGH
  LeftSensorValue  = digitalRead(FollowSensorLeft);
  RightSensorValue = digitalRead(FollowSensorRight);
  CarSpeedControl = 200;
  time--;
  if (time == 0)
  {
    count--;
    time = 2000;
    if (count == 0)
    {
      printf("$4WD,CSB120,PV8.3,GS000,LF0000,HW%d%d,GM00", LeftSensorValue, RightSensorValue);
      time = 2000;
      count = 1;
    }
  }

  
  if (LeftSensorValue == LOW && RightSensorValue == LOW)
  {
    run();        //When the follower is detected on both sides, the forward function is called
  }
  else if (LeftSensorValue == LOW && RightSensorValue == HIGH)
  {
    spin_left(); //There's an follower on the left.There's a signal to go back and turn left
  }
  else if (RightSensorValue == LOW && LeftSensorValue == HIGH)
  {
    spin_right();//There's an follower on the right.There's a signal to go back and turn right
  }
  else
  {
    brake();      //When the follower is not detected on both sides,car brake
  }
}

/**
* Function       ModeBEEP
* @author        Danny
* @date          2017.08.17
* @brief        Mode display function
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void ModeBEEP(int mode)
{
  pinMode(buzzer, OUTPUT);
  for (int i = 0; i < mode + 1; i++)
  {
    digitalWrite(buzzer, LOW); //Whistle
    delay(100);
    digitalWrite(buzzer, HIGH); //No whistle
    delay(100);
  }
  delay(100);
  digitalWrite(buzzer, HIGH); //No whistle
}
/**
* Function       BeepOnOffMode
* @author        Danny
* @date          2017.08.17
* @brief          Continuous whistle mode change
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void BeepOnOffMode()
{
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);   //sound
  delay(1000);                  
  digitalWrite(buzzer, HIGH);  //no sound
}
/**
* Function       serial_data_parse
* @author        Danny
* @date          2017.07.25
* @brief         Handling infrared receiving processing
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void serial_data_parse()
{

  /*Analytic mode change*/
  //First determine whether the model is chosen
  if (InputString.indexOf("MODE") > 0 && InputString.indexOf("4WD") > 0)
  {
    if (InputString[10] == '0') //stop
    {
      brake();
      g_CarState = enSTOP;
      g_modeSelect = 0;
      //position = 0;
      BeepOnOffMode();
    }
    else
    {
      switch (InputString[9])
      {
        case '0': g_modeSelect = 0; ModeBEEP(0); break;
        case '1': g_modeSelect = 1; ModeBEEP(1); break;
        case '2': g_modeSelect = 2; ModeBEEP(2); break;
        case '3': g_modeSelect = 3; ModeBEEP(3); break;
        case '4': g_modeSelect = 4; ModeBEEP(4); break;
        case '5': g_modeSelect = 5; ModeBEEP(5); break;
        case '6': g_modeSelect = 6; ModeBEEP(6); break;
        default: g_modeSelect = 0; break;
      }
      delay(1000);
      BeepOnOffMode();
    }
    InputString = "";                     //clear
    NewLineReceived = false;
    return;
  }

  //Non APK mode exits
  if (g_modeSelect != 0) //
  {
    InputString = "";                     //clear
    NewLineReceived = false;
    return;
  }

  //The control commands of the servo pan and the rotation of the actuator are analyzed
  //eg:$4WD,PTZ180#  the steering enginem turn to 180 degrees
  if (InputString.indexOf("PTZ") > 0)
  {
    int m_kp;
    int i = InputString.indexOf("PTZ"); //Looking at the beginning of PTZ # middle end character
    int ii = InputString.indexOf("#", i);
    if (ii > i)
    {
      String m_skp = InputString.substring(i + 3, ii);
      int m_kp = m_skp.toInt();        //Turns string into integer
      //      Serial.print("PTZ:");
      //      Serial.println(m_kp);
      servo_appointed_detection(180 - m_kp);//Turn to the specified angle m_kp
      InputString = "";                     //clear
      NewLineReceived = false;
      return;
    }
  }
  //Analysis of the host sent to the colorful searchlight instructions and lighting the corresponding color
  //eg:$4WD,CLR255,CLG0,CLB0# colour light light_R
  else if (InputString.indexOf("CLR") > 0)
  {
    int m_kp;
    int i = InputString.indexOf("CLR");
    int ii = InputString.indexOf(",", i);
    if (ii > i)
    {
      String m_skp = InputString.substring(i + 3, ii);
      int m_kp = m_skp.toInt();
      //      Serial.print("CLR:");
      //      Serial.println(m_kp);
      red =   m_kp;
    }
    i = InputString.indexOf("CLG");
    ii = InputString.indexOf(",", i);
    if (ii > i)
    {
      String m_skp = InputString.substring(i + 3, ii);
      int m_kp = m_skp.toInt();
      //      Serial.print("CLG:");
      //      Serial.println(m_kp);
      green =   m_kp;
    }
    i = InputString.indexOf("CLB");
    ii = InputString.indexOf("#", i);
    if (ii > i)
    {
      String m_skp = InputString.substring(i + 3, ii);
      int m_kp = m_skp.toInt();
      //      Serial.print("CLB:");
      //      Serial.println(m_kp);
      blue =  m_kp;
      color_led_pwm(red, green, blue);//Lights with corresponding colors
      InputString = "";               //clear
      NewLineReceived = false;
      return;
    }
  }
  //Analyze the general protocol instructions sent by the host computer and execute the corresponding actions
  //eg:$1,0,0,0,0,0,0,0,0,0#    car run
  if (InputString.indexOf("4WD") == -1)
  {
    //小车原地左旋右旋判断
    if (InputString[3] == '1')      //car turn left in place
    {
      g_CarState = enTLEFT;
    }
    else if (InputString[3] == '2') //car turn right in place
    {
      g_CarState = enTRIGHT;
    }
    else
    {
      g_CarState = enSTOP;
    }

   // whistle
    if (InputString[5] == '1')     //Whistle
    {
      whistle();
    }

    //speed
    if (InputString[7] == '1')     //Speed up,  50 each time
    {
      CarSpeedControl += 50;
      if (CarSpeedControl > 255)
      {
        CarSpeedControl = 255;
      }
    }
    if (InputString[7] == '2')//Slow down, 50 each time
    {
      CarSpeedControl -= 50;
      if (CarSpeedControl < 50)
      {
        CarSpeedControl = 100;
      }
    }

    //Steering engine rotation
    if (InputString[9] == '1') //steering engine rotate 180 degree
    {
      servo_appointed_detection(180);
    }
    if (InputString[9] == '2') //steering engine rotate 180 degree
    {
      servo_appointed_detection(0);
    }

    //lihgting
    switch (InputString[13])
    {
      case '1': corlor_led(ON, ON, ON); break;
      case '2': corlor_led(ON, OFF, OFF); break;
      case '3': corlor_led(OFF, ON, OFF); break;
      case '4': corlor_led(OFF, OFF, ON); break;
      case '5': corlor_led(OFF, ON, ON); break;
      case '6': corlor_led(ON, OFF, ON); break;
      case '7': corlor_led(ON, ON, OFF); break;
      case '8': corlor_led(OFF, OFF, OFF); break;
    }

    //outfire
    if (InputString[15] == '1')  //outfire
    {
      pinMode(OutfirePin, OUTPUT);
      digitalWrite(OutfirePin, LOW );
      g_motor = true;
    }
    else if (InputString[15] == '0')  //outfire
    {
      pinMode(OutfirePin, OUTPUT);
      digitalWrite(OutfirePin, HIGH );
      g_motor = false;
    }

    if (InputString[17] == '1') //steering engine rotate 90 degree
    {
      servo_appointed_detection(90);
    }

    //car run,back,turn left,turn right,stop 
    if (g_CarState != enTLEFT && g_CarState != enTRIGHT)
    {
      switch (InputString[1])
      {
        case run_car:   g_CarState = enRUN;  break;
        case back_car:  g_CarState = enBACK;  break;
        case left_car:  g_CarState = enLEFT;  break;
        case right_car: g_CarState = enRIGHT;  break;
        case stop_car:  g_CarState = enSTOP;  break;
        default: g_CarState = enSTOP; break;
      }
    }

    InputString = "";         //clear
    NewLineReceived = false;

    //According to the car state to do the corresponding action
    switch (g_CarState)
    {
      case enSTOP: brake(); break;
      case enRUN: run(); break;
      case enLEFT: left(); break;
      case enRIGHT: right(); break;
      case enBACK: back(); break;
      case enTLEFT: spin_left(); break;
      case enTRIGHT: spin_right(); break;
      default: brake(); break;
    }
  }
}

/**
* Function       serial_data_postback
* @author        Danny
* @date          2017.07.25
* @brief         The collected sensor data is transmitted through the serial port to the host computer
* @param[in]     void
* @retval        void
* @par History   no
*/
void serial_data_postback()
{
  //The information collected by the car ultrasonic sensor is displayed on the upper computer
  //Packing format:
  //    Ultrasonic, voltage, gray, Line patrol, infrared obstacle avoidance and seek light
  //$4WD,CSB120,PV8.3,GS214,LF1011,HW11,GM11#
  //Ultrasonic
  Distance_test();
  ReturnTemp = "$4WD,CSB" ;
  ReturnTemp.concat(distance);
  //voltage
  ReturnTemp += ",PV";
  //voltage_test();
  ReturnTemp.concat( voltage_test());
  //gray
  ReturnTemp += ",GS";
  ReturnTemp.concat(color_test());
  // Line patrol
  ReturnTemp += ",LF";
  track_test();
  ReturnTemp.concat(infrared_track_value);
  // infrared obstacle avoidance
  ReturnTemp += ",HW";
  infrared_avoid_test();
  ReturnTemp.concat(infrared_avoid_value);
  //seek light
  ReturnTemp += ",GM";
  follow_light_test();
  ReturnTemp.concat(LDR_value);
  ReturnTemp += "#";
  Serial.print(ReturnTemp);
  return;
}

/**
* Function       serialEvent
* @author        Danny
* @date          2017.07.25
* @brief         Serial unpack
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/

void serialEvent()
{
  while (Serial.available())
  {
    //One byte reads one byte, the next is read, and the string is placed into an array of data to form a completed packet
    IncomingByte = Serial.read();
    if (IncomingByte == '$')
    {
      StartBit = true;
    }
    if (StartBit == true)
    {
      InputString += (char) IncomingByte;
    }
    if (IncomingByte == '#')
    {
      NewLineReceived = true;
      StartBit = false;
    }
  }
}

/**
* Function       loop
* @author        Danny
* @date          2017.07.25
* @brief         The data sent by the serial port is parsed, and the corresponding instructions are executed
* @param[in]     void
* @retval        void
* @par History   no
*/
void loop()
{
  if (NewLineReceived)
  {
    serial_data_parse(); 
  }

  // Switch different function mode, function mode display
  switch (g_modeSelect)
  {
    case 1: break; 
    case 2: Tracking_Mode(); break; 
    case 3: Ultrasonic_avoidMode();  break; 
    case 4: FindColor_Mode(); break;  
    case 5: LightSeeking_Mode(); break; 
    case 6: Ir_flow_Mode(); break; 
  }

  //Let the car serial port send data to the mobile phone Bluetooth APK per second on average
  //Avoid serial data printing speed is too fast, resulting in APK can not run properly
  if (g_modeSelect == 0 && g_motor == false)
  {
    time--;
    if (time == 0)
    {
      count--;
      time = 20000;
      if (count == 0)
      {
        
        serial_data_postback();
        time = 20000;
        count = 10;
      }
    }
  }

}





