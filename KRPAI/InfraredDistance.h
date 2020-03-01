class InfDistance
{
    public:
    float distance;
    uint8_t pin;

    InfDistance(uint8_t _pin)
    {
        pin = _pin;
    }

    void read_distance()
    {
        float volts = analogRead(A0) * 0.0048828125;    // value from sensor * (5/1024)
        distance = 13 * pow(volts, -1);                 // worked out from datasheet graph
    }
};

/* Infrared Distance --------------------------------------------------------------------*/
InfDistance infDistance[] = {
    InfDistance(INF_DISTANCE_FRONT_PIN),    //Front
    InfDistance(INF_DISTANCE_LEFT_PIN),     //Left
    InfDistance(INF_DISTANCE_RIGHT_PIN),    //Right
};

void read_all_ir_distance()
{
    infDistance[INF_DISTANCE_FRONT].read_distance();
    infDistance[INF_DISTANCE_LEFT].read_distance();
    infDistance[INF_DISTANCE_RIGHT].read_distance();
}
