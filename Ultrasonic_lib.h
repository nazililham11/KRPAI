#define US_FRONT 0
#define US_FRONT        0
#define US_LEFT         1
#define US_RIGHT        2
#define US_FRONT_LEFT   3
#define US_FRONT_RIGHT  4

class Ultrasonic {
    public:
        float distance;
        uint8_t pin;

        Ultrasonic(uint8_t _pin){
            pin = _pin;
        }

        void read_distance(){
            pinMode(pin, OUTPUT);

            digitalWrite(pin, HIGH);
            delayMicroseconds(10);
            digitalWrite(pin, LOW);

            pinMode(pin, INPUT);

            distance = pulseIn(pin, HIGH);
            distance = (distance / 2.0) / 29.1;
        }
};