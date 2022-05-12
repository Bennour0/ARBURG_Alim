#include "Client.hpp"
#include "my_debug.hpp"

t_c2s ClientP::c2s;
t_s2c ClientP::s2c;

uint8_t ClientP::sen_feedmax;
uint8_t ClientP::sen_arburg;
uint8_t ClientP::sen_feedmax_lvl;

uint8_t ClientP::vlv_charger;
uint8_t ClientP::vlv_feedmax;
uint8_t ClientP::vlv_drymax;

queue<int> qg;

ClientP::ClientP(uint8_t id, uint8_t sen_feedmax_pin, uint8_t sen_arburg_pin, uint8_t sen_feedmax_lvl_pin,
                 uint8_t vlv_charger_pin, uint8_t vlv_feedmax_pin, uint8_t vlv_drymax_pin)
{
    // this->id = id;
    c2s.ID = id;
    c2s.inout.out = 0;
    c2s.inout.in = 0;
    sen_feedmax = sen_feedmax_pin;
    sen_arburg = sen_arburg_pin;
    sen_feedmax_lvl = sen_feedmax_lvl_pin;
    vlv_charger = vlv_charger_pin;
    vlv_feedmax = vlv_feedmax_pin;
    vlv_drymax = vlv_drymax_pin;
}

void ClientP::printMacAdd()
{
    D_PMA(Serial.println("\nStart ClientP::printMacAdd()");)
    Serial.print(WiFi.macAddress());
    D_PMA(Serial.println("\nEnd ClientP::printMacAdd()");)
}

void ClientP::startESPNOW()
{
    D_SESPNOW(Serial.println("\nStart ClientP::startESPNOW()");)
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    D_SESPNOW(Serial.println("Set board as Wifi station");)
    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    D_SESPNOW(Serial.println("ESP-NOW protol initialised");)
    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    // esp_now_register_send_cb(ServerP::OnDataSent);
    esp_now_register_send_cb(ClientP::OnDataSent);
    // esp_now_register_send_cb(ClientP::pOnSent);
    D_SESPNOW(Serial.println("OnDataSent registred");)
    // Register for a callback function that will be called when data is received
    esp_now_register_recv_cb(ClientP::OnDataRecv);
    D_SESPNOW(Serial.println("OnDataRecv registred");)

    esp_now_peer_info_t peerInfo = {};

    // Registering peers
    memcpy(peerInfo.peer_addr, serverMacAdd, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add server");
        return;
    }
    D_SESPNOW(Serial.printf("Server registred\n");)
    D_SESPNOW(Serial.println("End ClientP::startESPNOW()");)
}

void ClientP::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    D_ODS(Serial.println("Start ClientP::OnDataSent()");)
    c2s.inout.out++;
    D_ODS(Serial.println("End ClientP::OnDataSent()");)
}

void ClientP::showCQ(queue<int> g)
{
    queue<int> t = g;
    while (!t.empty())
    {
        D_SHQ(Serial.printf("| %4d |\n", t.front());)
        t.pop();
    }
}
void ClientP::runClient()
{
    if (s2c.ID == c2s.ID)
    {
        if (digitalRead(sen_feedmax) == HIGH && digitalRead(sen_feedmax_lvl) == LOW)
        {
            qg.push(10);
        }
        if (digitalRead(sen_arburg) == HIGH)
        {
            qg.push(20);
        }
        if (digitalRead(sen_feedmax_lvl) == HIGH && qg.front() == 10)
        {
            qg.pop();
        }
        if (qg.size() >= 1)
        {
            D_SHQ(showCQ(qg);)
        }
        if (qg.front() == 10)
        {
            digitalWrite(vlv_feedmax, HIGH);
            digitalWrite(vlv_drymax, LOW);
            digitalWrite(vlv_charger, LOW);
            delay(5000);
            digitalWrite(vlv_feedmax, LOW);
            digitalWrite(vlv_drymax, LOW);
            digitalWrite(vlv_charger, LOW);
            qg.pop();
        }
        if (qg.front() == 20)
        {
            digitalWrite(vlv_feedmax, LOW);
            digitalWrite(vlv_drymax, HIGH);
            digitalWrite(vlv_charger, HIGH);
            delay(5000);
            digitalWrite(vlv_feedmax, LOW);
            digitalWrite(vlv_drymax, LOW);
            digitalWrite(vlv_charger, LOW);
            qg.pop();
        }
    }
    else
    {
        digitalWrite(vlv_feedmax, LOW);
        digitalWrite(vlv_drymax, LOW);
        digitalWrite(vlv_charger, LOW);
    }
    if (digitalRead(sen_feedmax) == LOW && digitalRead(sen_arburg) == LOW)
    {
        while (!qg.empty())
        {
            qg.pop();
        }
    }
}

void ClientP::OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    D_ODR(Serial.println("Start ClientP::OnDataRecv()");)
    t_s2c s2c_in;
    D_ODR(Serial.print("Inside OnDataRecv\n");)
    memcpy(&s2c_in, incomingData, sizeof(s2c_in));
    s2c = s2c_in;
    Serial.printf("%4d | %4d\n", s2c_in.ID, s2c_in.start);
    c2s.inout.in++;
    D_ODR(Serial.println("End ClientP::OnDataRecv()");)
    runClient();
}
void ClientP::getQS()
{
    if (!qg.empty())
    {
        c2s.qs = qg.size();
    }
    else
    {
        c2s.qs = 0;
    }
}
// Local variables that holds sensors old status
bool tempFr;
bool tempAr;
bool tempFl;
void ClientP::send2server()
{
    c2s.Freq_sensor = digitalRead(sen_feedmax);
    c2s.Areq_sensor = digitalRead(sen_arburg);
    c2s.Flevel_sensor = digitalRead(sen_feedmax_lvl);
    // D_C2S(Serial.println("Start ClientP::send2server()");)
    // Send sensors readings
    if (c2s.Freq_sensor != tempFr || c2s.Areq_sensor != tempAr || c2s.Flevel_sensor != tempFl)
    {
        getQS();
        esp_err_t result = esp_now_send(serverMacAdd, (uint8_t *)&c2s, sizeof(c2s));
        tempFr = c2s.Freq_sensor;
        tempAr = c2s.Areq_sensor;
        tempFl = c2s.Flevel_sensor;
        Serial.printf("Sending to server %s (%4d, %4d)\n",
                      ((result == ESP_NOW_SEND_FAIL) ? "fail" : "succeed"),
                      c2s.inout.in, c2s.inout.out);
        // D_C2S(Serial.println("End ClientP::send2server()");)
    }
}

void ClientP::printMacAdd(const uint8_t *mac)
{
    for (int i = 0; i < 6; i++)
    {
        Serial.printf("%X%c", mac[i], ((i == 5) ? ' ' : ':'));
    }
}

void ClientP::printServer()
{
    printMacAdd(serverMacAdd);
}
