#include "Server.cpp"

ServerP s;
void setup() 
{
    Serial.begin(115200);
    s.startESPNOW();
    Serial.printf("The server mac add : ");
    s.printLocalMacAdd();
}
void loop()
{
}