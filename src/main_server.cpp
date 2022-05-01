#include "Server.cpp"

ServerP s;
t_s2c s2c;
void setup() 
{
    Serial.begin(115200);
    rtc.setTime(00, 07, 17, 01, 05, 2022);
    s.startESPNOW();
    Serial.printf("The server mac add : ");
    s.printLocalMacAdd();
}
void loop()
{
    s.broadcast(s2c);
    delay(2000);
}