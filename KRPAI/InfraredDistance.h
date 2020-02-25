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



void read_all_ir_distance()
{

}
