#include "ATMega128_Arduino_Pin.h"      //Convert Arduino to ATmega PORT

//--------------------------------------------------------------------
//[ULTRASONIC PIN CONFIGURATION]
#define ULTRASONIC_FRONT        PORT_E_0
#define ULTRASONIC_LEFT         PORT_C_6
#define ULTRASONIC_RIGHT        PORT_E_2
#define ULTRASONIC_FRONT_LEFT   PORT_C_7
#define ULTRASONIC_FRONT_RIGHT  PORT_E_1


//--------------------------------------------------------------------
//[INFRARED DISTANCE PIN CONFIGURATION]
#define INF_DISTANCE_FRONT_PIN        PORT_F_0
#define INF_DISTANCE_LEFT_PIN         PORT_F_1
#define INF_DISTANCE_RIGHT_PIN        PORT_F_2


//--------------------------------------------------------------------
//[SERVO PIN CONFIGURATION]
#define FRONT_LEFT_COXA     PORT_A_0 
#define FRONT_LEFT_FEMUR    PORT_A_1 
#define FRONT_LEFT_TIBIA    PORT_A_2

#define REAR_LEFT_COXA      PORT_D_7 
#define REAR_LEFT_FEMUR     PORT_D_6 
#define REAR_LEFT_TIBIA     PORT_D_5

#define FRONT_RIGHT_COXA    PORT_F_7 
#define FRONT_RIGHT_FEMUR   PORT_F_6 
#define FRONT_RIGHT_TIBIA   PORT_F_5

#define REAR_RIGHT_COXA     PORT_B_7 
#define REAR_RIGHT_FEMUR    PORT_B_6 
#define REAR_RIGHT_TIBIA    PORT_B_5


//--------------------------------------------------------------------
//[LEG DIMENSIONS]
#define L_COXA    25        //mm distance from coxa servo to femur servo
#define L_FEMUR   45        //mm distance from femur servo to tibia servo
#define L_TIBIA   72        //mm distance from tibia servo to foot


//--------------------------------------------------------------------
//[DEBUG]
#define DEBUG           false
#define SERVO_DEBUG     false   //Print servo angle
#define GAIT_DEBUG      false   //Gait Debug
#define GAIT_DELAYS     2000    //Delay to move leg        
#define DEBUG_COMMAND   false   //Debug with command


//--------------------------------------------------------------------
//[ULTRASONIC ID]
#define US_FRONT        0
#define US_LEFT         1
#define US_RIGHT        2
#define US_FRONT_LEFT   3
#define US_FRONT_RIGHT  4


//--------------------------------------------------------------------
//[INFRARED DISTANCE ID]
#define INF_DISTANCE_FRONT      0
#define INF_DISTANCE_LEFT       1
#define INF_DISTANCE_RIGHT      2


//--------------------------------------------------------------------
//[TRACK RESULT]
#define STRAIGHT        0
#define DEAD_END        1
#define STRAIGHT_LEFT   2
#define STRAIGHT_RIGHT  3
#define CROSS           4
#define RIGHT           5
#define LEFT            6
#define T               7



//--------------------------------------------------------------------
//[THRESHOLD]
#define FRONT_WALL_THRESHOLD    10       //cm front threshold
#define LEFT_WALL_THRESHOLD     10       //cm left threshold
#define RIGHT_WALL_THRESHOLD    10       //cm right threshold

#define ULTRASONIC_MEAN_COUNT 3         //many of sensor readings to get mean distance
