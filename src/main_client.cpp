#include "Client.cpp"

/*(uint8_t id, uint8_t sen_feedmax_pin, uint8_t sen_arburg_pin, uint8_t sen_feedmax_lvl_pin,
          uint8_t vlv_charger_pin, uint8_t vlv_feedmax_pin, uint8_t vlv_drymax_pin)*/
ClientP c(1, 2, 3, 4, 5, 6, 7);

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting client program");
    c.startESPNOW();
}
void loop()
{
}