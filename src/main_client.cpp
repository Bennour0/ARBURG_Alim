#include "Client.cpp"

/*(uint8_t id, uint8_t sen_feedmax_pin, uint8_t sen_arburg_pin, uint8_t sen_feedmax_lvl_pin,
          uint8_t vlv_charger_pin, uint8_t vlv_feedmax_pin, uint8_t vlv_drymax_pin)*/
ClientP c(1, 15, 2, 4, 23, 22, 1);
t_c2s m;

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting client program");
    c.begin();
    Serial.print("The client mac add : ");
    c.printMacAdd();
    Serial.printf("\nThe server mac add : ");
    c.printServer();
    Serial.println();
}
void loop()
{
    /*c.send2server();
    delay(2000);*/
}