class Ultrasonic
{
    public:
    float distance;
    uint8_t pin;

    Ultrasonic(uint8_t _pin)
    {
        pin = _pin;
    }

    float read_distance()
    {
        pinMode(pin, OUTPUT);

        digitalWrite(pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(pin, LOW);

        pinMode(pin, INPUT);

        distance = pulseIn(pin, HIGH);
        distance = (distance / 2.0) / 29.1;
        
        return distance;
    }

    float read_mean_distance(uint8_t loop_count = ULTRASONIC_MEAN_COUNT)
    {

        float total = 0;

        for (uint8_t i = 0; i < loop_count; i++)
        {
            read_distance();
            total = total + distance;
        }

        distance = (float)total / (float)loop_count;

        return distance;
    }
};

/* Ultrasonic --------------------------------------------------------------------*/
Ultrasonic ultrasonic[] = {
    Ultrasonic(ULTRASONIC_FRONT),       //Front
    Ultrasonic(ULTRASONIC_LEFT),        //Left
    Ultrasonic(ULTRASONIC_RIGHT),       //Right
    Ultrasonic(ULTRASONIC_FRONT_LEFT),  //Front Left
    Ultrasonic(ULTRASONIC_FRONT_RIGHT)  //Front Right
};

void read_all_distance(void)
{
    for (uint8_t i = 0; i < 5; i++)
    {
        ultrasonic[i].read_mean_distance();
    }
}


void read_wall(void)
{
    bool front_wall = ultrasonic[ULTRASONIC_FRONT].distance < FRONT_WALL_THRESHOLD;
    bool left_wall  = ultrasonic[ULTRASONIC_LEFT].distance  < LEFT_WALL_THRESHOLD;
    bool right_wall = ultrasonic[ULTRASONIC_RIGHT].distance < RIGHT_WALL_THRESHOLD;
}