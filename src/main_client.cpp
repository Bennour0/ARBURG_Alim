#include "Client.cpp"

/*(uint8_t id, uint8_t sen_feedmax_pin, uint8_t sen_arburg_pin, uint8_t sen_feedmax_lvl_pin,
          uint8_t vlv_charger_pin, uint8_t vlv_feedmax_pin, uint8_t vlv_drymax_pin)*/
ClientP c(1, 27, 26, 25, 13, 12, 14);
t_c2s m;

void setup()
{
    Serial.begin(115200);
    pinMode(27,INPUT);
    pinMode(26,INPUT);
    pinMode(25,INPUT);
    pinMode(13,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(14,OUTPUT);
    Serial.println("Starting client program");
    c.startESPNOW();
    Serial.print("The client mac add : ");
    c.printMacAdd();
    Serial.printf("\nThe server mac add : ");
    c.printServer();
    Serial.println();
}
void loop()
{
    c.send2server();
    c.runClient();
    delay(2000);
}