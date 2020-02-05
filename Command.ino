void command_init(void)
{
    #if DEBUG_COMMAND && DEBUG
    SerialCommandHandler.AddCommand(F("servo_angle"),   Cmd_SetServoAngle);
    SerialCommandHandler.AddCommand(F("servo_pos"),     Cmd_SetServoPos);

    SerialCommandHandler.AddCommand(F("stand"),         Cmd_Stand);
    SerialCommandHandler.AddCommand(F("sit"),           Cmd_Sit);
    SerialCommandHandler.AddCommand(F("turn_right"),    Cmd_Turn_Right);
    SerialCommandHandler.AddCommand(F("turn_left"),     Cmd_Turn_Left);
    SerialCommandHandler.AddCommand(F("step_forward"),  Cmd_Step_Forward);
    SerialCommandHandler.AddCommand(F("step_back"),     Cmd_Step_Back);
    SerialCommandHandler.AddCommand(F("body_left"),     Cmd_Body_Left);
    SerialCommandHandler.AddCommand(F("body_right"),    Cmd_Body_Right);
    SerialCommandHandler.AddCommand(F("hand_wave"),     Cmd_Hand_Wave);
    SerialCommandHandler.AddCommand(F("hand_shake"),    Cmd_Hand_Shake);
    
    SerialCommandHandler.SetDefaultHandler(Cmd_Unknown);
    #endif
}

#if DEBUG_COMMAND && DEBUG

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

void Cmd_SetServoPos(CommandParameter &Parameters)
{
    uint8_t leg = Parameters.NextParameterAsInteger();
    uint8_t x = Parameters.NextParameterAsInteger();
    uint8_t y = Parameters.NextParameterAsInteger();
    uint8_t z = Parameters.NextParameterAsInteger();
    uint8_t speed = Parameters.NextParameterAsInteger();

    if (leg < 0 || leg >= 4)
        return;

    move_speed = speed;
    set_site(leg, x, y, z);
    wait_reach(leg);
}

void Cmd_Stand(CommandParameter &Parameters)
{
    stand();
}

void Cmd_Sit(CommandParameter &Parameters)
{
    sit();
}

void Cmd_Turn_Right(CommandParameter &Parameters)
{
    uint16_t param = Parameters.NextParameterAsInteger();
    
    if (param > 0)
        turn_right(param);
}


void Cmd_Turn_Left(CommandParameter &Parameters)
{
    uint16_t param = Parameters.NextParameterAsInteger();

    if (param > 0)
        turn_left(param);
}


void Cmd_Step_Forward(CommandParameter &Parameters)
{
    uint16_t param = Parameters.NextParameterAsInteger();

    if (param > 0)
        step_forward(param);
}

void Cmd_Step_Back(CommandParameter &Parameters)
{
    uint16_t param = Parameters.NextParameterAsInteger();

    if (param > 0)
        step_back(param);
}

void Cmd_Body_Left(CommandParameter &Parameters)
{
    uint16_t param = Parameters.NextParameterAsInteger();

    if (param > 0)
        body_left(param);
}

void Cmd_Body_Right(CommandParameter &Parameters)
{
    uint16_t param = Parameters.NextParameterAsInteger();

    if (param > 0)
        body_right(param);
}

void Cmd_Hand_Wave(CommandParameter &Parameters)
{
    uint16_t param = Parameters.NextParameterAsInteger();

    if (param > 0)
        hand_wave(param);
}

void Cmd_Hand_Shake(CommandParameter &Parameters)
{
    uint16_t param = Parameters.NextParameterAsInteger();

    if (param > 0)
        hand_shake(param);
}
#endif
