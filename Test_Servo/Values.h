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
#define L_FEMUR   43  //mm distance from femur servo to tibia servo
#define L_TIBIA   71  //mm distance from tibia servo to foot

#define SQ_L_FEMUR   1849
#define SQ_L_TIBIA   541
                //139
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

/* A leg position request (output of body calcs, input to simple 3dof solver). */
typedef struct{
    int x;
    int y;
    int z;
    float r;
} ik_req_t;

/* Servo ouptut values (output of 3dof leg solver). */
typedef struct{
    int coxa;
    int femur;
    int tibia;
} ik_sol_t;

/* Actual positions, and indices of array. */
extern ik_req_t endpoints[LEG_COUNT];
#define RIGHT_FRONT    0
#define RIGHT_REAR     1
#define LEFT_FRONT     2
#define LEFT_REAR      3

/* Parameters for manipulating body position */
extern float bodyRotX;    // body roll
extern float bodyRotY;    // body pitch
extern float bodyRotZ;    // body rotation
extern int   bodyPosX;
extern int   bodyPosY;

/* Parameters for gait manipulation */
extern int    Xspeed;
extern int    Yspeed;
extern float  Rspeed;
extern int    tranTime;
extern float  cycleTime;
extern int    stepsInCycle;
extern int    liftHeight;
extern int    step;
extern int    currentGait;

/* Gait Engine */
extern int        gaitLegNo[];   // order to move legs in
extern ik_req_t   gaits[];       // gait position

/* convert radians to a dynamixel servo offset */
int radToServo(float rads);

/* select a gait pattern to use */
void gaitSelect(int GaitType);

/* find the translation of the endpoint (x,y,z) given our gait parameters */
extern ik_req_t (*gaitGen)(int leg);
extern void (*gaitSetup)();

/* 
 *  ripple gaits move one leg at a time 
 *  for going forward, or turning left/right
 */
#define RIPPLE                  0
#define RIPPLE_LEFT             1
#define RIPPLE_RIGHT            2

/* amble gaits move two alternate legs at a time */
#define AMBLE                   5

/* find the translation of the coxa point (x,y) in 3-space, given our rotations */
ik_req_t bodyIK(int X, int Y, int Z, int Xdisp, int Ydisp, float Zrot);

/* given our leg offset (x,y,z) from the coxa point, calculate servo values */
ik_sol_t legIK(int X, int Y, int Z);

/* ties all of the above together */
void doIK();

/* setup the starting positions of the legs. */
void setupIK();

#endif
