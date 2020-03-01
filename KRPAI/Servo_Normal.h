/* Servos --------------------------------------------------------------------*/
//define 12 servos for 4 legs and 3 dof
Servo servo[4][3];
//define servo's ports
const uint8_t servo_pin[4][3] = {
    {FRONT_LEFT_COXA,   FRONT_LEFT_FEMUR,   FRONT_LEFT_TIBIA},    //Front Left
    {REAR_LEFT_COXA,    REAR_LEFT_FEMUR,    REAR_LEFT_TIBIA},       //Rear Left
    {FRONT_RIGHT_COXA,  FRONT_RIGHT_FEMUR,  FRONT_RIGHT_TIBIA}, //Front Right
    {REAR_RIGHT_COXA,   REAR_RIGHT_FEMUR,   REAR_RIGHT_TIBIA}     //Rear Right
};

void servo_init(void);
void servo_attach(void);
void servo_detach(void);
void setServo(uint8_t leg_id, uint8_t part_id, uint16_t value);

void servo_init(void)
{
    servo_attach();
}

void servo_attach(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            servo[i][j].attach(servo_pin[i][j]);
            delay(100);
        }
    }
    Serial.println("Servos initialized");
    }

    void servo_detach(void)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            for (uint8_t j = 0; j < 3; j++)
            {
                servo[i][j].detach();
                delay(100);
            }
        }
    }

    void setServo(uint8_t leg_id, uint8_t part_id, uint16_t value)
    {
        servo[leg_id][part_id].write(value);
    }
