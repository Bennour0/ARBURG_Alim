#include "Server.cpp"

ServerP s;
t_s2c s2c;
void setup() 
{
    Serial.begin(115200);
    s.startESPNOW();
    Serial.printf("The server mac add : ");
    s.printLocalMacAdd();
}
void loop()
{
    s.broadcast(s2c);
    delay(2000);
}