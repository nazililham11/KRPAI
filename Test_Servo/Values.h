/******************************************************************************
 * Inverse Kinematics for 4 legged bots using 3DOF lizard legs
 *
 * FRONT VIEW       ^        ==0         0==
 *     /\___/\      |       |  0==[___]==0  |
 *    /       \     Z       |               |
 *
 * TOP VIEW
 *    \       /     ^
 *     \_____/      |
 *     |     |      X
 *     |_____|
 *     /     \      Y->
 *    /       \
 *****************************************************************************/

#ifndef NUKE
#define NUKE

#define LEG_COUNT 4

#define X_COXA    50  // mm between front and back legs /2
#define Y_COXA    37  // mm between front/back legs /2

#define L_COXA    25  //mm distance from coxa servo to femur servo
#define L_FEMUR   45  //mm distance from femur servo to tibia servo
#define L_TIBIA   72  //mm distance from tibia servo to foot

#define SQ_L_FEMUR   1849
#define SQ_L_TIBIA   541

//Servo ID
#define RF_COXA   2   //Right Front Coxa
#define RF_FEMUR  4    //Right Front Femur 
#define RF_TIBIA  6   //Right Front Tibia

#define LF_COXA   1   //Left Front Coxa
#define LF_FEMUR  3   //Left Front Femur   
#define LF_TIBIA  5   //Left Front Tibia

#define LR_COXA   7   //Left Rear Coxa
#define LR_TIBIA  11  //Left Rear Femur
#define LR_FEMUR  9   //Left Rear Tibia

#define RR_FEMUR  11  //Right Rear Coxa 
#define RR_COXA   8   //Right Rear Femur
#define RR_TIBIA  12  //Right Rear Tibia 

#endif
