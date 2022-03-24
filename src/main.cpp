#include "Client.cpp"

void setup()
{
    Serial.begin(115200);
    c2s.ID = PID;
    initESPNOW();
    // Sensors pins configurations
    pinMode(FEEDMAXREQ, INPUT);
    pinMode(ARBURGREQ, INPUT);
    pinMode(FEEDMAXLVL, INPUT);
}
void loop()
{
}