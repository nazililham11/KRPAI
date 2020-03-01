#include "PCA9685.h"
#include <Wire.h>

ServoDriver servo;

void servo_init(void);
void setServo(uint8_t leg_id, uint8_t part_id, uint16_t value);
uint8_t getServo_pin(uint8_t leg_id, uint8_t part_id);


void servo_init()
{
    Wire.begin();
    servo.init(0x7f);
}

void setServo(uint8_t leg_id, uint8_t part_id, uint16_t value)
{
    servo.setAngle(getServo_pin(leg_id, part_id), value);
}

uint8_t getServo_pin(uint8_t leg_id, uint8_t part_id)
{
    if (leg_id == 0){
        if      (part_id == 0)  return SERVO_PCA9685_FRONT_LEFT_COXA;
        else if (part_id == 1)  return SERVO_PCA9685_FRONT_LEFT_FEMUR;
        else                    return SERVO_PCA9685_FRONT_LEFT_TIBIA;
    } else if (leg_id == 1){
        if      (part_id == 0)  return SERVO_PCA9685_REAR_LEFT_COXA;
        else if (part_id == 1)  return SERVO_PCA9685_REAR_LEFT_FEMUR;
        else                    return SERVO_PCA9685_REAR_LEFT_TIBIA;
    } else if (leg_id == 2){
        if      (part_id == 0)  return SERVO_PCA9685_FRONT_RIGHT_COXA;
        else if (part_id == 1)  return SERVO_PCA9685_FRONT_RIGHT_FEMUR;
        else                    return SERVO_PCA9685_FRONT_RIGHT_TIBIA;
    } else if (leg_id == 3){
        if      (part_id == 0)  return SERVO_PCA9685_REAR_RIGHT_COXA;
        else if (part_id == 1)  return SERVO_PCA9685_REAR_RIGHT_FEMUR;
        else                    return SERVO_PCA9685_REAR_RIGHT_TIBIA;
    }
}
