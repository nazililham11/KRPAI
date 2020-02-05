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
#include <Servo.h>							  //to define and control servos
#include <FlexiTimer2.h>					  //to set a timer to manage all servos
#include "Test_Servo/ATMega128_Arduino_Pin.h" //Convert Arduino to ATmega PORT
#include "Test_Servo/Values.h"
#include "Ultrasonic_lib.h"
/* DEBUG ---------------------------------------------------------------------*/
#define DEBUG true
#define SERVO_DEBUG false
#define GRAIT_DEBUG false
#define GRAIT_DELAYS 2000
#define DEBUG_COMMAND false
/* Commands --------------------------------------------------------------------*/
#if DEBUG_COMMAND && DEBUG
#include <CommandHandler.h>
CommandHandler<> SerialCommandHandler(Serial, '[', ']');
#endif
/* Ultrasonic --------------------------------------------------------------------*/
Ultrasonic ultrasonic[] = {
	Ultrasonic(PORT_E_0),		//Front
	Ultrasonic(PORT_C_6),		//Left
	Ultrasonic(PORT_E_2),		//Right
	Ultrasonic(PORT_C_7),		//Front Left
	Ultrasonic(PORT_E_1)		//Front Right
};
/* Servos --------------------------------------------------------------------*/
//define 12 servos for 4 legs and 3 dof
Servo servo[4][3];
//define servo's ports
const uint8_t servo_pin[4][3] = {
	{PORT_A_0, PORT_A_1, PORT_A_2}, //Front Left
	{PORT_D_7, PORT_D_6, PORT_D_5}, //Rear Left
	{PORT_F_7, PORT_F_6, PORT_F_5}, //Front Right
	{PORT_B_7, PORT_B_6, PORT_B_5}  //Rear Right
};
/* Size of the robot ---------------------------------------------------------*/
const float length_a = L_FEMUR; //Femur
const float length_b = L_TIBIA; //Tibia
const float length_c = L_COXA;  //Coxa
const float length_side = 71;   //Length between leg
const float z_absolute = -50;   //max z coordinates
/* Constants for movement ----------------------------------------------------*/
const float z_default = -85;	 //z default coordinates
const float z_up = -65;			 //z up coordinates
const float z_boot = z_absolute; //z sit coordinates
const float x_default = 62;
const float x_offset = 0;
const float y_start = 0;
const float y_step = 40;
/* variables for movement ----------------------------------------------------*/
volatile float site_now[4][3];	//real-time coordinates of the end of each leg
volatile float site_expect[4][3]; //expected coordinates of the end of each leg
float temp_speed[4][3];			  //each axis' speed, needs to be recalculated before each movement
float move_speed;				  //movement speed
float speed_multiple = 1;		  //movement speed multiple
float spot_turn_speed = 3;
float leg_move_speed = 10;
float body_move_speed = 1.5;
float stand_seat_speed = 1;
volatile int rest_counter; //+1/0.02s, for automatic rest
//function's parameter
const float KEEP = 255;
//define PI for calculation
const float pi = 3.1415926;
/* Constants for turn --------------------------------------------------------*/
//temp length
const float temp_a = sqrt(pow(2 * x_default + length_side, 2) + pow(y_step, 2));
const float temp_b = 2 * (y_start + y_step) + length_side;
const float temp_c = sqrt(pow(2 * x_default + length_side, 2) + pow(2 * y_start + y_step + length_side, 2));
const float temp_alpha = acos((pow(temp_a, 2) + pow(temp_b, 2) - pow(temp_c, 2)) / 2 / temp_a / temp_b);
//site for turn
const float turn_x1 = (temp_a - length_side) / 2;
const float turn_y1 = y_start + y_step / 2;
const float turn_x0 = turn_x1 - temp_b * cos(temp_alpha);
const float turn_y0 = temp_b * sin(temp_alpha) - turn_y1 - length_side;
/* ---------------------------------------------------------------------------*/
