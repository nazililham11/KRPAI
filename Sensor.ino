void read_all_distance(void)
{
    for (uint8_t i = 0; i < 5; i++)
    {
        ultrasonic[i].read_distance();
    }
}