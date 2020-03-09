/* -----------------------------------------------------------------------------
  - Project: Remote control Crawling robot
  - Author:  panerqiang@sunfounder.com
  - Date:  2015/1/27
   -----------------------------------------------------------------------------
  - Overview
  - This project was written for the Crawling robot desigened by Sunfounder.
    This version of the robot has 4 legs, and each leg is driven by 3 servos.
  This robot is driven by a Ardunio Nano Board with an expansion Board.
  We recommend that you view the product documentation before using.
  - Request
  - This project requires some library files, which you can find in the head of
    this file. Make sure you have installed these files.
  - How to
  - Before use,you must to adjust the robot,in order to make it more accurate.
    - Adjustment operation
    1.uncomment ADJUST, make and run
    2.comment ADJUST, uncomment VERIFY
    3.measure real sites and set to real_site[4][3], make and run
    4.comment VERIFY, make and run
  The document describes in detail how to operate.

   ---------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include <Servo.h>							//control servos
#include <FlexiTimer2.h>			  //set a timer to manage all servos

#include "Config.h"             //Robot settings
#include "Servo_Generic.h"      //Servo 
#include "Kinematics.h"         //Kinematics algoritm
#include "Gait.h"               //Gait 
#include "Ultrasonic.h"         //Ultrasonic sensor
#include "MazeSolving.h"        //Maze solving algoritm
#include "Command.h"            //Command DEBUG


/*
- setup function
  ---------------------------------------------------------------------------*/
void setup()
{
    //start serial for debug
    Serial.begin(115200);
    Serial.println(F("Robot starts initialization"));

    command_init();

    site_init();           //init default site
    servo_init();        //initialize servos
    start_servo_service(); //start servo service

    Serial.println(F("Robot initialization Complete"));

    Serial.println(F("Stand"));
    stand();
    delay(5000);
}

/*
  - loop function
   ---------------------------------------------------------------------------*/
void loop()
{

    Serial.println(F("Turn left"));
    turn_left(5);
    delay(2000);

    Serial.println(F("Turn right"));
    turn_right(5);
    delay(2000);

    Serial.println(F("Step forward"));
    step_forward(10);
    delay(2000);

    Serial.println(F("Sit"));
    sit();
    delay(5000);
}
