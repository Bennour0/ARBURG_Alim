#include "Server.cpp"

ServerP s;
void setup() 
{
    Serial.begin(115200);
    // initESPNOW();
    s.startESPNOW();
    Serial.printf("The server mac add : ");
    s.printLocalMacAdd();
    /*Serial.begin(115200);
    initESPNOW();*/
}
void loop()
{
}