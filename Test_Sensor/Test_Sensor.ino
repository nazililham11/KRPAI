#include "ATMega128_Arduino_Pin.h"
#include "Ultrasonic_lib.h"

Ultrasonic ultrasonic[] = {
    Ultrasonic(PORT_E_5), //Front
    Ultrasonic(PORT_C_6), //Left
    Ultrasonic(PORT_E_7), //Right
    Ultrasonic(PORT_C_7), //Front Left
    Ultrasonic(PORT_E_6)  //Front Right
};

float ir_distance;

void setup(){
    Serial.begin(115200);
    Serial.println("Sensor Test");
}

void loop(){
    read_distance();
    read_ir_distance();
    print_distance();
    print_ir_distance();
    Serial.println();
    delay(100);
}

void read_ir_distance()
{
    float volts = analogRead(A0) * 0.0048828125;  // value from sensor * (5/1024)
    ir_distance = 13 * pow(volts, -1);                 // worked out from datasheet graph
}

void print_ir_distance(void)
{
    if (ir_distance <= 30){
        Serial.print(F("\tIR Distance"));
        Serial.print(ir_distance);   // print the distance
    }
}

void read_distance(){
    ultrasonic[US_FRONT].read_distance();
    ultrasonic[US_LEFT].read_distance();
    ultrasonic[US_RIGHT].read_distance();
    ultrasonic[US_FRONT_LEFT].read_distance();
    ultrasonic[US_FRONT_RIGHT].read_distance();
}

void print_distance(){
    Serial.print(F("Front:"));
    Serial.print(String(ultrasonic[US_FRONT].distance));
    Serial.print(F("\tLeft:"));
    Serial.print(String(ultrasonic[US_LEFT].distance));
    Serial.print(F("\tRight:"));
    Serial.print(String(ultrasonic[US_RIGHT].distance));
    Serial.print(F("\tFront Left:"));
    Serial.print(String(ultrasonic[US_FRONT_LEFT].distance));
    Serial.print(F("\tFront Right:"));
    Serial.print(String(ultrasonic[US_FRONT_RIGHT].distance));
}
