#include "ATMega128_Arduino_Pin.h"
#include "Ultrasonic_lib.h"

Ultrasonic ultrasonic[] = {
    Ultrasonic(PORT_E_0), //Front
    Ultrasonic(PORT_C_6), //Left
    Ultrasonic(PORT_E_2), //Right
    Ultrasonic(PORT_C_7), //Front Left
    Ultrasonic(PORT_E_1)  //Front Right
};

void setup(){
    Serial.begin(115200);
}

void loop(){
    read_distance();
    print_distance();
    delay(1000);
}

void read_distance(){
    ultrasonic[US_FRONT].read_distance();
    ultrasonic[US_LEFT].read_distance();
    ultrasonic[US_RIGHT].read_distance();
    ultrasonic[US_FRONT_LEFT].read_distance();
    ultrasonic[US_FRONT_RIGHT].read_distance();
}

void print_distance(){
    Serial.println("Distance");
    Serial.print(F("Front:"));
    Serial.print(String(ultrasonic[US_FRONT].distance));
    Serial.print("\tLeft:");
    Serial.print(String(ultrasonic[US_LEFT].distance));
    Serial.print("\tRight:");
    Serial.print(String(ultrasonic[US_RIGHT].distance));
    Serial.print("\tFront Left:");
    Serial.print(String(ultrasonic[US_FRONT_LEFT].distance));
    Serial.print("\tFront Right:");
    Serial.print(String(ultrasonic[US_FRONT_RIGHT].distance));
    Serial.println();
}