#include "ATMega128_Arduino_Pin.h"
#include <Servo.h>
#include <CommandHandler.h>
#include "Values.h"

#define SERVO_HOME_ANGLE 90

const uint8_t servo_pin[4][3] = {{PORT_A_0, PORT_A_1, PORT_A_2},
                                 {PORT_D_0, PORT_D_1, PORT_D_2},
                                 {PORT_B_7, PORT_B_6, PORT_B_5},
                                 {PORT_F_7, PORT_F_6, PORT_F_5}};

const uint8_t servo_home_angle[4][3] = {{90, 90, 90 - 20},  //Depan Kanan
                                        {90, 90, 90 + 20},  //Belakang Kanan
                                        {90, 90, 90 - 20},  //Belakang Kiri
                                        {90, 90, 90 + 20}}; //Depan Kiri

Servo servo[4][3];
CommandHandler<> SerialCommandHandler(Serial, '[', ']');

void setup()
{
    init_command();
    init_servo();
    goto_servo_home();
    delay(5000);
}

void loop()
{
    SerialCommandHandler.Process();
}

void init_servo()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            servo[i][j].attach(servo_pin[i][j]);
        }
    }
}

void goto_servo_home()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            servo[i][j].write(servo_home_angle[i][j]);
        }
    }
}

void init_command()
{
    Serial.begin(9600);
    SerialCommandHandler.AddCommand(F("servo"), Cmd_SetServoAngle);
    SerialCommandHandler.SetDefaultHandler(Cmd_Unknown);
}

void Cmd_Unknown()
{
    Serial.println(F("Unknown command."));
}

void Cmd_SetServoAngle(CommandParameter &Parameters)
{
    int leg_number = Parameters.NextParameterAsInteger();

    if (leg_number < 0 || leg_number >= 4)
        return;

    int servo_number = Parameters.NextParameterAsInteger();

    if (servo_number < 0 || servo_number >= 3)
        return;

    int angle = Parameters.NextParameterAsInteger();

    if (angle < 0 || angle >= 180)
        return;

    servo[leg_number][servo_number].write(angle);
}
