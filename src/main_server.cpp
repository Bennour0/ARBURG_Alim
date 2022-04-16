#include "Server.cpp"

ServerP s;
void setup() 
{
    Serial.begin(115200);
    s.printMacAdd();
    s.startESPNOW();
    /*Serial.begin(115200);
    initESPNOW();*/
}
void loop()
{
}