/*
- setup function
  ---------------------------------------------------------------------------*/
void setup()
{
    //start serial for debug
    Serial.begin(115200);
    Serial.println(F("Robot starts initialization"));

    command_init();

    site_init();           //init default site
    servo_attach();        //initialize servos
    start_servo_service(); //start servo service

    Serial.println(F("Robot initialization Complete"));

    Serial.println(F("Stand"));
    stand();
    delay(5000);
}

/*
  - loop function
   ---------------------------------------------------------------------------*/
void loop()
{

    // Serial.println(F("Turn left"));
    // turn_left(5);
    // delay(2000);

    // Serial.println(F("Turn right"));
    // turn_right(5);
    // delay(2000);

    Serial.println(F("Step forward"));
    step_forward(10);
    delay(2000);

    // Serial.println(F("Sit"));
    // sit();
    // delay(5000);
}