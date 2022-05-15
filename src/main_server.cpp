#include "Server.cpp"

/*(uint8_t pump_pin, uint8_t vlv1_pin, uint8_t vlv2_pin, uint8_t vlvr_pin)*/
ServerP s(13,12,14,27);

void setup() 
{
    Serial.begin(115200);
    rtc.setTime(00, 45, 13, 03, 05, 2022);
    Serial.println("Starting server program");
    s.begin();
    Serial.printf("The server mac add : ");
    s.printLocalMacAdd();
}
void loop()
{
    while
    (!qg.empty())
    {
        s.broadcast();
        delay(1000);
    }
}