/* Size of the robot ---------------------------------------------------------*/
float length_a = L_FEMUR;           //Femur
float length_b = L_TIBIA;           //Tibia
float length_c = L_COXA;            //Coxa
float length_side = L_SIDE_LEG;     //Length between leg
float z_absolute = -50;             //max z coordinates
/* Constants for movement ----------------------------------------------------*/
float z_default = -85;              //z default coordinates
float z_up = -65;                   //z up coordinates
float z_boot = z_absolute;          //z sit coordinates
float x_default = 62;
float x_offset = 0;
float y_start = 0;
float y_step = 40;
/* variables for movement ----------------------------------------------------*/
volatile float site_now[4][3];    //real-time coordinates of the end of each leg
volatile float site_expect[4][3]; //expected coordinates of the end of each leg
float temp_speed[4][3];           //each axis' speed, needs to be recalculated before each movement
float move_speed;                 //movement speed
float speed_multiple = 1;         //movement speed multiple
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

void start_servo_service(void);
void site_init(void);
void servo_service(void);
void set_site(uint8_t leg, float x, float y, float z);
void wait_reach(uint8_t leg);
void wait_all_reach(void);
void set_site(void);
void cartesian_to_polar(volatile float &alpha, volatile float &beta, volatile float &gamma,
                        volatile float x, volatile float y, volatile float z);
void polar_to_servo(uint8_t leg, float &alpha, float &beta, float &gamma);
void write_to_servo(uint8_t leg, float alpha, float beta, float gamma);


void start_servo_service(void)
{
    //start servo service
    FlexiTimer2::set(20, servo_service);
    FlexiTimer2::start();

    Serial.println("Servo service started");
}


void site_init(void)
{
    //initialize default parameter
    set_site(0, x_default - x_offset, y_start + y_step, z_boot);
    set_site(1, x_default - x_offset, y_start + y_step, z_boot);
    set_site(2, x_default + x_offset, y_start, z_boot);
    set_site(3, x_default + x_offset, y_start, z_boot);

    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            site_now[i][j] = site_expect[i][j];
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
    sei();
    static float alpha, beta, gamma;

    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            if (abs(site_now[i][j] - site_expect[i][j]) >= abs(temp_speed[i][j]))
                site_now[i][j] += temp_speed[i][j];
            else
                site_now[i][j] = site_expect[i][j];
        }

        cartesian_to_polar(alpha, beta, gamma, site_now[i][0], site_now[i][1], site_now[i][2]);
        polar_to_servo(i, alpha, beta, gamma);
        write_to_servo(i, alpha, beta, gamma);
    }

    rest_counter++;
}


/*
  - set one of end points' expect site
  - this founction will set temp_speed[4][3] at same time
  - non - blocking function
   ---------------------------------------------------------------------------*/
void set_site(uint8_t leg, float x, float y, float z)
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
void wait_reach(uint8_t leg)
{
    while (1)
    {
        if (site_now[leg][0] != site_expect[leg][0])
            continue;
        
        if (site_now[leg][1] != site_expect[leg][1])
            continue;
        
        if (site_now[leg][2] != site_expect[leg][2])
            continue;
        
        break;
        
    }
}


/*
  - wait all of end points move to expect site
  - blocking function
   ---------------------------------------------------------------------------*/
void wait_all_reach(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        wait_reach(i);
    }

    #if GAIT_DEBUG && DEBUG
        delay(GAIT_DELAYS);
    #endif
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

    //trans degree pi->180
    alpha = alpha / pi * 180;
    beta = beta / pi * 180;
    gamma = gamma / pi * 180;
}


void polar_to_servo(uint8_t leg, float &alpha, float &beta, float &gamma)
{
    switch(leg){
        case 1:                         //Rear Right
        case 2:                         //Front Left
            alpha = 90 - alpha;
            beta = beta + 20;
            gamma = 90 - gamma;
            break;
        case 0:                         //Front Right
        case 3:                         //Rear Left
            alpha = 90 + alpha;
            beta = 180 - beta - 20;
            gamma += 90;
            break;
    }
}

void write_to_servo(uint8_t leg, float alpha, float beta, float gamma)
{
    setServo(leg, 0, gamma);    //Coxa
    setServo(leg, 1, alpha);    //Femur
    setServo(leg, 2, beta);     //Tibia

    #if DEBUG && SERVO_DEBUG
        Serial.print(F("Write to Leg "));
        Serial.print(leg);
        Serial.print(F("\tCoxa  : "));
        Serial.print(gamma);
        Serial.print(F("\tFemur : "));
        Serial.print(alpha);
        Serial.print(F("\tTibia  : "));
        Serial.print(beta);
        Serial.println();
    #endif
}