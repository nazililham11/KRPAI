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
    
    Coxa  : Min 40, Max 180
    Femur : Min 0, Max 135
    Tibia : Min 0, Max 110

   ---------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include <Servo.h>                            //to define and control servos
#include <FlexiTimer2.h>                      //to set a timer to manage all servos
#include "Test_Servo/ATMega128_Arduino_Pin.h" //Convert Arduino to ATmega PORT
#define DEBUG true
/* Servos --------------------------------------------------------------------*/
//define 12 servos for 4 legs and 3 dof
Servo servo[4][3];
//define servo's ports
const uint8_t servo_pin[4][3] = {
    {PORT_A_0, PORT_A_1, PORT_A_2}, //Front Left
    {PORT_D_0, PORT_D_1, PORT_D_2}, //Rear Left
    {PORT_F_7, PORT_F_6, PORT_F_5}, //Front Right
    {PORT_B_7, PORT_B_6, PORT_B_5}  //Rear Right
};
/* Size of the robot ---------------------------------------------------------*/
const float length_a = 43;    //Femur
const float length_b = 71;    //Tibia
const float length_c = 25;    //Coxa
const float length_side = 71; //Length between leg
const float z_absolute = -28; //max z coordinates
/* Constants for movement ----------------------------------------------------*/
const float z_default = -50;     //z default coordinates
const float z_up = -30;          //z up coordinates
const float z_boot = z_absolute; //z sit coordinates
const float x_default = 62;
const float x_offset = 0;
const float y_start = 0;
const float y_step = 40;
/* variables for movement ----------------------------------------------------*/
volatile float site_now[4][3];    //real-time coordinates of the end of each leg
volatile float site_expect[4][3]; //expected coordinates of the end of each leg
float temp_speed[4][3];           //each axis' speed, needs to be recalculated before each movement
float move_speed;                 //movement speed
float speed_multiple = 1;         //movement speed multiple
const float spot_turn_speed = 4;
const float leg_move_speed = 8;
const float body_move_speed = 3;
const float stand_seat_speed = 1;
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

/*
  - setup function
   ---------------------------------------------------------------------------*/
void setup()
{
    //start serial for debug
    Serial.begin(115200);
    Serial.println("Robot starts initialization");

    //initialize default parameter
    set_site(0, x_default - x_offset, y_start + y_step, z_boot);
    // set_site(1, x_default - x_offset, y_start + y_step, z_boot);
    // set_site(2, x_default + x_offset, y_start - y_step, z_boot);
    // set_site(3, x_default + x_offset, y_start - y_step, z_boot);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            site_now[i][j] = site_expect[i][j];
        }
    }

    //initialize servos
    servo_attach();

    //start servo service
    FlexiTimer2::set(5000, servo_service);
    FlexiTimer2::start();
    Serial.println("Servo service started");
    Serial.println("Servos initialized");
    Serial.println("Robot initialization Complete");
}

/*
  - loop function
   ---------------------------------------------------------------------------*/
void loop()
{
    Serial.println("Stand");
    stand();
    delay(10000);
    // Serial.println("Sit");
    // sit();
    // delay(2000);
}

/*
  - sit
  - blocking function
   ---------------------------------------------------------------------------*/
void sit(void)
{
    move_speed = stand_seat_speed;
    // for (int leg = 0; leg < 4; leg++)
    // {
    //     set_site(leg, KEEP, KEEP, z_boot);
    // }
    set_site(0, KEEP, KEEP, z_boot);
    wait_all_reach();
}

/*
  - stand
  - blocking function
   ---------------------------------------------------------------------------*/
void stand(void)
{
    move_speed = stand_seat_speed;
    // for (int leg = 0; leg < 4; leg++)
    // {
    //     set_site(leg, KEEP, KEEP, z_default);
    // }
    set_site(0, KEEP, KEEP, z_default);
    wait_all_reach();
}

void servo_attach(void)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            servo[i][j].attach(servo_pin[i][j]);
            delay(100);
        }
    }
}

void servo_detach(void)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            servo[i][j].detach();
            delay(100);
        }
    }
}
/*
  - microservos service /timer interrupt function/50Hz
  - when set site expected,this function move the end point to it in a straight line
  - temp_speed[4][3] should be set before set expect site,it make sure the end point
   move in a straight line,and decide move speed.
   ---------------------------------------------------------------------------*/
void servo_service(void)
{

#if DEBUG
    Serial.println("Start Servo Sevice");
#endif
    sei();
    static float alpha, beta, gamma;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (abs(site_now[i][j] - site_expect[i][j]) >= abs(temp_speed[i][j]))
                site_now[i][j] += temp_speed[i][j];
            else
                site_now[i][j] = site_expect[i][j];
        }

        cartesian_to_polar(alpha, beta, gamma, site_now[i][0], site_now[i][1], site_now[i][2]);
        polar_to_servo(i, alpha, beta, gamma);
    }

    rest_counter++;
}

/*
  - set one of end points' expect site
  - this founction will set temp_speed[4][3] at same time
  - non - blocking function
   ---------------------------------------------------------------------------*/
void set_site(int leg, float x, float y, float z)
{
    float length_x = 0, length_y = 0, length_z = 0;

    if (x != KEEP)
        length_x = x - site_now[leg][0];
    if (y != KEEP)
        length_y = y - site_now[leg][1];
    if (z != KEEP)
        length_z = z - site_now[leg][2];

    float length = sqrt(pow(length_x, 2) + pow(length_y, 2) + pow(length_z, 2));

    temp_speed[leg][0] = length_x / length * move_speed * speed_multiple;
    temp_speed[leg][1] = length_y / length * move_speed * speed_multiple;
    temp_speed[leg][2] = length_z / length * move_speed * speed_multiple;

    if (x != KEEP)
        site_expect[leg][0] = x;
    if (y != KEEP)
        site_expect[leg][1] = y;
    if (z != KEEP)
        site_expect[leg][2] = z;
}

/*
  - wait one of end points move to expect site
  - blocking function
   ---------------------------------------------------------------------------*/
void wait_reach(int leg)
{
    while (1)
    {
        if (site_now[leg][0] == site_expect[leg][0])
        {
            if (site_now[leg][1] == site_expect[leg][1])
            {
                if (site_now[leg][2] == site_expect[leg][2])
                {
                    break;
                }
            }
        }
    }
}

/*
  - wait all of end points move to expect site
  - blocking function
   ---------------------------------------------------------------------------*/
void wait_all_reach(void)
{
    for (int i = 0; i < 4; i++)
        wait_reach(i);
}

/*
  - trans site from cartesian to polar
  - mathematical model 2/2
   ---------------------------------------------------------------------------*/
void cartesian_to_polar(volatile float &alpha, volatile float &beta, volatile float &gamma,
                        volatile float x, volatile float y, volatile float z)
{
    //calculate w-z degree
    float v, w;
    w = (x >= 0 ? 1 : -1) * (sqrt(pow(x, 2) + pow(y, 2)));
    v = w - length_c;
    alpha = atan2(z, v) + acos((pow(length_a, 2) - pow(length_b, 2) + pow(v, 2) + pow(z, 2)) / 2 / length_a / sqrt(pow(v, 2) + pow(z, 2)));
    beta = acos((pow(length_a, 2) + pow(length_b, 2) - pow(v, 2) - pow(z, 2)) / 2 / length_a / length_b);
    //calculate x-y-z degree
    gamma = (w >= 0) ? atan2(y, x) : atan2(-y, -x);

#if !DEBUG
    Serial.println("Calculate Cartesian to Polar");
    Serial.println("-X  : " + String(x));
    Serial.println("-Y : " + String(y));
    Serial.println("-Z  : " + String(z));
    Serial.println("-gamma  : " + String(gamma));
    Serial.println("-alpha : " + String(alpha));
    Serial.println("-beta  : " + String(beta));
    Serial.println();
#endif

    //trans degree pi->180
    alpha = alpha / pi * 180;
    beta = beta / pi * 180;
    gamma = gamma / pi * 180;
}

void polar_to_servo(int leg, float alpha, float beta, float gamma)
{
#if DEBUG
    if (leg == 0)
    {
        Serial.println("Set Leg " + String(leg));
        Serial.println("-Coxa  : " + String(gamma));
        Serial.println("-Femur : " + String(alpha));
        Serial.println("-Tibia  : " + String(beta));
        Serial.println();
    }
#endif
    if (leg == 0 || leg == 3)
    {
        // alpha += 90;
        // beta = 180 - beta - 30;

        alpha = 180 - (90 - alpha);
        beta = beta - 30;

        // alpha = 180 - alpha;
        // beta = 180 - beta - 30;

        // alpha = alpha;
        // beta = beta - 30;
        gamma += 90;
    }
    else if (leg == 1 || leg == 2)
    {
        alpha = 180 - alpha;
        beta = 180 - beta - 30;
        gamma = 90 - gamma;
    }

    servo[leg][0].write(gamma); //Coxa
    servo[leg][1].write(alpha); //Femur
    servo[leg][2].write(beta);  //Tibia

#if DEBUG
    if (leg == 0){
        Serial.println("Set Leg " + String(leg));
        Serial.println("-Coxa  : " + String(gamma));
        Serial.println("-Femur : " + String(alpha));
        Serial.println("-Tibia  : " + String(beta));
        Serial.println();
    }
#endif
}
