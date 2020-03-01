
void calculatePID(void)
{
    // P = error;
    // I = I + error;
    // D = error - previousError;
    // PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
    // previousError = error;
}

void checkPIDvalues(void)
{
    Serial.print("PID: ");
    Serial.print(Kp);
    Serial.print(" - ");
    Serial.print(Ki);
    Serial.print(" - ");
    Serial.println(Kd);
}