#include <Servo.h>              // library servo
#include <Wire.h>               // library I2C
#include <TPA81.h>              // Library sensor api TPA81
#include <SoftwareSerial.h>
#include <FlexiTimer2.h>
#include <MPU6050_tockn.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2);
MPU6050 mpu6050(Wire);
TPA81 tpa;
Servo servo[4][3];

//////// pin sonar ////////
const int echoPin1 = 0;
const int echoPin2 = 0;
const int echoPin3 = 0;
const int echoPin4 = 0;
const int echoPin5 = 0;
const int echoPin6 = 0;
const int echoPin7 = 0;

//////// set jarak maksimal ////////
#define distance 200

//////// pin sensor ////////
int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int sensor4 = 0;
int sensor5 = 0;

//////// pin voice ////////
int voice = 0;
int sound;
int aktif = 0;

//////// pin pompa ////////
#define pump 0

//////// pin led ////////
#define led 0 // aktif
#define led2 0 // ada api

//////// setup sonar ////////
long duration1 = 0;
long duration2 = 0;
long duration3 = 0;
long duration4 = 0;
long duration5 = 0;
long duration6 = 0;
long duration7 = 0;

float distance1 = 0;
float distance2 = 0;
float distance3 = 0;
float distance4 = 0;
float distance5 = 0;
float distance6 = 0;
float distance7 = 0;

//////// setup waktu servo ////////
int timer = 0;
//////////////////////////// {  2 ,1,3  }, { 5,  4, 6},  {8,  7, 9 },  {11, 10, 12}
const int servo_pin[4][3] = {{ 23,24, 22}, {42, 43, 44}, {13, 14, 15}, {51, 50, 52}};

/* variables for movement ----------------------------------------------------*/
volatile float site_now[4][3];    //real-time coordinates of the end of each leg
volatile float site_expect[4][3]; //expected coordinates of the end of each leg
float temp_speed[4][3];   //each axis' speed, needs to be recalculated before each movement
float move_speed;     //movement speed
volatile int rest_counter;      //+1/0.02s, for automatic rest
//functions' parameter
//define pi for calculation
const float pi = 3.1415926;
/* Constants for turn --------------------------------------------------------*/
//temp length
const float temp_a = sqrt(pow(2 * 62 + 71, 2) + pow(40, 2)); // 
const float temp_b = 2 * (0 + 40) + 71;
const float temp_c = sqrt(pow(2 * 62 + 71, 2) + pow(2 * 0 + 40 + 71, 2));
const float temp_alpha = acos((pow(temp_a, 2) + pow(temp_b, 2) - pow(temp_c, 2)) / 2 / temp_a / temp_b);
//site for turn
const float turn_x1 = (temp_a - 71) / 2;
const float turn_y1 = 0 + 40 / 2;
const float turn_x0 = turn_x1 - temp_b * cos(temp_alpha);
const float turn_y0 = temp_b * sin(temp_alpha) - turn_y1 - 71;
/* ---------------------------------------------------------------------------*/


/////////////////////////////////////////////////////////////////////////////////////////////////////SETUP
void setup() {

    Serial.begin(9600);
    Wire.begin();               // prosedur memulai komunikasi data I2C
    lcd.init();
    lcd.backlight();
    mpu6050.begin();

    set_site(0, 62 - 0, 0 + 40, -28);
    set_site(1, 62 - 0, 0 + 40, -28);
    set_site(2, 62 + 0, 0, -28);
    set_site(3, 62 + 0, 0, -28);

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 3; j++){
            site_now[i][j] = site_expect[i][j];
        }
    }

    //////// inisialisasi pin servo ////////
    for (int x = 0; x <= 4; x++) {
        for (int xx = 0; xx <= 3; xx++) {
            servo[x][xx].attach(servo_pin[x][xx]);
            delay(20);
        }
    }

    //start servo service
    FlexiTimer2::set(20, servo_service);
    FlexiTimer2::start();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////  LOOP
void loop() {  
    Serial.println("Step forward");
    step_forward(5);
    delay(2000);
    Serial.println("Step back");
    step_back(5);
    delay(2000);
    Serial.println("Turn left");
    turn_left(5);
    delay(2000);
    Serial.println("Turn right");
    turn_right(5);
    delay(2000);
}

/*
  sound = analogRead(voice);
  if (sound >= 210 && sound <= 240){
  aktif = 1;
  }
  while(aktif == 1){
  /////////////// coding disini ///////////////
  digitalWrite(led, HIGH);
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  sonar();
*/

//////////////////////////////////////////////////////////////////////////////// SENSOR
void sonar() {
    pinMode(echoPin1, OUTPUT);
    digitalWrite(echoPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(echoPin1, LOW);
    pinMode(echoPin1, INPUT);
    duration1 = pulseIn(echoPin1, HIGH);
    distance1 = (duration1 / 2) / 29.1;

    pinMode(echoPin2, OUTPUT);
    digitalWrite(echoPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(echoPin2, LOW);
    pinMode(echoPin2, INPUT);
    duration2 = pulseIn(echoPin2, HIGH);
    distance2 = (duration2 / 2) / 29.1;

    pinMode(echoPin3, OUTPUT);
    digitalWrite(echoPin3, HIGH);
    delayMicroseconds(10);
    digitalWrite(echoPin3, LOW);
    pinMode(echoPin3, INPUT);
    duration3 = pulseIn(echoPin3, HIGH);
    distance3 = (duration3 / 2) / 29.1;

    pinMode(echoPin4, OUTPUT);
    digitalWrite(echoPin4, HIGH);
    delayMicroseconds(10);
    digitalWrite(echoPin4, LOW);
    pinMode(echoPin4, INPUT);
    duration4 = pulseIn(echoPin4, HIGH);
    distance4 = (duration4 / 2) / 29.1;

    pinMode(echoPin5, OUTPUT);
    digitalWrite(echoPin5, HIGH);
    delayMicroseconds(10);
    digitalWrite(echoPin5, LOW);
    pinMode(echoPin5, INPUT);
    duration5 = pulseIn(echoPin5, HIGH);
    distance5 = (duration5 / 2) / 29.1;

    pinMode(echoPin6, OUTPUT);
    digitalWrite(echoPin6, HIGH);
    delayMicroseconds(10);
    digitalWrite(echoPin6, LOW);
    pinMode(echoPin6, INPUT);
    duration6 = pulseIn(echoPin6, HIGH);
    distance6 = (duration6 / 2) / 29.1;

    pinMode(echoPin7, OUTPUT);
    digitalWrite(echoPin7, HIGH);
    delayMicroseconds(10);
    digitalWrite(echoPin7, LOW);
    pinMode(echoPin7, INPUT);
    duration7 = pulseIn(echoPin7, HIGH);
    distance7 = (duration7 / 2) / 29.1;
}

void sit(void){
    move_speed = 1;
    
    for (int leg = 0; leg < 4; leg++){
        set_site(leg, 255, 255, -28);
    }
    
    wait_all_reach();
}

/*
  - stand
  - blocking function
   ---------------------------------------------------------------------------*/
void stand(void){
    move_speed = 1;
    
    for (int leg = 0; leg < 4; leg++){
        set_site(leg, 255, 255, -50);
    }

    wait_all_reach();
}

/*
  - spot turn to left
  - blocking function
  - parameter step steps wanted to turn
   ---------------------------------------------------------------------------*/
void turn_left(unsigned int step){
    move_speed = 4;
    
    while (step-- > 0){
        if (site_now[3][1] == 0){
            //leg 3&1 move
            set_site(3, 62 + 0, 0, -30);
            wait_all_reach();

            set_site(0, turn_x1 - 0, turn_y1, -50);
            set_site(1, turn_x0 - 0, turn_y0, -50);
            set_site(2, turn_x1 + 0, turn_y1, -50);
            set_site(3, turn_x0 + 0, turn_y0, -30);
            wait_all_reach();

            set_site(3, turn_x0 + 0, turn_y0, -50);
            wait_all_reach();

            set_site(0, turn_x1 + 0, turn_y1, -50);
            set_site(1, turn_x0 + 0, turn_y0, -50);
            set_site(2, turn_x1 - 0, turn_y1, -50);
            set_site(3, turn_x0 - 0, turn_y0, -50);
            wait_all_reach();

            set_site(1, turn_x0 + 0, turn_y0, -30);
            wait_all_reach();

            set_site(0, 62 + 0, 0, -50);
            set_site(1, 62 + 0, 0, -30);
            set_site(2, 62 - 0, 0 + 40, -50);
            set_site(3, 62 - 0, 0 + 40, -50);
            wait_all_reach();

            set_site(1, 62 + 0, 0, -50);
            wait_all_reach();
        } else {
            //leg 0&2 move
            set_site(0, 62 + 0, 0, -30);
            wait_all_reach();

            set_site(0, turn_x0 + 0, turn_y0, -30);
            set_site(1, turn_x1 + 0, turn_y1, -50);
            set_site(2, turn_x0 - 0, turn_y0, -50);
            set_site(3, turn_x1 - 0, turn_y1, -50);
            wait_all_reach();

            set_site(0, turn_x0 + 0, turn_y0, -50);
            wait_all_reach();

            set_site(0, turn_x0 - 0, turn_y0, -50);
            set_site(1, turn_x1 - 0, turn_y1, -50);
            set_site(2, turn_x0 + 0, turn_y0, -50);
            set_site(3, turn_x1 + 0, turn_y1, -50);
            wait_all_reach();

            set_site(2, turn_x0 + 0, turn_y0, -30);
            wait_all_reach();

            set_site(0, 62 - 0, 0 + 40, -50);
            set_site(1, 62 - 0, 0 + 40, -50);
            set_site(2, 62 + 0, 0, -30);
            set_site(3, 62 + 0, 0, -50);
            wait_all_reach();

            set_site(2, 62 + 0, 0, -50);
            wait_all_reach();
        }
    }
}

/*
  - spot turn to right
  - blocking function
  - parameter step steps wanted to turn
   ---------------------------------------------------------------------------*/
void turn_right(unsigned int step){
    move_speed = 4;
    while (step-- > 0){
        if (site_now[2][1] == 0){
            //leg 2&0 move
            set_site(2, 62 + 0, 0, -30);
            wait_all_reach();

            set_site(0, turn_x0 - 0, turn_y0, -50);
            set_site(1, turn_x1 - 0, turn_y1, -50);
            set_site(2, turn_x0 + 0, turn_y0, -30);
            set_site(3, turn_x1 + 0, turn_y1, -50);
            wait_all_reach();

            set_site(2, turn_x0 + 0, turn_y0, -50);
            wait_all_reach();

            set_site(0, turn_x0 + 0, turn_y0, -50);
            set_site(1, turn_x1 + 0, turn_y1, -50);
            set_site(2, turn_x0 - 0, turn_y0, -50);
            set_site(3, turn_x1 - 0, turn_y1, -50);
            wait_all_reach();

            set_site(0, turn_x0 + 0, turn_y0, -30);
            wait_all_reach();

            set_site(0, 62 + 0, 0, -30);
            set_site(1, 62 + 0, 0, -50);
            set_site(2, 62 - 0, 0 + 40, -50);
            set_site(3, 62 - 0, 0 + 40, -50);
            wait_all_reach();

            set_site(0, 62 + 0, 0, -50);
            wait_all_reach();
        } else {
            //leg 1&3 move
            set_site(1, 62 + 0, 0, -30);
            wait_all_reach();

            set_site(0, turn_x1 + 0, turn_y1, -50);
            set_site(1, turn_x0 + 0, turn_y0, -30);
            set_site(2, turn_x1 - 0, turn_y1, -50);
            set_site(3, turn_x0 - 0, turn_y0, -50);
            wait_all_reach();

            set_site(1, turn_x0 + 0, turn_y0, -50);
            wait_all_reach();

            set_site(0, turn_x1 - 0, turn_y1, -50);
            set_site(1, turn_x0 - 0, turn_y0, -50);
            set_site(2, turn_x1 + 0, turn_y1, -50);
            set_site(3, turn_x0 + 0, turn_y0, -50);
            wait_all_reach();

            set_site(3, turn_x0 + 0, turn_y0, -30);
            wait_all_reach();

            set_site(0, 62 - 0, 0 + 40, -50);
            set_site(1, 62 - 0, 0 + 40, -50);
            set_site(2, 62 + 0, 0, -50);
            set_site(3, 62 + 0, 0, -30);
            wait_all_reach();

            set_site(3, 62 + 0, 0, -50);
            wait_all_reach();
        }
    }
}

/*
  - go forward
  - blocking function
  - parameter step steps wanted to go
   ---------------------------------------------------------------------------*/
void step_forward(unsigned int step){
    move_speed = 8;
    while (step-- > 0){
        if (site_now[2][1] == 0){
            //leg 2&1 move
            set_site(2, 62 + 0, 0, -30);
            wait_all_reach();
            set_site(2, 62 + 0, 0 + 2 * 40, -30);
            wait_all_reach();
            set_site(2, 62 + 0, 0 + 2 * 40, -50);
            wait_all_reach();

            move_speed = 3;

            set_site(0, 62 + 0, 0, -50);
            set_site(1, 62 + 0, 0 + 2 * 40, -50);
            set_site(2, 62 - 0, 0 + 40, -50);
            set_site(3, 62 - 0, 0 + 40, -50);
            wait_all_reach();

            move_speed = 8;

            set_site(1, 62 + 0, 0 + 2 * 40, -30);
            wait_all_reach();
            set_site(1, 62 + 0, 0, -30);
            wait_all_reach();
            set_site(1, 62 + 0, 0, -50);
            wait_all_reach();
        } else {
            //leg 0&3 move
            set_site(0, 62 + 0, 0, -30);
            wait_all_reach();
            set_site(0, 62 + 0, 0 + 2 * 40, -30);
            wait_all_reach();
            set_site(0, 62 + 0, 0 + 2 * 40, -50);
            wait_all_reach();

            move_speed = 3;

            set_site(0, 62 - 0, 0 + 40, -50);
            set_site(1, 62 - 0, 0 + 40, -50);
            set_site(2, 62 + 0, 0, -50);
            set_site(3, 62 + 0, 0 + 2 * 40, -50);
            wait_all_reach();

            move_speed = 8;

            set_site(3, 62 + 0, 0 + 2 * 40, -30);
            wait_all_reach();
            set_site(3, 62 + 0, 0, -30);
            wait_all_reach();
            set_site(3, 62 + 0, 0, -50);
            wait_all_reach();
        }
    }
}

/*
  - go back
  - blocking function
  - parameter step steps wanted to go
   ---------------------------------------------------------------------------*/
void step_back(unsigned int step){
    move_speed = 8;
    while (step-- > 0){
        if (site_now[3][1] == 0){
            //leg 3&0 move
            set_site(3, 62 + 0, 0, -30);
            wait_all_reach();
            set_site(3, 62 + 0, 0 + 2 * 40, -30);
            wait_all_reach();
            set_site(3, 62 + 0, 0 + 2 * 40, -50);
            wait_all_reach();

            move_speed = 3;

            set_site(0, 62 + 0, 0 + 2 * 40, -50);
            set_site(1, 62 + 0, 0, -50);
            set_site(2, 62 - 0, 0 + 40, -50);
            set_site(3, 62 - 0, 0 + 40, -50);
            wait_all_reach();

            move_speed = 8;

            set_site(0, 62 + 0, 0 + 2 * 40, -30);
            wait_all_reach();
            set_site(0, 62 + 0, 0, -30);
            wait_all_reach();
            set_site(0, 62 + 0, 0, -50);
            wait_all_reach();
        } else {
            //leg 1&2 move
            set_site(1, 62 + 0, 0, -30);
            wait_all_reach();
            set_site(1, 62 + 0, 0 + 2 * 40, -30);
            wait_all_reach();
            set_site(1, 62 + 0, 0 + 2 * 40, -50);
            wait_all_reach();

            move_speed = 3;

            set_site(0, 62 - 0, 0 + 40, -50);
            set_site(1, 62 - 0, 0 + 40, -50);
            set_site(2, 62 + 0, 0 + 2 * 40, -50);
            set_site(3, 62 + 0, 0, -50);
            wait_all_reach();

            move_speed = 8;

            set_site(2, 62 + 0, 0 + 2 * 40, -30);
            wait_all_reach();
            set_site(2, 62 + 0, 0, -30);
            wait_all_reach();
            set_site(2, 62 + 0, 0, -50);
            wait_all_reach();
        }
    }
}

// add by RegisHsu
void body_left(int i){
    set_site(0, site_now[0][0] + i, 255, 255);
    set_site(1, site_now[1][0] + i, 255, 255);
    set_site(2, site_now[2][0] - i, 255, 255);
    set_site(3, site_now[3][0] - i, 255, 255);
    wait_all_reach();
}

void body_right(int i){
    set_site(0, site_now[0][0] - i, 255, 255);
    set_site(1, site_now[1][0] - i, 255, 255);
    set_site(2, site_now[2][0] + i, 255, 255);
    set_site(3, site_now[3][0] + i, 255, 255);
    wait_all_reach();
}

void hand_wave(int i){
    float x_tmp;
    float y_tmp;
    float z_tmp;
    move_speed = 1;
    
    if (site_now[3][1] == 0){
        
        body_right(15);
        
        x_tmp = site_now[2][0];
        y_tmp = site_now[2][1];
        z_tmp = site_now[2][2];
        move_speed = 3;
        
        for (int j = 0; j < i; j++){
            set_site(2, turn_x1, turn_y1, 50);
            wait_all_reach();
            set_site(2, turn_x0, turn_y0, 50);
            wait_all_reach();
        }
        
        set_site(2, x_tmp, y_tmp, z_tmp);
        wait_all_reach();
        move_speed = 1;
        body_left(15);
        
        } else {
        
        body_left(15);
        
        x_tmp = site_now[0][0];
        y_tmp = site_now[0][1];
        z_tmp = site_now[0][2];
        move_speed = 3;
        
        for (int j = 0; j < i; j++){
            set_site(0, turn_x1, turn_y1, 50);
            wait_all_reach();
            set_site(0, turn_x0, turn_y0, 50);
            wait_all_reach();
        }

        set_site(0, x_tmp, y_tmp, z_tmp);
        wait_all_reach();
        move_speed = 1;
        body_right(15);
    }
}

void hand_shake(int i){
    float x_tmp;
    float y_tmp;
    float z_tmp;
    move_speed = 1;
    
    if (site_now[3][1] == 0){
        
        body_right(15);
        
        x_tmp = site_now[2][0];
        y_tmp = site_now[2][1];
        z_tmp = site_now[2][2];
        move_speed = 3;
        
        for (int j = 0; j < i; j++){
            set_site(2, 62 - 30, 0 + 2 * 40, 55);
            wait_all_reach();
            set_site(2, 62 - 30, 0 + 2 * 40, 10);
            wait_all_reach();
        }

        set_site(2, x_tmp, y_tmp, z_tmp);
        wait_all_reach();
        move_speed = 1;
        body_left(15);
    
    } else {
    
        body_left(15);
        
        x_tmp = site_now[0][0];
        y_tmp = site_now[0][1];
        z_tmp = site_now[0][2];
        move_speed = 3;
        
        for (int j = 0; j < i; j++){
            set_site(0, 62 - 30, 0 + 2 * 40, 55);
            wait_all_reach();
            set_site(0, 62 - 30, 0 + 2 * 40, 10);
            wait_all_reach();
        }

        set_site(0, x_tmp, y_tmp, z_tmp);
        wait_all_reach();
        move_speed = 1;
        body_right(15);
    }
}

void head_up(int i){
    set_site(0, 255, 255, site_now[0][2] - i);
    set_site(1, 255, 255, site_now[1][2] + i);
    set_site(2, 255, 255, site_now[2][2] - i);
    set_site(3, 255, 255, site_now[3][2] + i);
    wait_all_reach();
}

void head_down(int i){
    set_site(0, 255, 255, site_now[0][2] + i);
    set_site(1, 255, 255, site_now[1][2] - i);
    set_site(2, 255, 255, site_now[2][2] + i);
    set_site(3, 255, 255, site_now[3][2] - i);
    wait_all_reach();
}

void body_dance(int i){
    float x_tmp;
    float y_tmp;
    float z_tmp;
    float body_dance_speed = 2;
    
    sit();
    
    move_speed = 1;
    set_site(0, 62, 62, 255);
    set_site(1, 62, 62, 255);
    set_site(2, 62, 62, 255);
    set_site(3, 62, 62, 255);
    wait_all_reach();
    
    //stand();
    set_site(0, 62, 62, -50 - 20);
    set_site(1, 62, 62, -50 - 20);
    set_site(2, 62, 62, -50 - 20);
    set_site(3, 62, 62, -50 - 20);
    wait_all_reach();
    
    move_speed = body_dance_speed;
    head_up(30);
    
    for (int j = 0; j < i; j++){
        
        if (j > i / 4)
            move_speed = body_dance_speed * 2;
        
        if (j > i / 2)
            move_speed = body_dance_speed * 3;
        
        set_site(0, 255, 62 - 20, 255);
        set_site(1, 255, 62 + 20, 255);
        set_site(2, 255, 62 - 20, 255);
        set_site(3, 255, 62 + 20, 255);
        wait_all_reach();
    
        set_site(0, 255, 62 + 20, 255);
        set_site(1, 255, 62 - 20, 255);
        set_site(2, 255, 62 + 20, 255);
        set_site(3, 255, 62 - 20, 255);
        wait_all_reach();
    }
    move_speed = body_dance_speed;
    head_down(30);
}


/*
  - microservos service /timer interrupt function/50Hz
  - when set site expected,this function move the end point to it in a straight line
  - temp_speed[4][3] should be set before set expect site,it make sure the end point
   move in a straight line,and decide move speed.
   ---------------------------------------------------------------------------*/
void servo_service(void){
    sei();
    static float alpha, beta, gamma;

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 3; j++){
    
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
void set_site(int leg, float x, float y, float z){
    float length_x = 0;
    float length_y = 0;
    float length_z = 0;

    if (x != 255)
        length_x = x - site_now[leg][0];
    
    if (y != 255)
        length_y = y - site_now[leg][1];
 
    if (z != 255)
        length_z = z - site_now[leg][2];

    float length = sqrt(pow(length_x, 2) + pow(length_y, 2) + pow(length_z, 2));

    temp_speed[leg][0] = length_x / length * move_speed * 1;
    temp_speed[leg][1] = length_y / length * move_speed * 1;
    temp_speed[leg][2] = length_z / length * move_speed * 1;

    if (x != 255)
        site_expect[leg][0] = x;

    if (y != 255)
        site_expect[leg][1] = y;
    
    if (z != 255)
        site_expect[leg][2] = z;
}

/*
  - wait one of end points move to expect site
  - blocking function
   ---------------------------------------------------------------------------*/
void wait_reach(int leg){
    while (1) {
        if (site_now[leg][0] == site_expect[leg][0]){
            if (site_now[leg][1] == site_expect[leg][1]){
                if (site_now[leg][2] == site_expect[leg][2]){
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
    for (int i = 0; i < 4; i++){
        wait_reach(i);
    }
}

/*
  - trans site from cartesian to polar
  - mathematical model 2/2
   ---------------------------------------------------------------------------*/
void cartesian_to_polar(volatile float &alpha, 
                        volatile float &beta, 
                        volatile float &gamma, 
                        volatile float x, 
                        volatile float y, 
                        volatile float z){

    //calculate w-z degree
    float v, w;
    
    w = (x >= 0 ? 1 : -1) * (sqrt(pow(x, 2) + pow(y, 2)));
    v = w - 77.5;
    
    alpha = atan2(z, v) + acos((pow(55, 2) - pow(77.5, 2) + pow(v, 2) + pow(z, 2)) / 2 / 55 / sqrt(pow(v, 2) + pow(z, 2)));
    beta = acos((pow(55, 2) + pow(77.5, 2) - pow(v, 2) - pow(z, 2)) / 2 / 55 / 77.5);
    
    //calculate x-y-z degree
    gamma = (w >= 0) ? atan2(y, x) : atan2(-y, -x);
    
    //trans degree pi->180
    alpha = alpha / pi * 180;
    beta = beta / pi * 180;
    gamma = gamma / pi * 180;
}

/*
  - trans site from polar to microservos
  - mathematical model map to fact
  - the errors saved in eeprom will be add
   ---------------------------------------------------------------------------*/
void polar_to_servo(int leg, float alpha, float beta, float gamma){
    if (leg == 0){
        alpha = 90 - alpha;
        beta = beta;
        gamma += 90;
    } else if (leg == 1) {
        alpha += 90;
        beta = 180 - beta;
        gamma = 90 - gamma;
    } else if (leg == 2) {
        alpha += 90;
        beta = 180 - beta;
        gamma = 90 - gamma;
    } else if (leg == 3) {
        alpha = 90 - alpha;
        beta = beta;
        gamma += 90;
    }

    servo[leg][0].write(alpha);
    servo[leg][1].write(beta);
    servo[leg][2].write(gamma);
}